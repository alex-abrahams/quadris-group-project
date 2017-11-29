#include "cell.h"

Cell::Cell(size_t row, size_t col, size_t id) : row{row}, col{col}, id{id} {}

void Cell::setType(TetroType type) {
  this->type = type;
  this->notifyObservers();
}

void Cell::setRowCol(size_t newRow, size_t newCol) {
  this->row = newRow;
  this->col = newCol;
}

Info Cell::getInfo() const {
  Info info {row, col, type};
  return info;
}
