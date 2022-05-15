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

    /* returns the board for testing purposes*/
    std::vector<std::vector<Tile>> getBoard();

    /* Place Tile on the board, takes the coordinates in the format sent in by the player,
       and converts it into the appropriate vector coordinates */
    void placeTile(Tile tile, std::string coordinates);

    /* Remove Tile, to be used if move is invalid*/
    std::string removeTile(std::string coordinates);

    /* returns the row and column extracted from the board coordinates provided */
    Row getRow(std::string coordinates);
    Column getCol(std::string coordinates);

    /* checks that there is no tile at the specified location */
    bool isEmpty(std::string coordinates);
    /* checks that one of the surrounding tiles is occupied, to make the move valid */
    bool validMove(std::string coordinates);

    /* Utility method to get the face of the tile */
    std::string displayTile(int row, int col);
    /* Prints the rows of the board */
    std::string printRow(int row, std::string colLetter);
    /* Displays the board as a 2D grid */
    void displayBoard();
    
    

    /* For saving purposes: saves the board state - NOT YET IMPLEMENTED */

    void saveBoard(std::ofstream& file);

   

private:
    std::vector<std::vector<Tile>> board;
    Row rows;
    Column columns;
    //Tile* empty;

};

#endif // BOARD_H
