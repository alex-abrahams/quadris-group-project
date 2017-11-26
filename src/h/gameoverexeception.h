#ifndef GAME_OVER_EXCEPT_H
#define GAME_OVER_EXCEPT_H

#include <exception>
#include <stdexcept>

class GameOverException: public std::runtime_error {
    std::string whatMessage;
    public: 
        GameOverException(std::string whatMessage);
        virtual const char* what() const throw();
  

}

#endif
