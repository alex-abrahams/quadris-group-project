#include "cmdparser.h"
#include <iostream>
#include <string>
#include "gamesingleton.h"

#define GS_GET GameSingleton::get()

CommandParser::CommandParser(){
  funcs.emplace("down", []{GS_GET.down();});
  funcs.emplace("up", []{GS_GET.up();});
  funcs.emplace("left", []{GS_GET.left();});
  funcs.emplace("right", []{GS_GET.right();});
  funcs.emplace("clockwise", []{GS_GET.clockwise();});
  funcs.emplace("counterclockwise", []{GS_GET.counterclockwise();});
  funcs.emplace("drop", []{GS_GET.drop();});
  funcs.emplace("levelup", []{GS_GET.levelup();});
  funcs.emplace("norandom", [this]{GS_GET.norandom(args);});
  funcs.emplace("sequence", [this]{GS_GET.sequence(args);});
  funcs.emplace("I", []{GS_GET.I();});
  funcs.emplace("J", []{GS_GET.J();});
  funcs.emplace("L", []{GS_GET.L();});
  funcs.emplace("Zero", []{GS_GET.Zero();});
  funcs.emplace("S", []{GS_GET.S();});
  funcs.emplace("Z", []{GS_GET.Z();});
  funcs.emplace("T", []{GS_GET.T();});
  funcs.emplace("restart", []{GS_GET.restart();});
  funcs.emplace("hint", []{GS_GET.hint();});
}

CommandParser::CommandParser(std::string i): CommandParser(){
  //TODO file macros
}

//gets,parses and executes next available command;
void CommandParser::nextCommand(){
  std::string line;
  std::getline(std::cin, line);
  std::istringstream ss{line};
  ss >> cmd;
  std::string tmp;
  std::getline(ss, args);
  std::map<std::string, std::function<void()>>data = match(cmd);
  if(data.size() == 1){
    data.begin()->second();
  }
}

//wrapper for for calling functsion with arguments due to homogenity of containers problem

