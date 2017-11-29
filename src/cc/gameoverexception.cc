#include "gameoverexception.h"
#include <string>

GameOverException::GameOverException(std::string whatMessage) : 
  whatMessage{whatMessage} {}

  std::string GameOverException::getErrorMessage() {
    return whatMessage;
  }
