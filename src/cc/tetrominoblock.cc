#include "tetrominoblock.h"

#include <iostream> // testing
TetrominoBlock::TetrominoBlock(size_t w, size_t h, size_t r, size_t c, size_t id, TetroType t)
  : row{r}, col{c}, height{h}, width{w}, id{id}, type{t} {
    for (size_t rr = 0; rr < h; ++rr) {
      cells.push_back(std::vector<Cell>());
      for (size_t cc = 0; cc < width; ++cc) {
        cells.at(rr).emplace_back(r - h + 1 + rr, c + cc, id);
      }
    }
  }

TetrominoBlock::~TetrominoBlock() {}

void TetrominoBlock::setCell(size_t r, size_t c) {
  cells.at(r).at(c) = Cell(row - height + 1 + r, col + c, id, type);
}

size_t lowerLeftRowIdx() {
  return 0;
}
size_t lowerRightRowIdx() {
  return 0;
}

TetroType TetrominoBlock::getType()  {
  return type;
}

size_t TetrominoBlock::getHeight() {
  return height;
}

size_t TetrominoBlock::getWidth()  {
  return width;
}

size_t TetrominoBlock::getLocationRow()  {
  return row;
}

size_t TetrominoBlock::getLocationCol()  {
  return col;
}

void TetrominoBlock::setCellPosn(size_t rowAt, size_t colAt, size_t newRow, size_t newCol)  {
  if (cells.size() > rowAt && cells.at(rowAt).size() > colAt) {
    cells.at(rowAt).at(colAt).setRowCol(newRow, newCol); 
  }
}

Info TetrominoBlock::getCellInfo(size_t row, size_t col)  {
  return cells.at(row).at(col).getInfo();
}

Cell TetrominoBlock::getCell(size_t row, size_t col)  {
  return cells.at(row).at(col);
}

void TetrominoBlock::setLocationRow(size_t r) {
  row = r;
}

void TetrominoBlock::setLocationCol(size_t c) {
  col = c;
}

void TetrominoBlock::rotate(bool clockwise) {
  if (width == height) return; // no need to rotate a square
  size_t newHeight = width;
  size_t newWidth = height;
  std::vector<std::vector<Cell>> temp;

  for (size_t row = 0; row < newHeight; ++row) {
    temp.push_back(std::vector<Cell>());
    temp.at(row).resize(newWidth); 
  }

  // iterate through the current
  // set each row to a column in the temp according to
  // row i in current -> col in temp at height - i - 1
  for (size_t row = 0; row < height; ++row) {
    std::vector<Cell> rowElements = cells.at(row); // these become the column in the temp

    // rowElements.size() == newHeight

    // set elements of a column in temp
    // goes through each row in temp at fixed column height - row - 1
    for (size_t rowTemp = 0; rowTemp < newHeight; ++rowTemp) {

        int rotationRow = 0;
        int rotationCol = 0;


      if (clockwise) {
        temp.at(rowTemp).at(height - row - 1) = rowElements.at(rowTemp);
        
        int curCol = static_cast<int>(temp.at(rowTemp).at(height - row - 1).getInfo().col);
        int curRow = static_cast<int>(temp.at(rowTemp).at(height - row - 1).getInfo().row);
        
        if (height > width) {
          rotationRow = cells.at(height - 1).at(0).getInfo().row;
          rotationCol = cells.at(height - 1).at(0).getInfo().col;
        } else if (width > height) {
          rotationRow = cells.at(height - 1).at(0).getInfo().row - 1;
          rotationCol = cells.at(height - 1).at(0).getInfo().col + 1; // rotate about this location

        }

        int newCol = rotationRow + rotationCol - curRow; 
        int newRow = rotationRow - rotationCol + curCol; 
        if (height > width) newRow -= 1;
        
        if (type == TetroType::IBlock && width > height) newRow -= 1;
        else if (type == TetroType::IBlock && width < height) newRow += 1;

        temp.at(rowTemp).at(height - row - 1).setRowCol(static_cast<size_t>(newRow), static_cast<size_t>(newCol));
      } else if (!clockwise) { // COUNTERCLOCKWISE 
        temp.at(rowTemp).at(row) = rowElements.at(newHeight - rowTemp - 1);

        int curCol = static_cast<int>(temp.at(rowTemp).at(row).getInfo().col);
        int curRow = static_cast<int>(temp.at(rowTemp).at(row).getInfo().row);
        
        rotationRow = cells.at(height - 1).at(0).getInfo().row - 1;
        rotationCol = cells.at(height - 1).at(0).getInfo().col + 1;

        int newCol = rotationCol - rotationRow + curRow;
        int newRow = rotationCol + rotationRow - curCol;
        if (height < width) newCol -= 1;
        
        if (type == TetroType::IBlock && width > height) newCol -= 1;
        else if (type == TetroType::IBlock && width < height) newCol += 1;

        temp.at(rowTemp).at(row).setRowCol(static_cast<size_t>(newRow), static_cast<size_t>(newCol));

      }
    }
  }

  cells = temp;
  height = newHeight;
  width = newWidth;
  row = temp.at(newHeight - 1).at(0).getInfo().row;
  col = temp.at(newHeight - 1).at(0).getInfo().col;

}

void TetrominoBlock::rotateCW() {
  rotate(true);
}

void TetrominoBlock::rotateCCW() {
  rotate(false);
}

size_t TetrominoBlock::getID() {
	return id;
}
void TetrominoBlock::setID(size_t id) {
	this->id = id;
	for(auto &i : cells){
		for(auto &b : i){
			b.setID(id);
		}
	}
}


