#ifndef TETFAC_H
#define TETFAC_H

#include <memory>
#include <iostream>
#include "abstracttetromino.h"
#include "tetrominoblock.h"
#include "info.h"
class TetrominoFactory {
	size_t currentID = 0;
	public:
	size_t getCurrentID();
  std::shared_ptr<TetrominoBlock> makeTetromino(TetroType type, size_t id = 1);
};

#endif

