#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include "Tile.h"
#include <vector>

class Board {
public:
    /* Constructor */
    Board(std::vector<std::vector<Tile>> board);
    ~Board();
    Board(Board& other);
    /* Destructor */

    /* Place Tile */

    /* Get Coordinates */
private:
    std::vector<std::vector<Tile>> board;

    

};

#endif // ASSIGN2_BOARD_H
