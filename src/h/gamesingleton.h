#ifndef GAMESINGLETON_H
#define GAMESINGLETON_H
#include <string>

class GameSingleton {
  GameSingleton();
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
