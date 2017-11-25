#ifndef CMDPARSER_H
#define CMDPARSER_H
#include <map>
typedef void (*sFunc)()
class CommandParser{
  std::map<string,sFunc> funcs;
  callFunc(string s);
  string arg;
  string cmd;
  callWithArg();
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
