#ifndef TETFAC_H
#define TETFAC_H
#include "abstracttetromino.h"
#include "tetrominoblock.h"
#include "info.h"

class TetrominoFactory {
	size_t currentID = 0;
	public:
	TetrominoBlock *makeTetromino(TetroType type, size_t id);
};

#endif
