#include "../h/board.h"
#include <memory>
#include <iostream>
#include <vector>
#include <cstddef>
#include "../h/gameoverexception.h"
class TextDisplay;

Board::Board(size_t rows, size_t cols, size_t reservedRows) : 
	rows{rows}, cols{cols}, reservedRows{reservedRows}, totalRows{rows + reservedRows} {}

bool Board::isTopLeftBlocked() const {
	  size_t width = currentTetro->getWidth();
    size_t height = currentTetro->getHeight();

    
    for (size_t row = 0; row < width; ++row) {
        for (size_t col = 0; col < height; ++col) {
            if (theBoard.at(row).at(col).getInfo().type != TetroType::None && 
                currentTetro->getCell(row, col).getInfo().type != TetroType::None) {
                return false
            }
        }
    }

    return true;
}

void Board::init() {
    theBoard.clear();
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
    for (int row = fullRowIndex; row > reservedRows - 1; --row) {
        // check that the dtors of Cell run for row-1 when it is overwritten  
        theBoard.at(row) = theBoard.at(row - 1);
    }
}

// TODO
void Board::dropTetromino() {
    
}

Board::~Board() {}

std::ostream &operator<<(std::ostream &out, const Board &b) {
  out << *(g.td);
  return out;
}
