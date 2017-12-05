#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <vector>
#include <map>
#include <memory>
#include "observer.h"
#include "abstracttetromino.h"
#include "info.h"
#include "notiffrom.h"
class Cell;


class TextDisplay: public Observer<Info, NotifFrom> {
	std::vector<std::vector<char>> theDisplay; // theDisplay.at(row).at(col) to access
  std::shared_ptr<AbstractTetromino> nextTetro;
  const int gridWidth;
	const int gridHeight;

	std::map< TetroType, char > blockChars 
	{
		{ TetroType::IBlock,    'I' },
		{ TetroType::JBlock,    'J' },
		{ TetroType::LBlock,    'L' },
		{ TetroType::SBlock,    'S' },
		{ TetroType::ZBlock,    'Z' },
		{ TetroType::ZeroBlock, '0' },
		{ TetroType::TBlock,    'T' },
		{ TetroType::None,      ' ' },
		{ TetroType::OneBlock,  '*' }
	}; // the characters corresponding to each piece type

  int score = 0;
	int hiScore = 0;
	int level = 0;	
	
  public:
	
	TextDisplay(int h, int w); // constructor
  
  void setNextTetromino(std::shared_ptr<AbstractTetromino> tetro);
  
	void notify(Publisher<Info, NotifFrom> &whoNotified) override; // gets stuff from cells or from game singleton
	
	void draw(std::ostream &out, std::shared_ptr<AbstractTetromino> currentTetromino = nullptr/*, std::shared_ptr<AbstractTetromino> nextPiece = nullptr*/); // draw the display
};

#endif


