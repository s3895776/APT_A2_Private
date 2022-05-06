#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Tile.h"

// Define a Row type
typedef int Row;
#define ROW    15
#define COLUMN 15

// Define a Column type
typedef int Column;

class Board {
public:
    /* Constructor, Destructor, Copy Constructor */
    Board();
    ~Board();
    Board(Board& other);

    /* Place Tile on the board, takes the coordinates in the format sent in by the player,
       and converts it into the appropriate vector coordinates */
    std::string placeTile(Tile* tile, std::string coordinates);

    /* Remove Tile, to be used if move is invalid*/

    std::string removeTile(Tile* tile, std::string coordinates);
    
    /* Displays the board as a 2D grid */
    void displayBoard();

    std::string displayTile(int row, int col);
    void printRow(int row, std::string colLetter);

    /* For saving purposes: saves the board state */

    std::string saveBoard();

    std::vector<std::vector<Tile*>> getBoard();

    void putTile(int row, int col){

    }

    

private:
    std::vector<std::vector<Tile*>> board;
    Row rows;
    Column columns;
    //Tile* empty;

};

#endif // BOARD_H
