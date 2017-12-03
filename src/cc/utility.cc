#include "utility.h"
#include "info.h"
std::vector<std::string> utility::bufferFile(std::string name){
    std::ifstream f (name);
    std::string line;
    std::vector<std::string> tmp;
    while (std::getline(f, line)){
      tmp.push_back(line);
    }
    return tmp;
  }

  TetroType utility::strToTet(std::string i){
    if(i == "I")
      return TetroType::IBlock;
    if(i == "J")
      return TetroType::JBlock;
    if(i == "L")
      return TetroType::LBlock;
    if(i == "0")
      return TetroType::ZeroBlock;
    if(i == "S")
      return TetroType::SBlock;
    if(i == "Z")
      return TetroType::ZBlock;
    if(i == "T")
      return TetroType::TBlock;
    return TetroType::None;
  }


