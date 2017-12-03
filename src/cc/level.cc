#include "level.h"

  Level0::Level0(std::vector<std::string> i){
    norand(i);
  }

  void Level0::norand(std::vector<std::string> i ){
    for(std::string t : i)
      q.emplace(utility::strToTet(t));
  }

  void Level0::droppedBlock()  {}

  std::shared_ptr<TetrominoBlock> Level0::getNextBlock(){
    if(q.size() == 0)return GameSingleton::get().makeBlock(TetroType::None);
    std::shared_ptr<TetrominoBlock> t = GameSingleton::get().makeBlock(q.front());
    q.pop();
    return t;
  }
