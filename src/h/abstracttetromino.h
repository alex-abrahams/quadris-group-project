#ifndef ABSTET_H
#define ABSTET_H
#include "info.h"
#include "cell.h"

class AbstractTetromino {
	size_t row;
  size_t col; // location of bottom left
	size_t height;
	size_t width; // dimensions of tetromino
	TetroType type;
	std::vector<std::vector<Cell>> cells;
	
  public:
  	
  virtual TetroType getType();
	virtual size_t getHeight();
	virtual size_t getWidth();
	virtual size_t lowerLeftRowIdx();
	virtual size_t lowerRightRowIdx();
  // changes the location of this tetromino object's cell on the board
  virtual void setCellPosn(size_t rowAt, size_t colAt, size_t newRow, size_t newCol);
  virtual Info getCellInfo(size_t row, size_t col);
  virtual Cell getCell(size_t row, size_t col);

  virtual AbstractTetromino rotatecw() = 0;
	virtual AbstractTetromino rotateccw() = 0;
  virtual ~AbstractTetromino();
  
}

#endif
