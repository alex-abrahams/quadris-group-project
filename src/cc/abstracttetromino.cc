#include "abstracttetromino.h"

TetroType AbstractTetromino::getType() {
	return type;
}

size_t AbstractTetromino::getHeight() {
	return height;
}

size_t AbstractTetromino::getWidth() {
	return width;
}

size_t AbstractTetromino::getLocationRow() {
	return row;
}

size_t AbstractTetromino::getLocationCol() {
	return col;
}

Info getCellInfo(size_t row, size_t col) {
	return cells.at(row).at(col).getInfo();
}

Cell getCell(size_t row, size_t col) {
	return cells.at(row).at(col);
}
