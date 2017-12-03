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

  NotifFrom notifFrom {FromType::Game, rowsScore, blocksClearedScore, hiscore, level}; 
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
  NotifFrom notifFrom {FromType::Game, rowsScore, blocksClearedScore, hiscore, level}; 
  this->setNotifFrom(notifFrom);
  this->notifyObservers();
}

void GameSingleton::leveldown(){
  // TODO: didnt work
  if (level > 0) {
    --level;
    NotifFrom notifFrom {FromType::Game, rowsScore, blocksClearedScore, hiscore, level}; 
    this->setNotifFrom(notifFrom);
    this->notifyObservers();
  }
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

size_t GameSingleton::getRowsScore() {
	return rowsScore;
}
size_t GameSingleton::getBlocksClearedScore() {
	return blocksClearedScore;
}
size_t GameSingleton::getHiScore() {
	return hiscore;
}
size_t GameSingleton::getLevel() {
	return level;
}
void GameSingleton::setRowsScore(size_t s) {
	std::cout << "set rows score to " << s << std::endl;
	rowsScore = s;
	NotifFrom notifFrom {FromType::Game, rowsScore, blocksClearedScore, hiscore, level}; 
    this->setNotifFrom(notifFrom);
    this->notifyObservers();
}
void GameSingleton::setBlocksClearedScore(size_t s) {
	blocksClearedScore = s;
	NotifFrom notifFrom {FromType::Game, rowsScore, blocksClearedScore, hiscore, level}; 
    this->setNotifFrom(notifFrom);
    this->notifyObservers();
}
void GameSingleton::setHiScore(size_t h) {
	hiscore = h;
	NotifFrom notifFrom {FromType::Game, rowsScore, blocksClearedScore, hiscore, level}; 
    this->setNotifFrom(notifFrom);
    this->notifyObservers();
}
void GameSingleton::setLevel(size_t l) {
	level = l;
	NotifFrom notifFrom {FromType::Game, rowsScore, blocksClearedScore, hiscore, level}; 
    this->setNotifFrom(notifFrom);
    this->notifyObservers();
}

size_t GameSingleton::getCurrentID() {
	return tetroFactory->getCurrentID();
}

std::ostream &operator<<(std::ostream &out, const GameSingleton &gs) {
  out << gs.theBoard;
  return out;
}



