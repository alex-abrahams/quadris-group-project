#ifndef ABSTET_H
#define ABSTET_H
#include "cell.h"
#include "info.h"

class AbstractTetromino {

  public:
  virtual ~AbstractTetromino() = 0;
  
  virtual TetroType getType();
	virtual size_t getHeight();
	virtual size_t getWidth();
	virtual size_t getLocationRow();
	virtual size_t getLocationCol();
  // changes the location of this tetromino object's cell on the board
  virtual void setCellPosn(size_t rowAt, size_t colAt, size_t newRow, size_t newCol);
  virtual Info getCellInfo(size_t row, size_t col);
  virtual Cell getCell(size_t row, size_t col);

};

#endif
