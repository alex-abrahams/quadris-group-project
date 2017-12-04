#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <memory>
#include <cstddef>
#include "cell.h"
#include "tetrominofactory.h"

class TextDisplay;
class GraphicsDisplay;
class AbstractTetromino;

enum class Direction {Down, Left, Right, CW, CCW};
class Board : public Publisher<Info, NotifFrom>{
  /* Format of theBoard vector of vectors
     theBoard.at(i): rows
     theBoard.at().at(j): columns
     So, a cell at row i, column j is theBoard.at(i).at(j)

     This is to faciliate moving rows downwards.
     Just reassign theBoard.at(i) = theBoard.at(i-1);
     */
  std::vector<std::vector<Cell>> theBoard;
  size_t rows; // rows of a board
  size_t cols; // cols of a board
  size_t reservedRows; // the rows reserved for rotating the currentTetro
  size_t totalRows;
  size_t currentId;
  bool textonly;

  std::shared_ptr<TextDisplay> td;
  std::shared_ptr<GraphicsDisplay> gd;
  std::shared_ptr<AbstractTetromino> currentTetro;

  // checks if row at rowIndex is full
  bool isRowFull(size_t rowIndex) const;

  // returns -1 if there are no full rows
  int getIndexOfFullRow() const;

  // drop the above row(s) once a row is full
  void dropRows(size_t row);

  bool generalizedLateralBlockCheck(/*size_t column = 0, */int lr = 0);

  bool rotationCheck(AbstractTetromino &temp);

  // checks if moving/rotating current tetromino in the direction dir is possible
  bool isBlocked(Direction dir);

  bool isTextOnly() const;
  
  public:
  std::shared_ptr<TextDisplay> getTextDisplay();
  std::shared_ptr<GraphicsDisplay> getGraphicsDisplay();

  void setCurrentTetromino(std::shared_ptr<AbstractTetromino> tetro);
  std::shared_ptr<AbstractTetromino> getCurTetro() {
    return currentTetro;
  }

  Info getInfo() const {
    Info info {0, 0, TetroType::None};
    return info;
  }

  // initializes theBoard
  void init(size_t rows, size_t cols, size_t reservedRows, bool textonly);

  // moves current tetromino one cell in the direction dir
  void move(Direction dir);

  // hard drop the current tetromino
  void dropTetromino();

  /* checks if there is space for the block to be
   * put in the top left corner.
   * If there isn't, the game ends. */
  bool isTopLeftBlocked() const;

  ~Board();

  friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif

