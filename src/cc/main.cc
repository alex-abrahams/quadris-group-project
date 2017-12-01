#include "cmdparser.h"
#include "gamesingleton.h"
#include <iostream>

int main() {
	GameSingleton gs;
	gs.init();
  gs.start();
	std::cout << gs;
}
