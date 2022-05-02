#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H


#include <vector>
#include "Tile.h"


class Board {
public:
    /* Constructor, Destructor, Copy Constructor */
    Board();
    ~Board();
    Board(Board& other);

    /* Place Tile on the board, takes the coordinates in the format sent in by the player,
       and converts it into the appropriate vector coordinates */
    std::string placeTile(Tile tile, std::string coordinates);

    /* Remove Tile, to be used if move is invalid*/

    std::string removeTile(Tile tile, std::string coordinates);
    
    /* Displays the board as a 2D grid */
    std::string displayBoard();

private:
    std::vector<std::vector<Tile>> board;
    //Tile* empty;

};

#endif // ASSIGN2_BOARD_H
