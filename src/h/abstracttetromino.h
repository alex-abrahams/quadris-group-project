#ifndef ABSTET_H
#define ABSTET_H
#include "cell.h"
#include "info.h"

class AbstractTetromino {

  public:
  AbstractTetromino();
  virtual ~AbstractTetromino();
  
  virtual TetroType getType() = 0;
	virtual size_t getHeight() = 0;
	virtual size_t getWidth() = 0;
	virtual size_t getLocationRow() = 0;
	virtual size_t getLocationCol() = 0;
	virtual size_t getID() = 0;
	virtual void setID(size_t id) = 0;
	virtual void setLocationRow(size_t r) = 0;
	virtual void setLocationCol(size_t c) = 0;
  // changes the location of this tetromino object's cell on the board
  virtual void setCellPosn(size_t rowAt, size_t colAt, size_t newRow, size_t newCol) = 0;
  virtual Info getCellInfo(size_t row, size_t col) = 0;
  virtual Cell getCell(size_t row, size_t col) = 0;
  virtual void rotateCW() = 0;
  virtual void rotateCCW() = 0;
};
#endif


