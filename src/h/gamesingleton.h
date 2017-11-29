#ifndef GAMESINGLETON_H
#define GAMESINGLETON_H
#include <string>

class GameSingleton {
  GameSingleton();
  Board b;
  public:
  
  static GameSingleton& get(){
    static GameSingleton r;
    return r;
  }

  void init();

  //control interfaces
  void down();
  void up();
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
