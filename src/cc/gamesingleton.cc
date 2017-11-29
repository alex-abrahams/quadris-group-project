#include "gamesingleton.h"

//TODO

GameSingleton::GameSingleton(){

}

void GameSingleton::down(){
  board.move(Direction::Down);
}

void GameSingleton::left(){
  board.move(Direction::Left);
}

void GameSingleton::right(){
  board.move(Direction::Right);
}

void GameSingleton::clockwise(){
//TODO
}

void GameSingleton::drop(){
  board.dropTetromino();
}

void





