#include <iostream>
#include "graphicsdisplay.h"
#include "publisher.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int gridHeight, int gridWidth, int winHeight, int winWidth):
 gridHeight{gridHeight}, gridWidth{gridWidth}, winHeight{winHeight}, winWidth{winWidth}, gameWidth{winWidth/2}, xw{winWidth, winHeight} {
	for (int i = 0; i < gridHeight; i++) {
		theDisplay.push_back( std::vector<TetroType>() );
		for (int j = 0; j < gridWidth; j++) {
			theDisplay.at(i).push_back(TetroType::None);
		}
	}
	xw.fillRectangle(0, 0, winWidth, winHeight, Xwindow::Black);
}


void GraphicsDisplay::notify(Publisher<Info, NotifFrom> &whoNotified) {
	NotifFrom fr = whoNotified.getNotifFrom();
	if (fr.from == FromType::Cell) {
		// ¯\_(ツ)_/¯
	} else if (fr.from == FromType::Game) {
		std::cout << "GraphicsDisplay::notify() -> Game notified" << std::endl;
		this->score = fr.rowsScore + fr.blocksClearedScore;
		this->hiScore = fr.hiscore;
		this->level  = fr.level;
	} else {
		std::cout << "GraphicsDisplay::notify() -> IDK who notified lol" << std::endl;
	}
}

void GraphicsDisplay::draw(std::shared_ptr<AbstractTetromino> currentTetromino) {
	int cellWidth = gameWidth / gridWidth;
	int cellHeight = winHeight / gridHeight;
	for (int r = 0; r < gridHeight; r++) {
		for (int c = 0; c < gridWidth; c++) {
			switch(theDisplay.at(r).at(c)) {
				case TetroType::IBlock:
					xw.fillRectangle(c * cellWidth, r * cellHeight, cellWidth, cellHeight, Xwindow::White);
					break;
				case TetroType::JBlock:
					xw.fillRectangle(c * cellWidth, r * cellHeight, cellWidth, cellHeight, Xwindow::Red);
					break;
				case TetroType::LBlock:
					xw.fillRectangle(c * cellWidth, r * cellHeight, cellWidth, cellHeight, Xwindow::Blue);
					break;
				case TetroType::SBlock:
					xw.fillRectangle(c * cellWidth, r * cellHeight, cellWidth, cellHeight, Xwindow::Green);
					break;
				case TetroType::ZBlock:
					xw.fillRectangle(c * cellWidth, r * cellHeight, cellWidth, cellHeight, Xwindow::Yellow);
					break;
				case TetroType::ZeroBlock:
					xw.fillRectangle(c * cellWidth, r * cellHeight, cellWidth, cellHeight, Xwindow::Orange);
					break;
				case TetroType::TBlock:
					xw.fillRectangle(c * cellWidth, r * cellHeight, cellWidth, cellHeight, Xwindow::Pink);
					break;
				default:
					xw.fillRectangle(c * cellWidth, r * cellHeight, cellWidth, cellHeight, Xwindow::Black);
					break;
			}
		}
	}
}

