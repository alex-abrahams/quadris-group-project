#ifndef TETFAC_H
#define TETFAC_H
#include "abstracttetromino.h"
#include "tetrominoblock.h"
#include "info.h"

class TetrominoFactory {
	TetrominoBlock *makeTetromino(TetroType type);
};

#endif
