#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include "LinkedList.h"

class Game {

    public:
        /* Constructor, destructor, copy constructor
        */
        Game();
        ~Game();
        Game(Game& other);
        std::string modifyBoard(std::vector<Tile> tilesToPlace, std::vector<std::string> coordinates);
        std::string loadGame(std::string saveFile);
        std::string newGame();
        std::string saveState();
        std::string turnEnd();


    private:
        std::vector< std::vector<char> > board;
        LinkedList tileBag;
        std::string awardPoints();
        std::string invalidMove();
};


#endif // GAME_H