#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "LinkedList.h"


class Player {
    public:
        /* Constructor, destructor */
        Player();
        ~Player();

        /* Copy constructor (not sure if necessary) */
        Player(const Player& other);

        /* drop a tile from linkedList hand and return it */
        Tile dropTile(Letter letter);

        /* set a tile in the hand */
        std::string fillHand(Tile tile);

        /* return the hand as a comma separated ordered list */
        std::string getHand();

        /* Fill in the players name */
        std::string setName(std::string name);

        /*        return the players name         */
        std::string getName();
        
        /* append score to the player score */
        std::string addScore(int score);

        /* get the score of the player */
        int getScore();

    private:
        LinkedList hand;
        std::string name;
        int score;

};


#endif // GAME_H