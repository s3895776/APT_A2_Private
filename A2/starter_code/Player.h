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

        /* Return true if player has this tile in hand */
        bool hasTile(Letter letter);

        /* Delete a tile from the LinkedList hand and return it.
            If there is no tile in hand with the same letter, 
            the returned Tile will be Tiles' default constructor.
        */

        /*
         * Remove tile with the first occurence of letter from the hand
         * and returns the removed tile
         */
        Tile dropTile(Letter letter);

        /* set a tile in the hand */
        std::string fillHand(Tile tile);

        /* add new tile to the hand */
        void addTile(Tile tile);

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