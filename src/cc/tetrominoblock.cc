#include "../h/tetrominoblock.h"

TetrominoBlock::TetrominoBlock(size_t w, size_t h, size_t r, size_t c, size_t id, TetroType t): height{h}, width{w}, row{r}, col{c}, id{id}, type{t} {
	for (int rr = 0; rr < height; rr++) {
		cells.push_back( std::vector<Cell>() );
		for (int cc = 0; cc < width; cc++) {
			cells.at(rr).push_back(Cell(r-h+1+rr, c+cc, id));
		}
	}
}

void TetrominoBlock::setCell(size_t r, size_t c) {
	cells.at(r).at(c) = Cell(row-height+1+r, col+c, id, type);
}

AbstractTetromino TetrominoBlock::rotatecw() {
	//TODO: rotate clockwise function
}

AbstractTetromino TetrominoBlock::rotateccw() {
	//TODO: rotate counterclockwise function
}
