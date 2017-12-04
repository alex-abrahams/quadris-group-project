#include "cmdparser.h"
#include "gamesingleton.h"

#define GS_GET GameSingleton::get()


CommandParser::CommandParser(){
  funcs.emplace("down", []{GS_GET.down();});
  funcs.emplace("left", []{GS_GET.left();});
  funcs.emplace("right", []{GS_GET.right();});
  funcs.emplace("clockwise", []{GS_GET.clockwise();});
  funcs.emplace("counterclockwise", []{GS_GET.counterclockwise();});
  funcs.emplace("drop", []{GS_GET.drop();});
  funcs.emplace("levelup", []{GS_GET.levelup();});
  funcs.emplace("leveldown",[]{GS_GET.leveldown();});
  funcs.emplace("norandom", [&]{GS_GET.norandom(args);});
  funcs.emplace("sequence", [&]{GS_GET.sequence(args);});
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


void CommandParser::execMacro(std::string i){
  std::istringstream ss {macros.at(i)};
  std::string tmp;
  while(ss >> tmp){
    std::istringstream tp {tmp};
    int rep;
    if(!(tp>>rep))
      rep = 1;
    tp >> tmp;
    std::function<void()> tt = getCommand(tmp);
    for(int i = 0 ; i < rep; i++)
      tt();
  }
}

void CommandParser::createMacro(std::string in){
  std::istringstream ss{in};
  ss >> cmd;
  std::string tmp2;
  std::getline(ss,tmp2);
  funcs.emplace(cmd, [&]{execMacro(cmd);});
  macros.emplace(cmd,tmp2);
}

std::function<void()> CommandParser::getCommand(std::string cmd){
 std::map<std::string, std::function<void()>>data = match(cmd);
  if(data.size() == 1){
    return data.begin()->second;
  }
  for(auto i : data){
    if(i.first == cmd)return i.second;
  }
  return []{};
}

//gets,parses and executes next available command;
void CommandParser::nextCommand(){
  std::string line;
  if(!std::getline(std::cin, line))GameSingleton::get().endGame(true);
  std::istringstream dd {line};
  dd >> cmd;
  std::istringstream ss {cmd};
  int rep = 1;
  if(!(ss >> rep)){
    rep = 1;
    //std::cout << "testss" << std::endl;
  }else{
    ss >> cmd;
  }
  std::string tmp;
  std::getline(ss, args);
  std::function<void()> t = getCommand(cmd);
  for(int i = 0; i < rep; i++)
    t();

}



//wrapper for for calling functsion with arguments due to homogenity of containers problem


