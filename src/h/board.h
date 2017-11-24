
#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
	/* Format of theBoard vector of vectors
		theBoard.at(i): rows
		theBoard.at().at(j): columns
		So, a cell at row i, column j is theBoard.at(i).at(j)

		This is to faciliate moving rows downwards.
		Just reassign theBoard.at(i) = theBoard.at(i+1);
	*/
	std::vector<std::vector<Cell>> theBoard;
	int rows;
	int cols;
	const int reserverdRows;
	int emptyCells;

	AbstractTetromino *currentTetro;
	
	public:
		Board(int rows, int cols, int reservedRows);
	   // TODO: void setObserver(Observer<> *obs);
		bool isFull() const;
		void init();
		void drop();
		~Board();
}

#endif
