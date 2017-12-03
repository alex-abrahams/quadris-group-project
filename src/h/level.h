#ifndef LEVEL_H
#define LEVEL_H
#include "info.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <queue>
#include "utility.h"
#include "gamesingleton.h"
class Level{
  bool rng = true;
  public:
  virtual std::shared_ptr<TetrominoBlock> getNextBlock(){return nullptr;};
  virtual void droppedBlock(){};
  virtual void norand(std::vector<std::string> i){};
};

class Level0 : public Level{
  public:
  std::queue<TetroType> q;
  Level0(std::vector<std::string> i);
  std::shared_ptr<TetrominoBlock> getNextBlock() override;
  void droppedBlock() override;
  void norand(std::vector<std::string> i) override;
};
#endif
