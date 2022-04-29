#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "LinkedList.h"
#include "Game.h"


class Player {
    public:
        /* Constructor, destructor */
        Player();
        ~Player();

        /*Copy constructor (not sure if necessary) */
        Player(Player& other);

        /* Save details of Game ADT and its Tile bag. 
        */
        std::string saveGame(std::ifstream& fileSave);
        /* I imagine it will be formatted for entering details 
        into the Game ADT and its Tile bag. 
        */
        std::string loadGame(std::ifstream& fileLoad);
        /* place Tiles from linkedList hand
        */
        std::string placeTiles();
        /* replace Tiles from linkedList hand
        */
        std::string replaceTiles();
        /* "end turn"
        */
        std::string skip();
        /*  quit the program
        */
        std::string quit();

    private:
        Game game;
        LinkedList hand;

};


#endif // GAME_H