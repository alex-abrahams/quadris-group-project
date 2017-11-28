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

  virtual AbstractTetromino rotatecw() = 0;
	virtual AbstractTetromino rotateccw() = 0;
  virtual ~AbstractTetromino();
  
// REMOVE: the tetromino cant actually move on the board. It can rotate by
// itself but the board needs to move it.
//	virtual AbstractTetromino moveLeft() = 0;
//	virtual AbstractTetromino moveRight() = 0;
//	virtual AbstractTetromino moveDown() = 0;
};

#endif
