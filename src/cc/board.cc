#include "board.h"
#include "gameoverexception.h"
#include "abstracttetromino.h"
#include <memory>
#include <iostream>
#include <vector>
#include <cstddef>
#include "textdisplay.h"


void Board::setCurrentTetromino(std::shared_ptr<AbstractTetromino> tetro) {
  this->currentTetro = tetro;
}

std::shared_ptr<TextDisplay> Board::getTextDisplay() {
  return this->td;
}

bool Board::isTopLeftBlocked() const {
  size_t width = currentTetro->getWidth();
  size_t height = currentTetro->getHeight();

  for (size_t row = 0; row < width; ++row) {
    for (size_t col = 0; col < height; ++col) {
      if (theBoard.at(row).at(col).getInfo().type != TetroType::None && 
          currentTetro->getCellInfo(row, col).type != TetroType::None) {
        return false;
      }
    }
  }

  return true;
}

void Board::init(size_t rows, size_t cols, size_t reservedRows) {
  this->rows = rows;
  this->cols = cols;
  this->reservedRows = reservedRows;
  this->totalRows = rows + reservedRows;
  currentId = 0;

  td = std::make_shared<TextDisplay>(totalRows, cols);
  theBoard.resize(totalRows);

  for (size_t row = 0; row < totalRows; ++row) {
    for (size_t col = 0; col < cols; ++col) {
      theBoard.at(row).emplace_back(row, col);
      theBoard.at(row).at(col).attach(td);
    }
  }
}

void Board::dropIntoTopLeft() {
  if (isTopLeftBlocked()) throw GameOverException{"game over"};

  size_t width = currentTetro->getWidth();
  size_t height = currentTetro->getHeight();

  for (size_t row = reservedRows - 1; row < height + reservedRows - 1; ++row) {
    for (size_t col = 0; col < width; ++col) {
      theBoard.at(row).at(col) = currentTetro->getCell(row, col);
    }
  }    
}


bool Board::isRowFull(size_t rowIndex) const {
  for (size_t col = 0; col < cols; ++col) {      
    if (theBoard.at(rowIndex).at(col).getInfo().type == TetroType::None)
      return false;
  }

  return true;
}

int Board::getIndexOfFullRow() const {
  for (size_t row = reservedRows - 1; row < rows; ++row) {
    if (isRowFull(row)) return row;
  }
  return -1;
}

void Board::dropRows(size_t fullRowIndex) {
  for (size_t row = fullRowIndex; row > reservedRows - 2; --row) {
    // check that the dtors of Cell run for row-1 when it is overwritten  
    if (row > 0) theBoard.at(row) = theBoard.at(row - 1);
  }
}

bool Board::generalizedLateralBlockCheck(/*size_t column, */int lr) {
  //std::cout << "BLOCKCHECK!!! height = " << currentTetro->getHeight() << " width = " << currentTetro->getWidth() << std::endl;
  for (size_t row = 0; row < currentTetro->getHeight(); ++row) {
    for (size_t column = 0; column < currentTetro->getWidth(); ++column) {
      //std::cout << "checking " << row << ", " << column << std::endl;
      Info info = currentTetro->getCellInfo(row, column);
      if ((info.col == 0 && lr == -1) || (info.col == cols - 1 && lr == 1)) {
        //std::cout << "edge!!" << std::endl;
        return true; // means it's at the left/right edge of the board
      }

      if (info.type != TetroType::None) {
        if ((column == 0 && lr == -1) ||  (column == currentTetro->getWidth()-1 && lr == 1) || currentTetro->getCellInfo(row, column+lr).type == TetroType::None) {
          TetroType cellType = theBoard.at(info.row).at(info.col + static_cast<size_t>(lr)).getInfo().type;
          if (cellType != TetroType::None) {
            //std::cout << "blocked!!!!" << std::endl;
            return true;
          }
        }
      }
    }
  }
  return false;
}


bool Board::rotationCheck(AbstractTetromino &temp) {
  for (size_t row = 0; row < temp.getHeight(); ++row) {    
    for (size_t col = 0; col < temp.getWidth(); ++col) {
      Info info = temp.getCellInfo(row, col);

      if (info.type != TetroType::None && 
          theBoard.at(row).at(col).getInfo().type != TetroType::None) {
        return true;
      }

    }
  }
  return false;
}

bool Board::isBlocked(Direction dir) {
  size_t lowestRow = currentTetro->getHeight() - 1; 
  AbstractTetromino &temp = *currentTetro; 

  switch(dir) {
    case Direction::Down : 
      //for (size_t col = 0; col < currentTetro->getWidth(); ++col) {
      //  Info info = currentTetro->getCellInfo(lowestRow, col);
      //
      //  std::cout << "Board::isblocked -> info.row " << info.row << std::endl;
      //
      //  if (info.row == totalRows - 1) return true; // means it's at the bottom of the board
      //
      //  if (info.type != TetroType::None) {
      //    TetroType cellType = theBoard.at(info.row + 1).at(info.col).getInfo().type;
      //    if (cellType != TetroType::None) return true;
      //  }
      //}
      for (size_t row = 0; row < currentTetro->getHeight(); ++row) {
        for (size_t column = 0; column < currentTetro->getWidth(); ++column) {
          //std::cout << "checking " << row << ", " << column << std::endl;
          Info info = currentTetro->getCellInfo(row, column);
          if (info.row == totalRows - 1) {
            //std::cout << "edge!!" << std::endl;
            return true; // means it's at the left/right edge of the board
          }

          if (info.type != TetroType::None) {
            if ((row == currentTetro->getHeight()-1) || currentTetro->getCellInfo(row+1, column).type == TetroType::None) {
              TetroType cellType = theBoard.at(info.row + 1).at(info.col).getInfo().type;
              if (cellType != TetroType::None) {
                //std::cout << "blocked!!!!" << std::endl;
                return true;
              }
            }
          }
        }
      }
      return false;
      break;
    case Direction::Left :
      return generalizedLateralBlockCheck(/*0, */-1);
      break;
    case Direction::Right :
      return generalizedLateralBlockCheck(/*currentTetro->getWidth() - 1, */1);
      break;
    case Direction::CW :
      // rotate tetromino
      // compare width of tetromino to how many cells there are between the
      // left/right edge of the tetromino and the edge of the board
      // if there is enough space to rotate, iterate thru the rows and cols
      // ask if a cell in the tetromino is non empty AND is in a cell that is
      // also non empty on the board
      // return true if blocked, false otherwise
      //
      // SAME FOR CCW

      temp.rotateCW();
      return rotationCheck(temp);
      break;
    case Direction::CCW :
      temp.rotateCCW();
      return rotationCheck(temp);
      break;
    default : 
      return true;
      break;
  }
  return false;
}

void Board::move(Direction dir) {  
  if (currentTetro) {
    if (!isBlocked(dir)) {
      switch(dir) {
        case Direction::Down :
          currentTetro->setLocationRow(currentTetro->getLocationRow()+1);
          break;
        case Direction::Left : 
          currentTetro->setLocationCol(currentTetro->getLocationCol()-1);
          break;
        case Direction::Right : 
          currentTetro->setLocationCol(currentTetro->getLocationCol()+1);
          break;
        case Direction::CW :
          currentTetro->rotateCW();
          break;
        case Direction::CCW :
          currentTetro->rotateCCW(); 
          break;
        default :
          break;
      }
    }
    bool b = isBlocked(dir);
    for (size_t row = 0; row < currentTetro->getHeight(); ++row) {
      for (size_t col = 0; col < currentTetro->getWidth(); ++col) {

        size_t rowAt = currentTetro->getCellInfo(row, col).row;
        size_t colAt = currentTetro->getCellInfo(row, col).col;
        switch(dir) {
          case Direction::Down :
            // Set cell at board(row, col)  to (row+1, col)
            if (!b) {
              currentTetro->setCellPosn(row, col, rowAt + 1, colAt);
              std::cout << rowAt << "," << colAt << " to " << rowAt + 1 << "," << colAt << std::endl; 
            } else { std::cout << "blocked!" << std::endl; }
            break;
          case Direction::Left : 
            // Set cell at board(row, col)  to (row, col-1)
            if (!b) {
              currentTetro->setCellPosn(row, col, rowAt, colAt - 1);
              std::cout << rowAt << "," << colAt << " to " << rowAt << "," << colAt-1 << std::endl; 
            }
            break;
          case Direction::Right :
            // Set cell at board(row, col)  to (row, col+1)
            if (!b) {
              currentTetro->setCellPosn(row, col, rowAt, colAt + 1);
              std::cout << rowAt << "," << colAt << " to " << rowAt << "," << colAt+1 << std::endl; 
            }
            break;
          case Direction::CW :
            break;
          case Direction::CCW :
            break;
          default:
            break;
        }

      }
    }

  } else {
    std::cout << "Current tetro in board is null" << std::endl;
  }
}

void Board::dropTetromino() {
  while(!isBlocked(Direction::Down)) {
    move(Direction::Down);
  }

  // put the current tetromino onto the board.
  for (size_t row = 0; row < currentTetro->getHeight(); ++row) {
    for (size_t col = 0; col < currentTetro->getWidth(); ++col) {
      size_t boardRow = currentTetro->getCellInfo(row, col).row;
      size_t boardCol = currentTetro->getCellInfo(row, col).col;
      if (currentTetro->getCellInfo(row, col).type != TetroType::None) {
        theBoard.at(boardRow).at(boardCol) = currentTetro->getCell(row, col);
        theBoard.at(boardRow).at(boardCol).attach(td);
        theBoard.at(boardRow).at(boardCol).notifyObservers();
      }
    }
  }
  //for (size_t row = 0; row < totalRows; row++) {
  //  for (size_t col = 0; col < cols; col++) {
  //	  std::cout << row << "," << col << std::endl;
  //	  theBoard.at(row).at(col).notifyObservers();
  //  }
  //}
}

Board::~Board() {}

std::ostream &operator<<(std::ostream &out, const Board &b) {
  b.td -> draw(out, b.currentTetro);
  return out;
}



