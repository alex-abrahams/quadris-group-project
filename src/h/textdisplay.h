#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <vector>
#include <map>
#include "observer.h"
#include "abstracttetromino.h"
#include "info.h"

class Cell;

class TextDisplay: public Observer<Info> {
	std::vector<std::vector<char>> theDisplay; // theDisplay.at(row).at(col) to access
	const int gridWidth;
	const int gridHeight;
	const map<TetroType,char> blockChars; // the characters corresponding to each piece type
	
	public:
	
	TextDisplay(int h, int w); // constructor
	
	void notify(Publisher<Info> &whoNotified) override; // gets stuff from cells
	
	void draw(std::ostream &out, int level, int score, int hiScore, AbstractTetromino currentTetromino, AbstractTetromino nextPiece); // draw the display
};

#endif
