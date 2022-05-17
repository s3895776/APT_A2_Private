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

    /* checks that there is no tile at the specified location 
    will cause segment fault without correct coordinates.*/
    bool isEmpty(std::string coordinates);
    bool isEmpty(Row row, Column col);

    /* checks that one of the surrounding tiles is occupied, to make the move valid */
    bool validCoordinate(std::string coordinates);
    bool validMove(Row row, Column col);

    /* Return true if coordinate is both valid and empty */
    bool validAndEmpty(std::string coordinates);
    bool validAndEmpty(Row row, Column col);

    /* Utility method to get the face of the tile */
    std::string displayTile(int row, int col);
    /* Prints the rows of the board */
    std::string printRow(int row, std::string colLetter);
    int getScore();
    /* Displays the board as a 2D grid */
    void displayBoard();
    
    

    /* For saving purposes: saves the board state - NOT YET IMPLEMENTED */

    void saveBoard(std::ofstream& file);

    // separate coordinates according to how Board treats coordinates. 
    // row is first, column is second
    // works as expected given that the coordinates are valid for 
    // the Board ADT. 
    std::vector<int> separateCoordinates(std::string coordinates);

    /* Check if the board is empty. */
    bool boardEmpty();
   
    /* checks projectedCoordinates to see if they are all valid moves.
    only works for when Coordinates are already validated.


    */
    bool checkBoardAdjacency(std::vector<std::string> projectedCoordinates);

    /* Return boolean that tells if the current tile is adjacent
        to a non-empty tile
        Coordinate parameters must be valid for Board. 
        */
    bool adjacentNotEmpty(int rowCoordinate, int colCoordinate);

private:
    std::vector<std::vector<Tile>> board;
    Row rows;
    Column columns;
    //Tile* empty;

};

#endif // BOARD_H
