#include "tetrominoblock.h"

TetrominoBlock::TetrominoBlock(size_t w, size_t h, size_t r, size_t c, size_t id, TetroType t)
  : row{r}, col{c}, height{h}, width{w}, id{id}, type{t} {
	for (size_t rr = 0; rr < h; rr++) {
		cells.push_back(std::vector<Cell>());
		for (size_t cc = 0; cc < width; cc++) {
      cells.at(rr).emplace_back(r - h + 1 + rr, c + cc, id);
		}
	}
}

TetrominoBlock::~TetrominoBlock() {}

void TetrominoBlock::setCell(size_t r, size_t c) {
	cells.at(r).at(c) = Cell(row - height + 1 + r, col + c, id, type);
}

size_t lowerLeftRowIdx() {
  return 0;
}
size_t lowerRightRowIdx() {
  return 0;
}

TetroType TetrominoBlock::getType()  {
	return type;
}

size_t TetrominoBlock::getHeight() {
	return height;
}

size_t TetrominoBlock::getWidth()  {
	return width;
}

size_t TetrominoBlock::getLocationRow()  {
	return row;
}

size_t TetrominoBlock::getLocationCol()  {
	return col;
}

void TetrominoBlock::setCellPosn(size_t rowAt, size_t colAt, size_t newRow, size_t newCol)  {
}

Info TetrominoBlock::getCellInfo(size_t row, size_t col)  {
	return cells.at(row).at(col).getInfo();
}

Cell TetrominoBlock::getCell(size_t row, size_t col)  {
	return cells.at(row).at(col);
}

