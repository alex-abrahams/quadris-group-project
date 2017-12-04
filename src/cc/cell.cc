#include "cell.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "gamesingleton.h"

Cell::Cell() {
  row = 0;
  col = 0;
  id = 0;
  type = TetroType::None;
}

Cell::Cell(size_t row, size_t col, size_t id, TetroType type) : row{row}, col{col}, id{id}, type{type} {
  NotifFrom notifFrom {FromType::Cell};
  this->setNotifFrom(notifFrom);
}

void Cell::setRowCol(size_t newRow, size_t newCol) {
  this->row = newRow;
  this->col = newCol;
}

Info Cell::getInfo() const {
  Info info {row, col, type};
  return info;
}

void Cell::setID(size_t i) {
	id = i;
}

size_t Cell::getID() {
	return id;
}


