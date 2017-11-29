#include "gamesingleton.h"
#include "board.h"

//TODO

GameSingleton::GameSingleton(){

}

GameSingleton& GameSingleton::get(){
  static GameSingleton s;
  return s;
}

void GameSingleton::down(){
}

void GameSingleton::left(){
}

void GameSingleton::right(){
}

void GameSingleton::clockwise(){
//TODO
}

void GameSingleton::counterclockwise(){

}

void GameSingleton::drop(){
}

void GameSingleton::levelup(){

}

void GameSingleton::leveldown(){

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

}

void GameSingleton::L(){

}

void GameSingleton::J(){

}

void GameSingleton::Zero(){

}

void GameSingleton::S(){

}

void GameSingleton::Z(){

}

void GameSingleton::T(){

}
