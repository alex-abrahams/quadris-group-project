#include <iostream>
#include "graphicsdisplay.h"
#include "publisher.h"
#include <sstream>
#include <string>
using namespace std;

GraphicsDisplay::GraphicsDisplay(int gridHeight, int gridWidth, int winHeight, int winWidth):
 gridHeight{gridHeight}, gridWidth{gridWidth}, winHeight{winHeight}, winWidth{winWidth}, gameWidth{(winWidth*2)/3}, xw{winWidth, winHeight} {
	for (int i = 0; i < gridHeight; i++) {
		theDisplay.push_back( std::vector<TetroType>() );
		for (int j = 0; j < gridWidth; j++) {
			theDisplay.at(i).push_back(TetroType::None);
		}
	}
	xw.fillRectangle(0, 0, winWidth, winHeight, Xwindow::Black);
}

void GraphicsDisplay::setNextTetromino(std::shared_ptr<AbstractTetromino> tetro) {
  nextTetro = tetro; 
}

void GraphicsDisplay::notify(Publisher<Info, NotifFrom> &whoNotified) {
	NotifFrom fr = whoNotified.getNotifFrom();
	if (fr.from == FromType::Cell) {
		theDisplay.at(whoNotified.getInfo().row).at(whoNotified.getInfo().col) = whoNotified.getInfo().type;
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
	std::vector<std::vector<TetroType>> realDisplay;
	for (int r = 0; r < gridHeight; r++) {
		realDisplay.push_back( std::vector<TetroType>() );
		for (int c = 0; c<gridWidth; c++) {
			realDisplay.at(r).push_back(theDisplay.at(r).at(c));
		}
	}
	if (currentTetromino) {
		// put in the tetromino to this display vector
		for (size_t r = 0; r < currentTetromino->getHeight(); r++) {
			for (size_t c = 0; c < currentTetromino->getWidth(); c++) {
				if (currentTetromino->getCellInfo(r,c).type != TetroType::None) {
					realDisplay.at(currentTetromino->getLocationRow() - currentTetromino->getHeight() + 1 + r).at(currentTetromino->getLocationCol() + c) = currentTetromino->getType();
				}
			}
		}
	}
	int cellWidth = gameWidth / gridWidth;
	int cellHeight = winHeight / gridHeight;
	for (int r = 0; r < gridHeight; r++) {
		for (int c = 0; c < gridWidth; c++) {
			switch(realDisplay.at(r).at(c)) {
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
	xw.fillRectangle(gameWidth+5, 0, winWidth-(gameWidth+5), winHeight, Xwindow::White);
	stringstream s, h, l;
	s << "Score: " << score;
	h << "Hi Score: " << hiScore;
	l << "Level: " << level;
	xw.drawString(gameWidth+20, 100, s.str());
	xw.drawString(gameWidth+20, 150, h.str());
	xw.drawString(gameWidth+20, 200, l.str());
	
	if (nextTetro) {
		// show the next tetromino
		for (size_t r = 0; r < nextTetro->getHeight(); r++) {
			for (size_t c = 0; c < nextTetro->getWidth(); c++) {
				switch(nextTetro->getCellInfo(r,c).type) {
					case TetroType::IBlock:
						xw.fillRectangle(gameWidth + 20 + c * 20, 250 + r * 20, 20, 20, Xwindow::Black);
						break;
					case TetroType::JBlock:
						xw.fillRectangle(gameWidth + 20 + c * 20, 250 + r * 20, 20, 20, Xwindow::Red);
						break;
					case TetroType::LBlock:
						xw.fillRectangle(gameWidth + 20 + c * 20, 250 + r * 20, 20, 20, Xwindow::Blue);
						break;
					case TetroType::SBlock:
						xw.fillRectangle(gameWidth + 20 + c * 20, 250 + r * 20, 20, 20, Xwindow::Green);
						break;
					case TetroType::ZBlock:
						xw.fillRectangle(gameWidth + 20 + c * 20, 250 + r * 20, 20, 20, Xwindow::Yellow);
						break;
					case TetroType::ZeroBlock:
						xw.fillRectangle(gameWidth + 20 + c * 20, 250 + r * 20, 20, 20, Xwindow::Orange);
						break;
					case TetroType::TBlock:
						xw.fillRectangle(gameWidth + 20 + c * 20, 250 + r * 20, 20, 20, Xwindow::Pink);
						break;
					default:
						xw.fillRectangle(gameWidth + 20 + c * 20, 250 + r * 20, 20, 20, Xwindow::White);
						break;
				}
			}
		}
	}
}

