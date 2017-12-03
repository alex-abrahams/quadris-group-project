#include "gamesingleton.h"
#include "tetrominofactory.h"
#include "textdisplay.h"

std::unique_ptr<Level> getZLevel(){
  return nullptr;
}

std::vector<std::unique_ptr<Level>> generateLevels(std::vector<std::string> i);

void GameSingleton::init(std::string file, int dlevel, bool textonly) {
  level = dlevel;

  theBoard.init(15, 11, 3);
  //initlevels
  levels.push_back(std::unique_ptr<Level>(new Level0(utility::bufferFile(file))));
  //generateLevels(utility::bufferFile(levelFile));
  td = theBoard.getTextDisplay();
  this->attach(td);

  tetroFactory = std::make_unique<TetrominoFactory>();
  current = levels.at(level)->getNextBlock();
  next = levels.at(level)->getNextBlock();
  theBoard.setCurrentTetromino(current);

  td->setNextTetromino(next);

  NotifFrom notifFrom {FromType::Game, score, hiscore, level};
  this->setNotifFrom(notifFrom);
  this->notifyObservers();
  this->cmdp = CommandParser{};
  gameRunning = true;
}


std::shared_ptr<TextDisplay> GameSingleton::getTextDisplay() {
  return td;
}

void GameSingleton::start(){
  std::cout << *this;
  while(gameRunning){
    cmdp.nextCommand();
    std::cout << *this;
  }
}

void GameSingleton::dropMiddle(){

}

void GameSingleton::down(){
  theBoard.move(Direction::Down);
}
void GameSingleton::left(){
  theBoard.move(Direction::Left);
}

void GameSingleton::right(){
  theBoard.move(Direction::Right);
}

void GameSingleton::clockwise(){
  theBoard.move(Direction::CW);
}

void GameSingleton::counterclockwise(){
  theBoard.move(Direction::CCW);
}

void GameSingleton::drop(){
	theBoard.dropTetromino();
  current = next;
  next = tetroFactory->makeTetromino(TetroType::TBlock);
  theBoard.setCurrentTetromino(current);
  td->setNextTetromino(next);
}

void GameSingleton::levelup(){
  level += 1;
  if(level >= levels.size()) level = levels.size()-1;
  NotifFrom notifFrom {FromType::Game, score, hiscore, level};
  this->setNotifFrom(notifFrom);
  this->notifyObservers();
}

void GameSingleton::leveldown(){
  // TODO: didnt work
  if (level > 0) {
    --level;
    NotifFrom notifFrom {FromType::Game, score, hiscore, level};
    this->setNotifFrom(notifFrom);
    this->notifyObservers();
  }
}

void GameSingleton::norandom(std::string file){
  levels.at(level)->norand(utility::bufferFile(file));
}

void GameSingleton::sequence(std::string file){

}

void GameSingleton::restart(){

}

void GameSingleton::hint(){

}

void GameSingleton::I(){
  std::cout << "Setting I" << std::endl;
  current = tetroFactory->makeTetromino(TetroType::IBlock);
  theBoard.setCurrentTetromino(current);
  this->notifyObservers();
}

void GameSingleton::L(){
  current = tetroFactory->makeTetromino(TetroType::LBlock);
  theBoard.setCurrentTetromino(current);
  this->notifyObservers();
}

void GameSingleton::J(){
  current = tetroFactory->makeTetromino(TetroType::JBlock);
  theBoard.setCurrentTetromino(current);
  this->notifyObservers();
}

void GameSingleton::Zero(){
  current = tetroFactory->makeTetromino(TetroType::ZeroBlock);
  theBoard.setCurrentTetromino(current);
  this->notifyObservers();
}
void GameSingleton::S(){
  current = tetroFactory->makeTetromino(TetroType::SBlock);
  theBoard.setCurrentTetromino(current);
  this->notifyObservers();
}

void GameSingleton::Z(){
  // TODO: didnt work
  current = tetroFactory->makeTetromino(TetroType::ZBlock);
  theBoard.setCurrentTetromino(current);
  this->notifyObservers();
}

void GameSingleton::T(){
  current = tetroFactory->makeTetromino(TetroType::TBlock);
  theBoard.setCurrentTetromino(current);
  this->notifyObservers();
}

std::ostream &operator<<(std::ostream &out, const GameSingleton &gs) {
  out << gs.theBoard;
  return out;
}


