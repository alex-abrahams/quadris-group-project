#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <memory>
#include <cstddef>

class Board {
	/* Format of theBoard vector of vectors
		theBoard.at(i): rows
		theBoard.at().at(j): columns
		So, a cell at row i, column j is theBoard.at(i).at(j)

		This is to faciliate moving rows downwards.
		Just reassign theBoard.at(i) = theBoard.at(i+1);
	*/
	std::vector<std::vector<Cell>> theBoard;
	const size_t rows;
	const size_t cols;
	const size_t reservedRows;
  const size_t totalRows;

  std::unique_ptr<TextDisplay> td;
  std::unique_ptr<AbstractTetromino> currentTetro;
	
    // checks if row at rowIndex is full
    bool isRowFull(size_t rowIndex) const;

    // returns -1 if there are no full rows
    int getIndexOfFullRow() const;

    // drop the above row(s) once a row is full
    void dropRows();

	public:

		Board(int rows, int cols, int reservedRows);
	   // TODO: void setObserver(Observer<> *obs);
		
    /* checks if there is space for the block to be 
     * put in the top left corner. 
     * If there isn't, the game ends. */
    bool isTopLeftBlocked() const;
		
    // initializes theBoard
    void init();

    // drops the current tetromino into the top left corner
    void dropIntoTopLeft();

    // hard drop the current tetromino
		void dropTetromino();

		~Board();

    friend std::ostream &operator<<(std::ostream &out, const Board &b);
}

#endif
