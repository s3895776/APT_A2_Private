#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "LinkedList.h"
#include "Game.h"


class Player {
    public:
        std::string saveGame(std::ifstream& fileSave);
        std::string loadGame(std::ifstream& fileLoad);
        std::string placeTiles();
        std::string replaceTiles();
        std::string skip();
        std::string quit();

    private:
        Game game;
        LinkedList hand;

};


#endif // GAME_H