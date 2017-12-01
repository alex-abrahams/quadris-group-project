#include "cmdparser.h"
#include "gamesingleton.h"
#include <iostream>

int main() {
  GameSingleton::get().init();
  GameSingleton::get().start();
	std::cout << GameSingleton::get();
}
