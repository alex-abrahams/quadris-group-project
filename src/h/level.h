#ifndef LEVEL_H
#define LEVEL_H
#include "info.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include "utility.h"
#include "gamesingleton.h"
#include "notiffrom.h"
#include "info.h"
#include "observer.h"
class Level : public Observer<Info, NotifFrom> {
  public:
  bool isSelected = false;
  bool rng = true;
  bool passthrough = false;

  void notify(Publisher<Info, NotifFrom> &whoN) override {};
  virtual std::shared_ptr<TetrominoBlock> getNextBlock(){return nullptr;};
  virtual void norand(std::vector<std::string> i){};
};

class Level0 : public Level{
  public:
  std::queue<TetroType> q;
  Level0(std::vector<std::string> i);
  std::shared_ptr<TetrominoBlock> getNextBlock() override;
  void norand(std::vector<std::string> i) override;
};

class LevelDecorator : public Level{
  protected:
  std::shared_ptr<Level> prev;
  public:
  void notify(Publisher<Info, NotifFrom> &whon){prev->notify(whon);};
  virtual std::shared_ptr<TetrominoBlock> getNextBlock() override{return nullptr;};
  virtual void norand(std::vector<std::string> i){};
  void rnd(){rng = true;};
};

class RandomDecorator : public LevelDecorator {
  int max = 0;
  int vals[7] = {0,0,0,0,0,0,0};
  protected:
  public:
  RandomDecorator(std::string data, std::shared_ptr<Level> p);
  std::shared_ptr<TetrominoBlock> getNextBlock() override;
  void norand(std::vector<std::string> i){rng = false; prev->norand(i);};
};

class HeavyDecorator : public LevelDecorator {
  public:
  HeavyDecorator(std::shared_ptr<Level> p);
  std::shared_ptr<TetrominoBlock> getNextBlock(){return prev->getNextBlock();};
  void notify(Publisher<Info, NotifFrom> &whon) override;
  void norand(std::vector<std::string> i){prev->norand(i);};
};

class MiddleDecorator : public LevelDecorator {
  int numdrops = 0;
  public:
  MiddleDecorator(std::shared_ptr<Level> p);
  std::shared_ptr<TetrominoBlock> getNextBlock(){return prev->getNextBlock();};
  void notify(Publisher<Info, NotifFrom> &whon) override;
  void norand(std::vector<std::string> i){prev->norand(i);};
};

#endif

