#ifndef CMDPARSER_H
#define CMDPARSER_H
#include <map>
#include <iostream>
#include <sstream>
#include <string>
#include <functional>

class CommandParser {
  std::map<std::string, std::function<void()>> funcs;
  // funcs with args
  std::string args;
  std::string cmd;
  std::map<std::string, std::string> macros;

  void execMacro(std::string i);


  void createMacro(std::string in);
  //return submap of all string function pairs that match command header s
  std::map<std::string, std::function<void()>> match(std::string s) {
    std::map<std::string, std::function<void()>> r;
    for(auto& it : funcs){
      if(it.first.find(s) == 0){
        r.emplace(it.first,it.second);
      }
    }
    return r;
  }

  public:

  std::function<void()> getCommand(std::string i);
    //custom scripting file
    //format tba
    CommandParser(std::string relPath);
    //default constructor initializes with only default commands
    CommandParser();
    //parse and execute next command action.
    void nextCommand();


};


#endif
