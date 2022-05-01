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

        /*Copy constructor (not sure if necessary) */
        Player(Player& other);

        /* Just pass on the name and hand
        as 
        */
        std::string saveGame();

        /* place Tiles from linkedList hand
        */

        std::string placeTiles(LinkedList* tileBag);
        /* replace Tiles from linkedList hand
        */

        std::string replaceTile(LinkedList* tileBag);
        /* "end turn"
        */

        std::string skip();
        /*  quit the program
        */

        std::string quit();

        /* Fill in the players name
        */

        std::string setName(std::string name);

        /* return the hand to display  
        */
        std::string getHand();

        /* Fill in the players hand to full]
        remember to empty the tile bag for tiles 
        that are taken
        */
        std::string setHand(LinkedList* tileBag);

        /*        return the players name         */
        std::string getName();

    private:
        LinkedList hand;
        std::string name;

};


#endif // GAME_H