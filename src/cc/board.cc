#include "../h/board.h"
#include "../h/gameoverexception.h"
#include <memory>
#include <iostream>
#include <vector>
#include <cstddef>
class TextDisplay;

Board::Board(size_t rows, size_t cols, size_t reservedRows) : 
  rows{rows}, cols{cols}, reservedRows{reservedRows}, totalRows{rows + reservedRows} {}

  bool Board::isTopLeftBlocked() const {
    size_t width = currentTetro->getWidth();
    size_t height = currentTetro->getHeight();

    for (size_t row = 0; row < width; ++row) {
      for (size_t col = 0; col < height; ++col) {
        if (theBoard.at(row).at(col).getInfo().type != TetroType::None && 
            currentTetro->getCellInfo(row, col).type != TetroType::None) {
          return false
        }
      }
    }

    return true;
  }

void Board::init() {
  theBoard.clear();
  tetroPosns.clear();
  td = std::make_unique<TextDisplay>(rows, cols);

  theGrid.resize(totalRows);
  for (size_t row = 0; row < totalRows; ++row) {
    for (size_t col = 0; col < cols; ++col) {
      theBoard.at(row).at(col).emplace_back(row, col);
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

void Board::dropRows(int fullRowIndex) {
  for (int row = fullRowIndex; row > reservedRows - 2; --row) {
    // check that the dtors of Cell run for row-1 when it is overwritten  
    theBoard.at(row) = theBoard.at(row - 1);
  }
}

bool Board::generalizedLateralBlockCheck(size_t column = 0, int lr = 0) {
  for (size_t row = 0; row < currentTetro->getHeight(); ++row) {
    Info info = currentTetro->getCellInfo(row, column);
    if (info.col == 0 || info.col == cols - 1) return true; // means it's at the left/right edge of the board

    if (info.type != TetroType::None) {
      TetroType cellType = theBoard.at(info.row).at(info.col + static_cast<size_t>(lr)).getInfo().type;
      if (cellType != TetroType::None) return true;
    }
  }
  return false;
}

bool Board::isBlocked(Direction dir) {
  size_t lowestRow = currentTetro->getHeight() - 1; 
  size_t rightMostRow = currentTetro->getWidth() - 1;

  switch(dir) {
    case Direction::Down : 
      for (size_t col = 0; col < currentTetro->getWidth(); ++col) {
        Info info = currentTetro->getCellInfo(lowestRow, col);
        if (info.row == rows + reservedRows - 1) return true; // means it's at the bottom of the board

        if (info.type != TetroType::None) {
          TetroType cellType = theBoard.at(info.row + 1).at(info.col).getInfo().type;
          if (cellType != TetroType::None) return true;
        }
      }
      break;
    case Direction::Left :
      return generalizedLateralBlockCheck(0, -1);
      break;
    case Direction::Right :
      return generalizedLateralBlockCheck(currentTetro->getWidth() - 1, 1);
      break;
    case Direction::CW :
      // take rotated tetromino
      // compare width of tetromino to how many cells there are between the
      // left/right edge of the tetromino and the edge of the board
      // if there is enough space to rotate, iterate thru the rows and cols
      // ask if a cell in the tetromino is non empty AND is in a cell that is
      // also non empty on the board
      // return true if blocked, false otherwise
      //
      // SAME FOR CCWW
      // TODO
      break;
    case Direction::CCW :
      // TODO
      break;
    default : 
      return true;
      break;
  }
  return false;
}

void Board::move(Direction dir) {  
  for (size_t row = 0; row < currentTetro->getHeight(); ++row) {
    for (size_t col = 0; col < currentTetro->getWidth(); ++col) {
      size_t rowAt = currentTetro->getCellInfo(row, col).row;
      size_t colAt = currentTetro->getCellInfo(row, col).col;
      switch(dir) {
        case Direction::Down :
          // Set cell at board(row, col)  to (row+1, col)
          if (!isBlocked(dir)) currentTetro->setCellPosn(rowAt, colAt, rowAt + 1, colAt);
          break;
        case Direction::Left : 
          // Set cell at board(row, col)  to (row, col-1)
          if (!isBlocked(dir)) currentTetro->setCellPosn(rowAt, colAt, rowAt, colAt - 1);
          break;
        case Direction::Right :
          // Set cell at board(row, col)  to (row, col+1)
          if (!isBlocked(dir)) currentTetro->setCellPosn(rowAt, colAt, rowAt, colAt + 1);
          break;
        default:
          break;
      }
    }
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
      theBoard.at(boardRow).at(boardCol) = currentTetro->getCell(row, col);
    }
  }
}

Board::~Board() {}

std::ostream &operator<<(std::ostream &out, const Board &b) {
  out << *(g.td);
  return out;
}
