#include "textdisplay.h"
#include "publisher.h"
#include "gamesingleton.h"
#include <iostream>

TextDisplay::TextDisplay(int height, int width): gridWidth{width}, gridHeight{height} {
  for (int i = 0; i < height; i++) {
    theDisplay.push_back( std::vector<char>() );
    for (int j = 0; j < width; j++) {
      theDisplay.at(i).push_back(' ');
    }
  }
}

void TextDisplay::setNextTetromino(std::shared_ptr<AbstractTetromino> tetro) {
  nextTetro = tetro; 
}

void TextDisplay::notify(Publisher<Info, NotifFrom> &whoNotified) {

  NotifFrom fr = whoNotified.getNotifFrom();

  if (fr.from == FromType::Cell) {
    theDisplay.at(whoNotified.getInfo().row).at(whoNotified.getInfo().col) = 
     // (char)((dynamic_cast<Cell&>(whoNotified)).getID()+'0');
	blockChars[whoNotified.getInfo().type];
  } 
  else if (fr.from == FromType::Game) {
    this->score = fr.rowsScore + fr.blocksClearedScore;
    this->hiScore = fr.hiscore;
    this->level  = fr.level;
  } else {
//    std::cout << "TextDisplay::notify() -> IDK who notified" << std::endl;
  }
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  return out; 
}

void TextDisplay::draw(std::ostream &out, std::shared_ptr<AbstractTetromino> currentTetromino) {
  out << "Level: " << level << std::endl; // show level
  out << "Score: " << score << std::endl; // show score
  out << "Hi Score: " << hiScore << std::endl; // show hiscore

  for (int i = 0; i < gridWidth; i++) {
    out << "-"; // line of dashes
  }

  out << std::endl;

  // make temporary vector for display
  std::vector<std::vector<char>> realDisplay;

  for (int r = 0; r < gridHeight; r++) {
    realDisplay.push_back( std::vector<char>() );
    for (int c = 0; c<gridWidth; c++) {
      realDisplay.at(r).push_back(theDisplay.at(r).at(c));
    }
  }

  if (currentTetromino) {
    // put in the tetromino to this display vector
    for (size_t r = 0; r < currentTetromino->getHeight(); r++) {      
      for (size_t c = 0; c < currentTetromino->getWidth(); c++) {         
        if (currentTetromino->getCellInfo(r,c).type != TetroType::None) {
          realDisplay.at(currentTetromino->getLocationRow() - currentTetromino->getHeight() + 1 + r).
            at(currentTetromino->getLocationCol() + c) = blockChars[currentTetromino->getType()];
        }
      }
    }

  }

  for (int r = 0; r < gridHeight; r++) {
    for (int c = 0; c < gridWidth; c++) {
      out << realDisplay.at(r).at(c); // draw the display
    }
    out << std::endl;
  }

  for (int i = 0; i < gridWidth; i++) {
    out << "-"; // line of dashes
  }

  out << std::endl;
  out << "Next:" << std::endl;

  if (nextTetro) {
    // show the next tetromino
    for (size_t r = 0; r < nextTetro->getHeight(); r++) {
      for (size_t c = 0; c < nextTetro->getWidth(); c++) {
        if (nextTetro->getCellInfo(r,c).type != TetroType::None) {
          out << blockChars[nextTetro->getType()];
        } else {
          out << " ";
        }
      }
    out << std::endl;
	  }
  }
}







