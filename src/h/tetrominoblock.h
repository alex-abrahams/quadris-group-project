#ifndef TETBLO_H
#define TETBLO_H
#include "abstracttetromino.h"

class TetrominoBlock : public AbstractTetromino {
	public:
	TetrominoBlock()
	AbstractTetromino rotatecw() override;
	AbstractTetromino rotateccw() override;
};

#endif
