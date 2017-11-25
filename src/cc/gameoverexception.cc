#include "../h/gameoverexcept.h"
#include <string>

GameOverException::GameOverException(std::string whatMessage) : 
    whatMessage{whatMessage} {}

const char* GameOverException::what() const throw() {
    return whatMessage.c_str();
}
