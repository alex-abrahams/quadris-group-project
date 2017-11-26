#include "../h/cell.h"

Cell::Cell(size_t row, size_t col) : row{row}, col{col} {}


void Cell::setType(TetroType type) {
  this->type = type;
}

Info getInfo() {
  Info info {row, col, type};
  return info;
}
