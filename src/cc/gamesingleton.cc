#include "gamesingleton.h"
#include "tetrominofactory.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"


std::shared_ptr<GameSingleton> GameSingleton::ins;
std::shared_ptr<Level> GameSingleton::getZLevel(std::string file){
  return std::shared_ptr<Level>(new Level0(utility::bufferFile(file)));
}

std::vector<std::shared_ptr<Level>> GameSingleton::generateLevels(std::vector<std::string> i){
  //std::cout << "Z" << i.size();
  std::vector<std::shared_ptr<Level>> r;
  std::shared_ptr<Level> t = getZLevel("sequence.txt");
  for(size_t b = 0; b < i.size(); b++){
    //std::cout << "TEST: " << i.at(b);
    if(i.at(b) == "rnd"){
      t = std::shared_ptr<Level>(new RandomDecorator(i.at(++b), t));
    }else if(i.at(b) == "hvy"){
      t = std::shared_ptr<Level>(new HeavyDecorator(t));
    }else if(i.at(b) == "mid"){
      t = std::shared_ptr<Level>(new MiddleDecorator(t));
    }else if(i.at(b) == "done"){
      r.push_back(t);
      t = getZLevel("sequence.txt");
    }
  }
  return r;
}


void GameSingleton::init(std::string file, int dlevel, bool textonly, size_t highscore) {
  level = dlevel;
  hiscore = highscore;
  this->textonly = textonly;
  theBoard.init(15, 11, 3, textonly);
  //initlevels
  levels.push_back(getZLevel(file));
  std::vector<std::shared_ptr<Level>> t = generateLevels(utility::bufferFile(levelFile));
  levels.insert(levels.end(), t.begin(), t.end());

  for(auto i : levels){
    theBoard.attach(i);
    this->attach(i);
  }
  levels.at(level)->select(true);
  td = theBoard.getTextDisplay();
  this->attach(td);

  levels.at(level)->isSelected = true;
  if (!textonly) {
    gd = theBoard.getGraphicsDisplay();
    this->attach(gd);
  }

  tetroFactory = std::make_unique<TetrominoFactory>();
  current = levels.at(level)->getNextBlock();
  idlevel.emplace(current->getID(), level);
  // std::cout << current->getID();
  tetroFactory->addToID();
  next = levels.at(level)->getNextBlock();
  //  std::cout << next->getID();
  tetroFactory->addToID();
  idlevel.emplace(0,0);
  idlevel.emplace(next->getID(), level);
  theBoard.setCurrentTetromino(current);
  td->setNextTetromino(next);

  if (!textonly) {
    gd->setNextTetromino(next);
  }

  NotifFrom notifFrom {FromType::Game, rowsScore, blocksClearedScore, hiscore, level};
  this->setNotifFrom(notifFrom);
  this->notifyObservers();
  this->cmdp = CommandParser{"macros.txt"};
  gameRunning = true;
}

void GameSingleton::start(){
  std::cout << *this;
  while(gameRunning){
    cmdp.nextCommand();
    std::cout << *this;
  }
}

void GameSingleton::endGame(bool hardEnd, std::string msg){
  if(rowsScore + blocksClearedScore > hiscore) {
    hiscore = rowsScore + blocksClearedScore;
  }

  utility::writeFile("highscore.txt",std::to_string(hiscore));
  if(hardEnd) exit(0);
  else throw GameOverException{"Game restart"};
}

std::shared_ptr<TextDisplay> GameSingleton::getTextDisplay() {
  return td;
}

void GameSingleton::dropMiddle(){
  std::shared_ptr<AbstractTetromino> b = tetroFactory->makeTetromino(TetroType::OneBlock);
  b->setID(0);
  std::shared_ptr<AbstractTetromino> tmp = current;
  current = b;
  theBoard.setCurrentTetromino(current);
  for(int i = 0; i < 5; i++)
    right();
  theBoard.dropTetromino();
  current = tmp;
  theBoard.setCurrentTetromino(current);
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
  next = levels.at(level)->getNextBlock();

  theBoard.setCurrentTetromino(current);

  if (next) {

    idlevel.emplace(next->getID(), level);
    tetroFactory->addToID();
    theBoard.calculateScore();
    td->setNextTetromino(next);
    if (!textonly) {
      gd->setNextTetromino(next);
    }
  }

  NotifFrom f{FromType::Drop};
  this->setNotifFrom(f);
  this->notifyObservers();
  this->setNotifFrom(NotifFrom{FromType::NOTHING});
  if (theBoard.isTopLeftBlocked()) endGame(false, "Game Over!");

}

void GameSingleton::levelup(){
  levels.at(level)->select(false);
  level += 1;
  if(level >= levels.size()) level = levels.size()-1;
  if(next == nullptr) {next = levels.at(level)->getNextBlock();
    td->setNextTetromino(next);
  }
  NotifFrom notifFrom {FromType::Game, rowsScore, blocksClearedScore, hiscore, level};
  this->setNotifFrom(notifFrom);
  this->notifyObservers();
  levels.at(level)->select(true);
}

void GameSingleton::leveldown(){
  levels.at(level)->select(false);
  if (level > 0) {
    --level;
    NotifFrom notifFrom {FromType::Game, rowsScore, blocksClearedScore, hiscore, level};
    this->setNotifFrom(notifFrom);
    this->notifyObservers();
  }
  if(next == nullptr){
    next = levels.at(level)->getNextBlock();
    td->setNextTetromino(next);
  }
  levels.at(level)->select(true);
}

void GameSingleton::norandom(std::string file){
  levels.at(level)->norand(utility::bufferFile(file));
}

void GameSingleton::random(){
  levels.at(level)->random();
}

void GameSingleton::sequence(std::string file){
  std::vector<std::string> d = utility::bufferFile(file);
  for(auto z : d){
    cmdp.getCommand(z)();
  }
}

void GameSingleton::restart(){
  endGame(false,"RestartGame");
}

void GameSingleton::hint(){

}

std::shared_ptr<AbstractTetromino> GameSingleton::makeTestTetromino(TetroType input) {
  std::shared_ptr<AbstractTetromino> ret = tetroFactory->makeTetromino(input);
  ret->setID(ret->getID()-2);
  std::cout << ret->getID()<< std::endl;
  return ret;
}

void GameSingleton::I(){
  current = makeTestTetromino(TetroType::IBlock);
  theBoard.setCurrentTetromino(current);
  std::cout << current->getID() << std::endl;
  this->notifyObservers();
}

void GameSingleton::L(){
  current = makeTestTetromino(TetroType::LBlock);
  theBoard.setCurrentTetromino(current);
  this->notifyObservers();
}

void GameSingleton::J(){
  current = makeTestTetromino(TetroType::JBlock);
  theBoard.setCurrentTetromino(current);
  this->notifyObservers();
}

void GameSingleton::Zero(){
  current = makeTestTetromino(TetroType::ZeroBlock);
  theBoard.setCurrentTetromino(current);
  this->notifyObservers();
}
void GameSingleton::S(){
  current = makeTestTetromino(TetroType::SBlock);
  theBoard.setCurrentTetromino(current);
  this->notifyObservers();
}

void GameSingleton::Z(){
  current = makeTestTetromino(TetroType::ZBlock);
  theBoard.setCurrentTetromino(current);
  this->notifyObservers();
}

void GameSingleton::T(){
  current = makeTestTetromino(TetroType::TBlock);
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

