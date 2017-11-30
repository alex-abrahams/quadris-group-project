#ifndef GAMESINGLETON_H
#define GAMESINGLETON_H
#include <string>
#include "board.h"

class GameSingleton {
  GameSingleton();
  Board *theBoard = nullptr;
  size_t score = 0;
  size_t hiscore = 0;
  size_t level = 0;
  
  public:

  static GameSingleton& get();

  void init();

  //control interfaces
  void down();
  void left();
  void right();
  void clockwise();
  void counterclockwise();
  void drop();
  void levelup();
  void leveldown();
  void norandom(std::string file);
  void sequence(std::string file);
  void restart();
  void hint();

  // change current tetromino
  void I();
  void L();
  void J();
  void Zero();
  void S();
  void Z();
  void T();

};
#endif

