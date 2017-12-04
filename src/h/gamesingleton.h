#ifndef GAMESINGLETON_H
#define GAMESINGLETON_H

#include <string>
#include "board.h"
#include "notiffrom.h"
#include <iostream> // for testing
#include "cmdparser.h"
#include "gameoverexception.h"
#include <utility>
#include "utility.h"
#include "level.h"
class Level;
class TetrominoFactory;

class GameSingleton : public Publisher<Info, NotifFrom> {
  Board theBoard;
  std::string levelFile = "levels.txt";
  size_t rowsScore = 0, blocksClearedScore = 0, hiscore = 0, level = 0;

  std::vector<std::shared_ptr<Level>> levels;


  bool textonly;
  std::unique_ptr<TetrominoFactory> tetroFactory;
  std::shared_ptr<AbstractTetromino> current;
  std::shared_ptr<AbstractTetromino> next;
  std::shared_ptr<TextDisplay> td;
  std::shared_ptr<GraphicsDisplay> gd;

  bool gameRunning = false;

  GameSingleton() {} // disable ctors
  GameSingleton(GameSingleton const &other);
  GameSingleton &operator=(GameSingleton const &other)=default;
  std::shared_ptr<Level> getZLevel(std::string file);
  std::vector<std::shared_ptr<Level>> generateLevels(std::vector<std::string> i);
  
  static std::shared_ptr<GameSingleton> ins;
  
  public:
  CommandParser cmdp;
  void endGame(bool hard = false, std::string msg = "Unknown");

  static GameSingleton& get(bool reset=false) {
    if(reset || ins == nullptr) ins = std::shared_ptr<GameSingleton>(new GameSingleton());
    return *ins;
  }



  void init(std::string i, int a, bool tonly, size_t hs);
  std::shared_ptr<TetrominoBlock> makeBlock(TetroType i){
    return tetroFactory->makeTetromino(i);
  }

  // pure virtual definition from Publisher
  Info getInfo() const {
    Info info {0, 0, TetroType::None};
    return info;
  }

  // accessors
  size_t getCurrentID();
  size_t getRowsScore();
  size_t getBlocksClearedScore();
  size_t getHiScore();
  size_t getLevel();
  void setRowsScore(size_t s);
  void setBlocksClearedScore(size_t s);
  void setHiScore(size_t h);
  void setLevel(size_t l);
  // need textdisplay pointer attached to cells of tetromino. Used in
  // tetrominoblock when setting up
  std::shared_ptr<TextDisplay> getTextDisplay();
  std::shared_ptr<GraphicsDisplay> getGraphicsDisplay();

  void start();

  void dropMiddle();
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



