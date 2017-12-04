#include "cmdparser.h"
#include "gamesingleton.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cstdlib>
#include "utility.h"
#include "gameoverexception.h"

int main(int argc, char** args) {
  std::string f = "sequence.txt";
  int i = 0;
  int deflv = 0;
  bool textonly = false;
  
  while(i < argc - 1){
    std::string opt = std::string(args[++i]);
    if(opt == "-seed")
      srand(atoi(args[++i]));
    else if(opt == "-text")
      textonly = true;
    else if(opt == "-scriptfile")
      f = std::string(args[++i]);
    else if(opt == "-startlevel")
      deflv = atoi(args[++i]);
  }

  while(true){
  size_t hs;
  std::istringstream ss(utility::bufferFile("highscore.txt").at(0));
  ss >> hs;

    try{
      GameSingleton::get().init(f,deflv,textonly, hs);
      GameSingleton::get().start();
	    std::cout << GameSingleton::get();
    } catch (const GameOverException &e) {
      GameSingleton::get(true);
    }
  }
}

