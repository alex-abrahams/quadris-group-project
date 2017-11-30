#include "cmdparser.h"
#include "gamesingleton.h"

int main() {
	GameSingleton *gs = new GameSingleton();
	gs->init();
	cout << gs->theBoard;
}
