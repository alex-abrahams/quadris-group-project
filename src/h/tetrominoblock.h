#ifndef TETBLO_H
#define TETBLO_H
#include "abstracttetromino.h"
#include "info.h"
#include "cell.h"

class TetrominoBlock : public AbstractTetromino {
	size_t id;
	public:
	TetrominoBlock(size_t w, size_t h, size_t r, size_t c, size_t id, TetroType t);
	void setCell(size_t r, size_t c);
	void rotatecw() override;
	void rotateccw() override;
};

#endif
