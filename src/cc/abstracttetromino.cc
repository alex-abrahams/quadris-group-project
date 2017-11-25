#include "abstracttetromino.h"

TetroType AbstractTetromino::getType() {
	return type;
}

int AbstractTetromino::getHeight() {
	return height;
}

int AbstractTetromino::getWidth() {
	return width;
}

int AbstractTetromino::getLocationRow() {
	return row;
}

int AbstractTetromino::getLocationCol() {
	return col;
}
