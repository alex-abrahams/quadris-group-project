#ifndef GAMESINGLETON_H
#define GAMESINGLETON_H

#include <string>
#include "board.h"
#include "notiffrom.h"

#include <iostream> // for testing
#include "cmdparser.h"
class TetrominoFactory;

class GameSingleton : public Publisher<Info, NotifFrom> {
  Board theBoard;
  size_t score = 0, hiscore = 0, level = 0;
  
  CommandParser cmdp;

  std::unique_ptr<TetrominoFactory> tetroFactory;
  std::shared_ptr<AbstractTetromino> current;
  std::shared_ptr<AbstractTetromino> next;
  std::shared_ptr<TextDisplay> td;  

  bool gameRunning = false;

  public:

  GameSingleton();
  static GameSingleton& get();  

  void init();

  // pure virtual definition from Publisher
  Info getInfo() const {
    Info info {0, 0, TetroType::None};
    return info;
  }

  // accessors
  size_t getScore();
  size_t getHiScore();
  size_t getLevel();

  void start();
  
  // control functions
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

  // change current tetromino (for testing)
  void I();
  void L();
  void J();
  void Zero();
  void S();
  void Z();
  void T();

  friend std::ostream &operator<<(std::ostream &out, const GameSingleton &gs);

};
#endif

