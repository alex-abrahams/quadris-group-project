#ifndef CELL_H
#define CELL_H

#include "info.h"
#include "notiffrom.h"
#include "publisher.h"
#include "observer.h"

class Cell : public Publisher<Info, NotifFrom> {
  size_t row, col;
  size_t id; // incrementing id number
  TetroType type = TetroType::None;

  size_t distanceMovedLeft, distanceMovedRight, distanceMovedDown = 0;

  public:
  Cell();
  Cell(size_t row, size_t col, size_t id = 0, TetroType type = TetroType::None);

  // make this cell hold a certain Tetromino type.
  void setType(TetroType type);
  
  void setRowCol(size_t newRow, size_t newCol);
  
  size_t getID();

  Info getInfo() const override;

};

#endif

