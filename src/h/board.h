#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <memory>
#include <cstddef>
#include <cell.h>

enum class Direction {Down, Left, Right, CW, CCW};

class Board {
  /* Format of theBoard vector of vectors
     theBoard.at(i): rows
     theBoard.at().at(j): columns
     So, a cell at row i, column j is theBoard.at(i).at(j)

     This is to faciliate moving rows downwards.
     Just reassign theBoard.at(i) = theBoard.at(i-1);
     */
  std::vector<std::vector<Cell>> theBoard;
  const size_t rows; // rows of a board
  const size_t cols; // cols of a board
  const size_t reservedRows; // the rows reserved for rotating the currentTetro
  const size_t totalRows;

  std::unique_ptr<TextDisplay> td;
  std::unique_ptr<AbstractTetromino> currentTetro;

  /* the row and col of the board each cell of the current tetromino is on
     represented by a Cell object who has fields row, col, and type.
     the row and col of the Cell will increment/decrement based on the position
     of the tetromino in the board 
     */
  std::vector<std::vector<Cell>> tetroPosns;

  // checks if row at rowIndex is full
  bool isRowFull(size_t rowIndex) const;

  // returns -1 if there are no full rows
  int getIndexOfFullRow() const;

  // drop the above row(s) once a row is full
  void dropRows();
 
  bool generalizedLateralBlockCheck(size_t column = 0, int lr = 0);

  // checks if moving/rotating current tetromino in the direction dir is possible
  bool isBlocked(Direction dir);


  /* checks if there is space for the block to be 
   * put in the top left corner. 
   * If there isn't, the game ends. */
  bool isTopLeftBlocked() const;
  
  public:

  Board(int rows, int cols, int reservedRows);
  // TODO: void setObserver(Observer<> *obs);


  // initializes theBoard
  void init();
  // moves current tetromino one cell in the direction dir
  void move(Direction dir);
  
  // drops the current tetromino into the top left corner
  void dropIntoTopLeft();

  // hard drop the current tetromino
  void dropTetromino();

  ~Board();

  friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif
