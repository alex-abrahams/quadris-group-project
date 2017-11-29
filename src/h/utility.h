#ifndef UTILITY_H
#define UTILITY_H
#include <fstream>
#include <vector>
namespace utility{
  //buffer file into usable vector of strings
  std::vector<string> bufferFile(string name){
    std::ifstream f (name);
    std::string line;
    std::vector<std::string> tmp;
    while (std::getline(f, line)){
      tmp.push_back(line);
    }
    return tmp;
  }


}
#endif
