#include "cmdparser.h"
#include <iostream>
#include <string>
#include "gamesingleton.h"

CommandParser::CommandParser(){
  // TODO: what's funcs??? where is it declared?
  
  funcs.emplace("down",GameSingleton::get().down;
  funcs.emplace("up",GameSingleton::GameSingleton::get().up;
  funcs.emplace("left",GameSingleton::GameSingleton::get().left);
  funcs.emplace("right",GameSingleton::GameSingleton::get().right);
  funcs.emplace("clockwise",GameSingleton::get().clockwise);
  funcs.emplace("counterclockwise",GameSingleton::get().counterclockwise);
  funcs.emplace("drop", GameSingleton::get().drop);
  funcs.emplace("levelup", GameSingleton::get().levelup);
  funcs.emplace("norandom", callWithArg);
  funcs.emplace("sequence", callWithArg);
  funcs.emaplce("I", GameSingleton::get().I);
  funcs.emplace("J", GameSingleton::get().J);
  funcs.emplace("L", GameSingleton::get().L);
  funcs.emplace("Zero", GameSingleton::get().Zero);
  funcs.emplace("S", GameSingleton::get().S);
  funcs.emplace("Z", GameSingleton::get().Z);
  funcs.emplace("T", GameSingleton::get().T);
  funcs.emplace("restart", GameSingleton::get().restart);
  funcs.emplace("hint", GameSingleton::get().hint);
}

CommandParser::CommandParser(string i): CommandParser(){
  //TODO file macros
}

//gets,parses and executes next available command;
void CommandParser:nextCommand(){
  string line;
  std::getline(std::cin, line);
  istringstream ss(line);
  ss  >> cmd;
  string tmp;
  std::getline(ss, args);
  std::map<string, std::function<void()> data = match(cmd);
  if(data.size() == 1){
    data.begin().second();
  }
}
//wrapper for for calling functsion with arguments due to homogenity of containers problem
void CommandParser::callWithArg(){
  //TODO where is the match function defined???
  std::map<std::string, std::function<void(std::string)> data = match(fwa);
  if(data.size() == 1){
    data.begin().second(args);
  }
}
