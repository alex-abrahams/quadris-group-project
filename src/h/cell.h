#ifndef CELL_H
#define CELL_H
#include "info.h"

class Cell : public Publisher<Info> {
  size_t row, col;
  size_t id; // incrementing id number
  TetroType type;

  public:
  Cell(size_t row, size_t col, size_t id, TetroType type = TetroType::None);

  // make this cell hold a certain Tetromino type.
  void setType(TetroType type);
  
  void setRowCol(size_t newRow, size_t newCol);

  Info getInfo() const override;

};

#endif
