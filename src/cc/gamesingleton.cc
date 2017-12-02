#include "gamesingleton.h"
#include "tetrominofactory.h"
#include "textdisplay.h"

void GameSingleton::init() {	
  theBoard.init(15, 11, 3);

  td = theBoard.getTextDisplay();
  this->attach(td);
  
  tetroFactory = std::make_unique<TetrominoFactory>();
  current = tetroFactory->makeTetromino(TetroType::JBlock);
  next = tetroFactory->makeTetromino(TetroType::ZBlock);
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
  while(gameRunning){
    cmdp.nextCommand();
    std::cout << *this;
  }
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
  this->notifyObservers();
}

void GameSingleton::counterclockwise(){
  this->notifyObservers();

}

void GameSingleton::drop(){
  this->notifyObservers();
}

void GameSingleton::levelup(){
  level += 1;
  this->notifyObservers();

}

void GameSingleton::leveldown(){
  if (level > 0) --level;

  this->notifyObservers();
}

void GameSingleton::norandom(std::string file){

}

void GameSingleton::sequence(std::string file){

}

void GameSingleton::restart(){

}

void GameSingleton::hint(){

}

void GameSingleton::I(){
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
