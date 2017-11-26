#include "cmdparser.h"
#define ins GameSingleton::get()
CommandParser::CommandParser(){
  funcs.emplace("down",ins.down;
  funcs.emplace("up",GameSingleton::get().up;
  funcs.emplace("left",GameSingleton::get().left);
  funcs.emplace("right",GameSingleton::get().right);
  funcs.emplace("clockwise",ins.clockwise);
  funcs.emplace("counterclockwise",ins.counterclockwise);
  funcs.emplace("drop", ins.drop);
  funcs.emplace("levelup", ins.levelup);
  funcs.emplace("norandom", callWithArg);
  funcs.emplace("sequence", callWithArg);
  funcs.emaplce("I", ins.I);
  funcs.emplace("J", ins.J);
  funcs.emplace("L", ins.L);
  funcs.emplace("restart", ins.restart);
  funcs.emplace("hint", ins.hint);
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
  std::map<std::string, std::function<void(std::string)> data = match(fwa);
  if(data.size() == 1){
    data.begin().second(args);
  }
}
