#include "../h/tetrominofactory.h"

TetrominoBlock *TetrominoFactory::makeTetromino(TetroType type) {
	currentID++;
	TetrominoBlock *theTetro;
	switch (type) {
		case TetroType::IBlock:
			theTetro = TetrominoBlock(4, 1, 3, 0, currentID, type);
			theTetro->setCell(0,0);
			theTetro->setCell(0,1);
			theTetro->setCell(0,2);
			theTetro->setCell(0,3);
			break;
		case TetroType::JBlock:
			theTetro = TetrominoBlock(3, 2, 3, 0, currentID, type);
			theTetro->setCell(0,0);
			theTetro->setCell(1,0);
			theTetro->setCell(1,1);
			theTetro->setCell(1,2);
			break;
		case TetroType::LBlock:
			theTetro = TetrominoBlock(3, 2, 3, 0, currentID, type);
			theTetro->setCell(0,2);
			theTetro->setCell(1,0);
			theTetro->setCell(1,1);
			theTetro->setCell(1,2);
			break;
		case TetroType::ZBlock:
			theTetro = TetrominoBlock(3, 2, 3, 0, currentID, type);
			theTetro->setCell(0,0);
			theTetro->setCell(0,1);
			theTetro->setCell(1,1);
			theTetro->setCell(1,2);
			break;
		case TetroType::ZeroBlock:
			theTetro = TetrominoBlock(2, 2, 3, 0, currentID, type);
			theTetro->setCell(0,0);
			theTetro->setCell(1,0);
			theTetro->setCell(0,1);
			theTetro->setCell(1,1);
			break;
		case TetroType::SBlock:
			theTetro = TetrominoBlock(3, 2, 3, 0, currentID, type);
			theTetro->setCell(1,0);
			theTetro->setCell(1,1);
			theTetro->setCell(0,1);
			theTetro->setCell(0,2);
			break;
		case TetroType::TBlock:
			theTetro = TetrominoBlock(3, 2, 3, 0, currentID, type);
			theTetro->setCell(0,0);
			theTetro->setCell(0,1);
			theTetro->setCell(0,2);
			theTetro->setCell(1,1);
			break;
	}
	return theTetro;
}
