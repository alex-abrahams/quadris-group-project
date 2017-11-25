#ifndef ABSTET_H
#define ABSTET_H
#include "info.h"

class AbstractTetromino {
	int row;
	int col; // location data of bottom left
	int height;
	int width; // dimensions of tetromino
	TetroType type;
	std::vector<std::vector<bool>> cellLocations; // height x width vector of booleans corresponding to locations of cells within tetromino
	public:
	TetroType getType();
	int getHeight();
	int getWidth();
	int getLocationRow();
	int getLocationCol();
	std::vector<std::vector<bool>> getCellLocations();
	virtual AbstractTetromino rotatecw() = 0;
	virtual AbstractTetromino rotateccw() = 0;
	virtual AbstractTetromino moveLeft() = 0;
	virtual AbstractTetromino moveRight() = 0;
	virtual AbstractTetromino moveDown() = 0;
}

#endif
