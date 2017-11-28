#include "textdisplay.h"
#include "subject.h"


TextDisplay::TextDisplay(int h, int w): gridHeight{h}, gridWidth{w} {
	for (int i = 0; i < h; i++) {
		theDisplay.push_back( std::vector<char>() );
		for (int j = 0; j < w; j++) {
			theDisplay.at(i).push_back(' ');
		}
	}
}
void TextDisplay::notify(Publisher<Info> &whoNotified) {
	theDisplay.at(whoNotified.getInfo().row).at(whoNotified.getInfo().col) = blockChars[whoNotified.getInfo().type];
}

void TextDisplay::draw(std::ostream &out, int level, int score, int hiScore, AbstractTetromino currentTetromino, AbstractTetromino nextPiece) {
	out << "Level: " << level << std::endl; // show level
	out << "Score: " << score << std::endl; // show score
	out << "Hi Score: " << hiScore << std::endl; // show hiscore
	for (int i=0; i<gridWidth; i++) {
		out << "-"; // line of dashes
	}
	out << std::endl;
	// make temporary vector for display
	std::vector<std::vector<char>> realDisplay;
	for (int r=0; r<h; r++) {
		realDisplay.push_back( std::vector<char>() );
		for (int c=0; c<w; c++) {
			realDisplay.at(r).push_back(theDisplay.at(r).at(c));
		}
	}
	// put in the tetromino to this display vector
	for (int r = 0; r < currentTetromino.getHeight(); r++) {
		for (int c = 0; c < currentTetromino.getWidth(); c++) {
			if (currentTetromino.getCellLocations().at(r).at(c).getInfo().type != TetroType::None) {
				realDisplay.at(currentTetromino.getLocationRow() - currentTetromino.getHeight() + 1 + r).at(currentTetromino.getLocationCol() + c) = blockChars[currentTetromino.getType()];
			}
		}
	}
	
	for (int r=0; r<h; r++) {
		for (int c=0; c<w; c++) {
			out << realDisplay.at(r).at(c) // draw the display
		}
		out << std::endl;
	}
	
	for (int i=0; i<gridWidth; i++) {
		out << "-"; // line of dashes
	}
	out << std::endl;
	out << "Next:" << std::endl;
	
	// show the next tetromino
	for (int r = 0; r < nextPiece.getHeight(); r++) {
		for (int c = 0; c < nextPiece.getWidth(); c++) {
			if (nextPiece.getCellLocations().at(r).at(c).getInfo().type != TetroType::None) {
				out << blockChars[nextPiece.getType()];
			} else {
				out << " ";
			}
		}
		out << std::endl;
	}
}
