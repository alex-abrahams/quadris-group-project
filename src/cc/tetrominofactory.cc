#include "../h/tetrominofactory.h"

std::shared_ptr<TetrominoBlock> TetrominoFactory::makeTetromino(TetroType type, size_t id) {
  std::shared_ptr<TetrominoBlock> theTetro;
	switch (type) {
		case TetroType::IBlock:
			theTetro = std::make_shared<TetrominoBlock>(4, 1, 3, 0, currentID, type);
			theTetro->setCell(0,0);
			theTetro->setCell(0,1);
			theTetro->setCell(0,2);
			theTetro->setCell(0,3);
			break;
		case TetroType::JBlock:
			theTetro = std::make_shared<TetrominoBlock>(3, 2, 2, 0, currentID, type);
			theTetro->setCell(0,0);
			theTetro->setCell(1,0);
			theTetro->setCell(1,1);
			theTetro->setCell(1,2);
			break;
		case TetroType::LBlock:
			theTetro = std::make_shared<TetrominoBlock>(3, 2, 2, 0, currentID, type);
			theTetro->setCell(0,2);
			theTetro->setCell(1,0);
			theTetro->setCell(1,1);
			theTetro->setCell(1,2);
			break;
		case TetroType::ZBlock:
			theTetro = std::make_shared<TetrominoBlock>(3, 2, 2, 0, currentID, type);
			theTetro->setCell(0,0);
			theTetro->setCell(0,1);
			theTetro->setCell(1,1);
			theTetro->setCell(1,2);
			break;
		case TetroType::ZeroBlock:
			theTetro = std::make_shared<TetrominoBlock>(2, 2, 1, 0, currentID, type);
			theTetro->setCell(0,0);
			theTetro->setCell(1,0);
			theTetro->setCell(0,1);
			theTetro->setCell(1,1);
			break;
		case TetroType::SBlock:
			theTetro = std::make_shared<TetrominoBlock>(3, 2, 2, 0, currentID, type);
			theTetro->setCell(1,0);
			theTetro->setCell(1,1);
			theTetro->setCell(0,1);
			theTetro->setCell(0,2);
			break;
		case TetroType::TBlock:
			theTetro = std::make_shared<TetrominoBlock>(3, 2, 2, 0, currentID, type);
			theTetro->setCell(0,0);
			theTetro->setCell(0,1);
			theTetro->setCell(0,2);
			theTetro->setCell(1,1);
			break;
    case TetroType::None:
      break;
    case TetroType::OneBlock:
      theTetro = std::make_shared<TetrominoBlock>(1, 1, 0, 0, currentID, type);
      theTetro->setCell(0,0);
      break;
    default:
      break;
	}

	return theTetro;
}

size_t TetrominoFactory::getCurrentID() {
	return currentID;
}

void TetrominoFactory::addToID() {
	currentID++;
}

