#ifndef UTILITY_H
#define UTILITY_H
#include <fstream>
#include <vector>
#include <string>
#include "info.h"
namespace utility{
  //buffer file into usable vector of strings
  std::vector<std::string> bufferFile(std::string name);
  void writeFile(std::string fname, std::string i);
  TetroType strToTet(std::string i);
}
#endif
