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
        Player(Player& other);
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

        /* Return true if hand is empty, else false.*/
        bool handEmpty();

        /* increment skipped turned if player skips a turn  */
        std::string skippedTurn();

        /* reset skipped turn count to zero if player does not skip the turn */
        std::string turnNotSkipped();

        /* Return true if the turns skipped are equal or above two*/
        bool skippedTwoTurns();

        /* Print the users score in the format. */
        std::string printScore();

    private:
        LinkedList hand;
        std::string name;
        int score;
        int turnsSkipped;

};


#endif // GAME_H