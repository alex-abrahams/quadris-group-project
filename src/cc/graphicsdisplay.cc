#include <iostream>
#include "graphicsdisplay.h"
#include "publisher.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int gridHeight, int gridWidth, int winHeight, int winWidth):
 gridHeight{gridHeight}, gridWidth{gridWidth}, winHeight{winHeight}, winWidth{winWidth}, gameWidth{winWidth/2}, xw{winWidth, winHeight} {
  xw.fillRectangle(0, 0, winWidth, winHeight, Xwindow::Black);
}


void GraphicsDisplay::notify(Publisher<Info, NotifFrom> &whoNotified) {
	NotifFrom fr = whoNotified.getNotifFrom();
	if (fr.from == FromType::Cell) {
		auto info = whoNotified.getInfo();
		int cellWidth = gameWidth / gridWidth;
		int cellHeight = winHeight / gridHeight;
		switch(info.type) {
			case TetroType::IBlock:
				xw.fillRectangle(info.col * cellWidth, info.row * cellHeight, cellWidth, cellHeight, Xwindow::White);
				break;
			case TetroType::JBlock:
				xw.fillRectangle(info.col * cellWidth, info.row * cellHeight, cellWidth, cellHeight, Xwindow::Red);
				break;
			case TetroType::LBlock:
				xw.fillRectangle(info.col * cellWidth, info.row * cellHeight, cellWidth, cellHeight, Xwindow::Blue);
				break;
			case TetroType::SBlock:
				xw.fillRectangle(info.col * cellWidth, info.row * cellHeight, cellWidth, cellHeight, Xwindow::Green);
				break;
			case TetroType::ZBlock:
				xw.fillRectangle(info.col * cellWidth, info.row * cellHeight, cellWidth, cellHeight, Xwindow::Yellow);
				break;
			case TetroType::ZeroBlock:
				xw.fillRectangle(info.col * cellWidth, info.row * cellHeight, cellWidth, cellHeight, Xwindow::Orange);
				break;
			case TetroType::TBlock:
				xw.fillRectangle(info.col * cellWidth, info.row * cellHeight, cellWidth, cellHeight, Xwindow::Pink);
				break;
			default:
				xw.fillRectangle(info.col * cellWidth, info.row * cellHeight, cellWidth, cellHeight, Xwindow::Black);
				break;
		}
	} else if (fr.from == FromType::Game) {
		std::cout << "GraphicsDisplay::notify() -> Game notified" << std::endl;
		this->score = fr.rowsScore + fr.blocksClearedScore;
		this->hiScore = fr.hiscore;
		this->level  = fr.level;
	} else {
		std::cout << "GraphicsDisplay::notify() -> IDK who notified lol" << std::endl;
	}
}

