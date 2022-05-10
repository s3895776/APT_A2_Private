#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <regex>
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

    /* returns the board for testing purposes*/
    std::vector<std::vector<Tile>> getBoard();

    /*
     * Place Tile on the board: parse coordinates from the player into row and column, convert it into an appropriate vector coordinates
     * Returns false if another tile already exists in place
     * Returns false if coordinates is in invalid format
     * Returns true if tile is successfully placed
     */
    bool placeTile(Tile tile, std::string coordinates);

    /* Remove Tile, to be used if move is invalid*/
    std::string removeTile(std::string coordinates);

    /* Utility method to get the face of the tile */
    std::string displayTile(int row, int col);
    /* Prints the rows of the board */
    void printRow(int row, std::string colLetter);
    /* Displays the board as a 2D grid */
    void displayBoard();
    
    

    /* For saving purposes: saves the board state - NOT YET IMPLEMENTED */

    std::string saveBoard();

   

private:
    std::vector<std::vector<Tile>> board;
    Row rows;
    Column columns;
    //Tile* empty;

};

#endif // BOARD_H
