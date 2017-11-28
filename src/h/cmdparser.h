#ifndef CMDPARSER_H
#define CMDPARSER_H
#include <map>
#include <iostream>
#include <sstream>
#include <functional>
class CommandParser{
  std::map<std::string,std::function<void()>> funcs;
  //funcs with args
  std::map<std::string,std::function<void(std::string i)>> fwa;
  std::string args;
  std::string cmd;

  void callWithArg();
  //return submap of all string function pairs that match command header s
  template<typename F>
  std::map<string,F> CommandParser::match(string s){
    std::map<string, F> r;
    for(auto& it : funcs){
      if(it.first.find(s) == 0){
        r.emplace(it.first,it.second);
      }
    }
    return r;
  }
  public:
    //custom scripting file
    //format tba
    CommandParser(string relPath);
    //default constructor initializes with only default commands
    CommandParser();
    //parse and execute next command action.
    void nextCommand();

};


#endif
