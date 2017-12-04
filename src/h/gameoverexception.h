#ifndef GAME_OVER_EXCEPT_H
#define GAME_OVER_EXCEPT_H
#include <string>
#include <exception>
class GameOverException : public std::exception {
    std::string whatMessage;
    public:
        GameOverException(std::string whatMessage);
        const char * what() const throw() {
          return whatMessage.c_str();
        }

};

#endif

