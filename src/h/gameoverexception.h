#ifndef GAME_OVER_EXCEPT_H
#define GAME_OVER_EXCEPT_H
#include <string>
class GameOverException {
    std::string whatMessage;
    public: 
        GameOverException(std::string whatMessage);
        std::string getErrorMessage(); 

};

#endif
