#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include "LinkedList.h"

class Game {

    private:
        std::vector< std::vector<char> > Board;
        LinkedList TileBag;
};


#endif // GAME_H