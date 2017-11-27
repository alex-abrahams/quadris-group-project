#include "../h/cell.h"

Cell::Cell(size_t row, size_t col) : row{row}, col{col} {}


void Cell::setType(TetroType type) {
  this->type = type;
}

void Cell::setRowCol(size_t newRow, size_t newCol) {
  this->row = newRow;
  this->col = newCol;
}

Info getInfo() {
  Info info {row, col, type};
  return info;
}
