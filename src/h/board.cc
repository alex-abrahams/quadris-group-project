#include "board.h"

Board::Board(int rows, int cols, int reservedRows) : 
	rows{rows}, cols{cols}, reservedRows{reservedRows} {}

bool Board::isFull() {
	return emptyCells == 0;
}

void Board::init() {

}

void Board::drop() {

}

Board::~Board() {

}
