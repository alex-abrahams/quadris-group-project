#ifndef TETBLO_H
#define TETBLO_H
#include "abstracttetromino.h"

class TetrominoBlock : public AbstractTetromino {
	size_t row;
  size_t col; // location of bottom left
	
  size_t height;
	size_t width; // dimensions of tetromino
	
  size_t id;
  TetroType type;
  std::vector<std::vector<Cell>> cells;


  public: 


  ~TetrominoBlock();
  TetrominoBlock(size_t w, size_t h, size_t r, size_t c, size_t id, TetroType t);
  void setCell(size_t r, size_t c);
  size_t lowerLeftRowIdx();
  size_t lowerRightRowIdx();
  
  TetroType getType() override;
  size_t getHeight() override;
  size_t getWidth() override;
  size_t getLocationRow() override;
  size_t getLocationCol() override;
  size_t getID();
  void setID(size_t id);
  void setLocationRow(size_t r) override;
  void setLocationCol(size_t c) override;
  // changes the location of this tetromino object's cell on the board
  void setCellPosn(size_t rowAt, size_t colAt, size_t newRow, size_t newCol) override;
  Info getCellInfo(size_t row, size_t col) override;
  Cell getCell(size_t row, size_t col) override;

  void rotateCW() override;
  void rotateCCW() override;
  void rotate(bool clockwise);
};

#endif


