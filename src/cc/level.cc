#include "level.h"

  Level0::Level0(std::vector<std::string> i){
    norand(i);
  }

  void Level0::norand(std::vector<std::string> i ){
    for(std::string t : i)
      q.emplace(utility::strToTet(t));
  }



  std::shared_ptr<TetrominoBlock> Level0::getNextBlock(){
    if(q.size() == 0)return GameSingleton::get().makeBlock(TetroType::None);
    std::shared_ptr<TetrominoBlock> t = GameSingleton::get().makeBlock(q.front());
    q.pop();
    return t;
  }

RandomDecorator::RandomDecorator(std::string dat, std::shared_ptr<Level> p){
  prev = p;
  prev->passthrough = true;
  std::istringstream ss(dat);
  int t;
  for(int i = 0; i < 7; i++){
    ss >> t;
    vals[i] = max + t;
    max += t;
  }
}

std::shared_ptr<TetrominoBlock> RandomDecorator::getNextBlock() {
  if(passthrough && !rng) return prev->getNextBlock();
  int t = rand() % max;
  for(int i = 0 ; i < 7; i++)
    if(vals[i] > t)
      return GameSingleton::get().makeBlock(static_cast<TetroType>(i));
  return nullptr;
}

HeavyDecorator::HeavyDecorator(std::shared_ptr<Level> t){
  prev = t;
  prev->passthrough = true;
}


void HeavyDecorator::notify(Publisher<Info, NotifFrom> &whon){
  if(whon.getNotifFrom().from == FromType::Move && whon.getNotifFrom().d != Direction::Down)
    GameSingleton::get().down();
  prev->notify(whon);
}

MiddleDecorator::MiddleDecorator(std::shared_ptr<Level> t){
  prev = t;
  prev->passthrough = true;
}

void MiddleDecorator::notify(Publisher<Info, NotifFrom> &who){
  if(who.getNotifFrom().from == FromType::Drop)
    if(!(++numdrops % 5))GameSingleton::get().dropMiddle();
  prev->notify(who);
}
