#include "board.h"
#include "gameoverexception.h"
#include "abstracttetromino.h"
#include <memory>
#include <iostream>
#include <vector>
#include <cstddef>
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "gamesingleton.h"
#include "tetrominoblock.h"

void Board::setCurrentTetromino(std::shared_ptr<AbstractTetromino> tetro) {
  this->currentTetro = tetro;
}

std::shared_ptr<TextDisplay> Board::getTextDisplay() {
  return this->td;
}

std::shared_ptr<GraphicsDisplay> Board::getGraphicsDisplay() {
  return this->gd;
}


void Board::init(size_t rows, size_t cols, size_t reservedRows, bool textonly) {
  this->textonly = textonly;
  this->rows = rows;
  this->cols = cols;
  this->reservedRows = reservedRows;
  this->totalRows = rows + reservedRows;
  currentId = 0;
  td = std::make_shared<TextDisplay>(totalRows, cols);
  if (!textonly) {
  	gd = std::shared_ptr<GraphicsDisplay>(new GraphicsDisplay(static_cast<int>(totalRows), static_cast<int>(cols), 600, 600));
  }
  theBoard.resize(totalRows);
  for (size_t row = 0; row < totalRows; ++row) {
    for (size_t col = 0; col < cols; ++col) {
      theBoard.at(row).emplace_back(row, col);
      theBoard.at(row).at(col).attach(td);
      if (!textonly) theBoard.at(row).at(col).attach(gd);
    }
  }
}

/*void Board::dropIntoTopLeft() {
  if (isTopLeftBlocked()) throw GameOverException{"game over"};
  size_t width = currentTetro->getWidth();
  size_t height = currentTetro->getHeight();
  for (size_t row = reservedRows - 1; row < height + reservedRows - 1; ++row) {
    for (size_t col = 0; col < width; ++col) {
      theBoard.at(row).at(col) = currentTetro->getCell(row, col);
    }
  }
}*/

bool Board::isTopLeftBlocked() const {
  size_t width = currentTetro->getWidth();
  size_t height = currentTetro->getHeight();
  for (size_t row = 0; row < height; ++row) {
    for (size_t col = 0; col < width; ++col) {
      Info info = currentTetro->getCellInfo(row, col);
      if (theBoard.at(info.row).at(info.col).getInfo().type != TetroType::None &&
          info.type != TetroType::None) {
        return true;
      }
    }
  }
  return false;
}

bool Board::isRowFull(size_t rowIndex) const {
  for (size_t col = 0; col < cols; ++col) {
    if (theBoard.at(rowIndex).at(col).getInfo().type == TetroType::None)
      return false;
  }
  return true;
}

int Board::getIndexOfFullRow() const {
  for (size_t row = totalRows-1; row > 0; row--) {
	  if (isRowFull(row)) return row;
  }
  return -1;
}

void Board::dropRows(size_t fullRowIndex) {
  for (size_t row = fullRowIndex; row > reservedRows - 2; --row) {
    if (row > 0) {
		theBoard.at(row) = theBoard.at(row - 1);
		for (size_t col = 0; col < cols; col++) {
			theBoard.at(row).at(col).setRowCol(theBoard.at(row).at(col).getInfo().row+1, col);
		}
	}
  }
}

bool Board::generalizedLateralBlockCheck(int lr) {
  for (size_t row = 0; row < currentTetro->getHeight(); ++row) {
    for (size_t column = 0; column < currentTetro->getWidth(); ++column) {
      Info info = currentTetro->getCellInfo(row, column);
      if ((info.col == 0 && lr == -1) || (info.col == cols - 1 && lr == 1)) {
        return true; // means it's at the left/right edge of the board
      }
      if (info.type != TetroType::None) {
        if ((column == 0 && lr == -1) ||  
            (column == currentTetro->getWidth()-1 && lr == 1) || 
            currentTetro->getCellInfo(row, column+lr).type == TetroType::None) {
          TetroType cellType = theBoard.at(info.row).at(info.col + static_cast<size_t>(lr)).getInfo().type;
          if (cellType != TetroType::None) {
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

      if ((info.row >= 18 || info.col >= 11) || (info.type != TetroType::None && 
          theBoard.at(info.row).at(info.col).getInfo().type != TetroType::None)) {
        return true;
      }
    }
  }
  return false;
}
bool Board::isBlocked(Direction dir) {
  TetrominoBlock temp = *(std::dynamic_pointer_cast<TetrominoBlock>(currentTetro));
  switch(dir) {
    case Direction::Down :
      for (size_t row = 0; row < currentTetro->getHeight(); ++row) {
        for (size_t column = 0; column < currentTetro->getWidth(); ++column) {
          Info info = currentTetro->getCellInfo(row, column);
          
          if (info.row == totalRows - 1) {
            return true; // means it's at the left/right edge of the board
          }
          
          if (info.type != TetroType::None) {
            if ((row == currentTetro->getHeight()-1) || 
                currentTetro->getCellInfo(row+1, column).type == TetroType::None) {
              
              TetroType cellType = theBoard.at(info.row + 1).at(info.col).getInfo().type;
              
              if (cellType != TetroType::None) {
                return true;
              }
            }
          }
        }
      }

      return false;
      break;
    case Direction::Left :
      return generalizedLateralBlockCheck(-1);
      break;
    case Direction::Right :
      return generalizedLateralBlockCheck(1);
      break;
    case Direction::CW :
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
      NotifFrom ntf {FromType::Move, 0, 0, 0,0,dir};
      this->setNotifFrom(ntf);
      switch(dir) {
        case Direction::Down :
          currentTetro->setLocationRow(currentTetro->getLocationRow()+1);
          this->notifyObservers();
          break;
        case Direction::Left :
          currentTetro->setLocationCol(currentTetro->getLocationCol()-1);
          this->notifyObservers();
          break;
        case Direction::Right :
          currentTetro->setLocationCol(currentTetro->getLocationCol()+1);
          this->notifyObservers();
          break;
        case Direction::CW :
          currentTetro->rotateCW();
          this->notifyObservers();
          break;
        case Direction::CCW :
          currentTetro->rotateCCW();
          this->notifyObservers();
          break;
        default :
          break;
      }
    }

    bool b = false;
    if (dir == Direction::Down || dir == Direction::Right || dir == Direction::Left) {
      b = isBlocked(dir);
    }

    for (size_t row = 0; row < currentTetro->getHeight(); ++row) {
      for (size_t col = 0; col < currentTetro->getWidth(); ++col) {
        size_t rowAt = currentTetro->getCellInfo(row, col).row;
        size_t colAt = currentTetro->getCellInfo(row, col).col;

        switch(dir) {
          case Direction::Down :
            // Set cell at board(row, col)  to (row+1, col)
            if (!b) {
              currentTetro->setCellPosn(row, col, rowAt + 1, colAt);
            } 
            break;
          case Direction::Left :
            // Set cell at board(row, col)  to (row, col-1)
            if (!b) {
              currentTetro->setCellPosn(row, col, rowAt, colAt - 1);
            }
            break;
          case Direction::Right :
            // Set cell at board(row, col)  to (row, col+1)
            if (!b) {
              currentTetro->setCellPosn(row, col, rowAt, colAt + 1);
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
		
        if (!textonly) theBoard.at(boardRow).at(boardCol).attach(gd);
        theBoard.at(boardRow).at(boardCol).notifyObservers();
      }
    }
  }

  // remove full rows, scoring
  size_t numberOfRowsRemoved = 0;
  while (getIndexOfFullRow() != -1) {
	  std::cout << "full row at " << getIndexOfFullRow() << std::endl;
	  numberOfRowsRemoved++;
	  dropRows(getIndexOfFullRow());
  }
  // add to score
  if (numberOfRowsRemoved > 0) {
	 GameSingleton::get().setRowsScore(GameSingleton::get().getRowsScore() +
       ((GameSingleton::get().getLevel() + numberOfRowsRemoved) * 
        (GameSingleton::get().getLevel() + numberOfRowsRemoved))); 
  }
  
  
  // add to score based on blocks fully removed
  size_t curID = GameSingleton::get().getCurrentID();
  bool found;
  size_t blocksClearedScore = 0;
  for (size_t i = 1; i < curID; i++) {
	  found = false;
	  for (size_t row = 0; row < totalRows; row++) {
		  for (size_t col = 0; col < cols; col++) {
			  if (theBoard.at(row).at(col).getID() == i) found = true;
			}
		}
		if (!found) {
			//TODO: change this to (the level at which the block was spawned + 1) ^ 2
			std::cout << "nothing with id " << i << " found" << std::endl;
			blocksClearedScore += 1;
		}
	}

  GameSingleton::get().setBlocksClearedScore(blocksClearedScore);

  for (size_t row = 0; row < totalRows; row++) {
    for (size_t col = 0; col < cols; col++) {
  	  theBoard.at(row).at(col).notifyObservers();
    }
  }
}

Board::~Board() {}

bool Board::isTextOnly() const {
	return textonly;
}

std::ostream &operator<<(std::ostream &out, const Board &b) {
  b.td -> draw(out, b.currentTetro);
  if (!b.isTextOnly()) {
	  b.gd -> draw(b.currentTetro);
  }
  return out;
}
