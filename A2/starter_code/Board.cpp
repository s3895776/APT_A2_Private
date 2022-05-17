#include "Board.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

Board::Board(){
    rows = ROW;
    columns = COLUMN;
    std::vector<std::vector<Tile>> b(rows, std::vector<Tile>(columns, Tile()));
    this->board = b;
}
Board::~Board(){
}
Board::Board(Board& other){
    board = other.board;
    rows = other.rows;
    columns = other.columns;
}

std::vector<std::vector<Tile>> Board::getBoard(){
    return board;
}
Row Board::getRow(std::string coordinates){
    char r = coordinates[0];
    Row row = -1;
    char row_letters[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O'};
    for (int i = 0; i < ROW; ++i) {
        if (r == row_letters[i]){
            row = i;
        }
    }
    return row;
}
Column Board::getCol(std::string coordinates){
    
    // Check the coordinates 
    // this method probably needs to be boolean
    // Column col = coordinates[1] - '0'
    std::string c = coordinates.substr(1);
    Column col = std::stoi(c);
    return col;
}
int Board::getScore(std::string coordinates){
    int turnScore = 0;
    // check if the coordinates are left, right, up or down of the given tile
    // get the value of the coordinates to the direction
    // repeat until there is no coordinate to check
    //return the score
    return turnScore;
}
void Board::placeTile(Tile tile, std::string coordinates){
    /* convert the coordinates into rows and cols */ 
    
    // TODO: add validation for the string, that its in the right order
    Column col = getCol(coordinates);
    Row row = getRow(coordinates);

    // place the tile given conditions
    // return success

    // TODO: Call validMove to check if the move is valid, if the board is notEmpty
    if (validAndEmpty(coordinates)) {
        board[row][col] = tile;
    }
    
}

bool Board::isEmpty(std::string coordinates) {
    Row row = getRow(coordinates);
    Column col = getCol(coordinates);
    bool empty = false;
    
    if (board[row][col].isEmpty()){
        empty = true;
    }
    
    return empty;
}

bool Board::validCoordinate(std::string coordinates) {
    bool valid = true;
    char _row = coordinates[0];
    
    
    if (!isalpha(_row)){
        valid = false;
    }
    std::string _col = coordinates.substr(1);
    int colLength = _col.length();
    for (int i = 0; i < colLength; ++i){
        if (!isdigit(_col[i])){
            valid = false;
        }
    }

    Row row = getRow(coordinates);
    Column col = getCol(coordinates);

    if ( (col >= 0 && col < COLUMN)
    && (row>=0 && row < ROW) && valid) {
        valid = true;
    } 
    else {
        valid = false;
    }
    
    return valid;
}

bool Board::isEmpty(Row row, Column col){
    bool empty = false;
    if (board[row][col].isEmpty()){
        empty = true;
    }
    return empty;
}

bool Board::validMove(Row row, Column col) {
    bool valid = false;

    if ( (col >= 0 && col < COLUMN)
    && (row>=0 && row < ROW)) {
        valid = true;
    }

    return valid;
}

bool Board::validAndEmpty(std::string coordinates) {
    bool validAndEmpty = false;
    Column col = getCol(coordinates);
    Row row = getRow(coordinates);
    if (validCoordinate(coordinates)) {
        
        if (isEmpty(row, col) ) {
            validAndEmpty = true;
        }
    }
    return validAndEmpty;
}

bool Board::validAndEmpty( Row row, Column col ) {
    bool validAndEmpty = false;
    if (validMove(row, col)) {
        if ( isEmpty(row, col) ) {
            validAndEmpty = true;
        }
    }
    return validAndEmpty;
}

// std::string Board::removeTile(std::string coordinates){
//     // TODO: maybe find a better way to do this, or just leave it as it is
//     // Column col = coordinates[0] - '0';
   
//     Column col = getCol(coordinates);
    
//     Row row = getRow(coordinates);
//     board[row][col] = Tile();
//     // no need to clean up if it ain't a pointer kekw
//     //do we need a return? cause this could theoretically be a void method
//     return "in progress";
// }

std::string Board::displayTile(int row, int col){
    std::string tile = " ";
    // if (board[row][col] != nullptr) {
    //     char letter = board[row][col]->letter;
    //     tile += letter;
    //     tile += " ";
    // } else {
    //     tile = "   ";
    // }

    // Guan: If i am correct this should equate to 
    
    tile += board[row][col].getLetter();
    tile += " ";
    return tile;
}

std::string Board::printRow(int row, std::string colLetter){
    std::string result = colLetter+" |";
    for (int i = 0; i < COLUMN; ++i){
        result += displayTile(row, i); 
        result += "|";
    }
    return result;
   
}

void Board::displayBoard(){
    /* BOARD OUTPUT VISUALISATION
         0   1   2   3   4   5   6   7   8   9  10  11  12  13  14 
       -------------------------------------------------------------
     A |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     B |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     C |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     D |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     E |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     F |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     G |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     H |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     I |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     J |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     K |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     L |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     M |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     N |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     O |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    */

    std::cout << "    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14 " << std::endl;
    std::cout << "  -------------------------------------------------------------" << std::endl;
    std::cout << printRow(0,"A") << std::endl;
    std::cout << printRow(1,"B") << std::endl;
    std::cout << printRow(2,"C") << std::endl;
    std::cout << printRow(3,"D") << std::endl;
    std::cout << printRow(4,"E") << std::endl;
    std::cout << printRow(5,"F") << std::endl;
    std::cout << printRow(6,"G") << std::endl;
    std::cout << printRow(7,"H") << std::endl;
    std::cout << printRow(8,"I") << std::endl;
    std::cout << printRow(9,"J") << std::endl;
    std::cout << printRow(10,"K") << std::endl;
    std::cout << printRow(11,"L") << std::endl;
    std::cout << printRow(12,"M") << std::endl;
    std::cout << printRow(13,"N") << std::endl;
    std::cout << printRow(14,"O") << std::endl;
}

void Board::saveBoard(std::ofstream& file){
    /* save format */
    /*W@B3 I@B4 M@B5 C@C1 S@D10 etc... */
    char row_letters[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O'};
    std::string boardState = "";
    for (int i = 0; i < COLUMN; ++i){
        for (int j = 0; j< ROW; ++j){
            Tile tile = board[j][i];
            if (!tile.isEmpty()){
                boardState += board[j][i].getLetter(); 
                boardState += '@';
                boardState += row_letters[j];
                boardState += std::to_string(i);;
                boardState += " ";
            }
        }
    }
    file << boardState << std::endl;
 
}

// separate coordinates
std::vector<int> Board::separateCoordinates(std::string coordinates) {
    // verify coordinates
    std::vector<int> separateCoordinates;

    if (this->validCoordinate(coordinates)) {
        // use std::to_string on Row and Col types.
        int row = ( getRow(coordinates));
        int col = ( getCol(coordinates));
        separateCoordinates.push_back(row);
        separateCoordinates.push_back(col);
    }
    
    return separateCoordinates;
}

bool Board::boardEmpty() {
    bool boardEmpty = true;
    int i = 0;
    int j = 0;
    while (boardEmpty && i < ROW) {
        while (boardEmpty && j < COLUMN) {
            if (!this->board[i][j].isEmpty()) {
                boardEmpty = false;
            }
            j += 1;
        }
        j = 0;
        i += 1;
    }
    return boardEmpty;
}

bool Board::checkBoardAdjacency(std::vector<std::string> projectedCoordinates) {
    bool canBePlaced = false;
    // separate the projectedCoordinates to expect normal input.
    // each cell should have two spaces with the first representing row 
    // and the second representing column
    // this lets us compare coordinates defined by the board.
    std::vector<std::vector<int>> separateCoordinates;
    
    // case where projectedCoordinates is zero is not checked

    // should also check if the board is empty: 
    // if so, no need to check for existent tiles.

    bool boardIsEmpty = this->boardEmpty();


    if (projectedCoordinates.size() == 1) {
        // TODO: if the board is empty, it will be a valid move. 
        if (boardIsEmpty) {
            canBePlaced = true;
        }

        else {
            // TODO: check all adjacent tiles. 
            // If at least one is not empty, than it can be placed.
            separateCoordinates.push_back(
                this->separateCoordinates(projectedCoordinates[0]));

            // do not check if coordinate is on a boundary. 
            // initiate boundary checks. 
            // enter the row as first param and the column as second param. 
            canBePlaced = this->adjacentNotEmpty(
                separateCoordinates[0][0], separateCoordinates[0][1]);
        }

    }

    else {
        canBePlaced = true;
        std::sort(projectedCoordinates.begin(), projectedCoordinates.end());
        
        // TODO: check if there are any duplicate coordinates. 
        // since its sorted, can check one element to the next. 

        for (std::string& coordinateString : projectedCoordinates) {
            separateCoordinates.push_back(
                this->separateCoordinates(coordinateString));
        }

        
        // TODO: check if all coordinates belong on the same line. 
        // i.e. letter == letter or number == number 
        int i = 0;
        int projectedSize = projectedCoordinates.size();
        bool rowIsSame = false;
        bool columnIsSame = false;

        // coordinates must be the same
        if (separateCoordinates[0][0] != separateCoordinates[1][0]) {
            columnIsSame = true;
        }
        // letters must be the same
        else {
            rowIsSame = true;
        }

        // must check for adjacency. 
        // if no tiles are adjacent to at least an existing tile,
        // the move is invalid. 
        // alternatively, if the board is empty, no need to check 
        // for adjacency.  

        // if notAdjacentToTile is true at end of while loop,
        // the board is not empty and tiles are not placed next to 
        // a non-empty space, therefore canBePlaced will also be false. 
        bool notAdjacentToTile = true;

        if (boardIsEmpty) {
            notAdjacentToTile = false;
        }

        // checks for coordinates belonging on the same line 
        // and if two coordinates are the same. 
        // checks if the board is empty, if not at least one tile
        // must belong next to an existing tile. 
        while (i < projectedSize - 1 && canBePlaced) {
            int currentRow = separateCoordinates[i][0];
            int currentCol = separateCoordinates[i][1];
            int nextRow = separateCoordinates[i + 1][0];
            int nextCol = separateCoordinates[i + 1][1];

            // TODO: check if there are any duplicate coordinates. 
            // since its sorted, can check one element to the next. 
            if (currentRow == nextRow && currentCol == nextCol) {
                // cannot be placed.      
                canBePlaced = false;   

            } 

            if (columnIsSame) {

                // number is not the same: compare second cell
                if (currentCol != nextCol) {
                    // cannot be placed.                
                    canBePlaced = false;          
                }

            }

            else if (rowIsSame) {
                
                // letter is not the same: compare first cell. 
                if (currentRow != nextRow) {
                    // cannot be placed.                
                    canBePlaced = false;          
                }              

            }

            if (notAdjacentToTile) {
                // check that adjacent is not empty.
                // if it is, the check no longer occurs.
                // if it isn't, the check continues in
                // the next loop. 
                notAdjacentToTile = this->adjacentNotEmpty(
                    currentRow, currentCol);
            }

            i += 1;
        }
        
        // based on above spec, if this is true, canBePlaced 
        // is false.
        if (notAdjacentToTile) {
            canBePlaced = false;
        }

        // all tiles are in a straight line. 
        // check for emptiness between tiles.
        // example: for C11 and C15, check C12 to C14. 
        // note that the straight line comparison depends 
        // on what line the user places tiles across.
        if (canBePlaced) {
            // check in between for the column
            int i = 0;

            // use this in place of a row or column.
            int numCoordinates = separateCoordinates.size();

            if (columnIsSame) {
                int columnIndex = 1;
                int columnNum = separateCoordinates[0][columnIndex];
                while ( i < numCoordinates) {
                    // whether its a row or column, increment to check 
                    // that the space between this and the next coordinate
                    // is not empty.
                    int rowCheck = separateCoordinates[i][columnIndex] + 1;
                    int nextRowCol = separateCoordinates[i + 1][columnIndex];
                    

                    while (rowCheck < nextRowCol) {
                        // if the cell is empty, the move is invalid. 
                        if (this->isEmpty(rowCheck, columnNum)) {
                            canBePlaced = false;
                        }
                        rowCheck += 1;
                    }

                    i += 1;
                }
            }
            
            // row is same
            else {
                int rowIndex = 0;
                int rowNum = separateCoordinates[0][rowIndex];
                
                while ( i < numCoordinates) {
                    // whether its a row or column, increment to check 
                    // that the space between this and the next coordinate
                    // is not empty.
                    int colCheck = separateCoordinates[i][rowIndex] + 1;
                    int nextRowCol = separateCoordinates[i + 1][rowIndex];
                    

                    while (colCheck < nextRowCol) {
                        // if the cell is empty, the move is invalid. 
                        if (this->isEmpty(rowNum, colCheck)) {
                            canBePlaced = false;
                        }

                        colCheck += 1;
                    }

                    i += 1;
                }

            }

        }

    }
    return canBePlaced;
}


bool Board::adjacentNotEmpty(int rowCoordinate, int colCoordinate) {
    // initiate boundary checks. 
    bool adjacentNotEmpty = false;
    bool checkLeft = true;
    bool checkRight = true;
    bool checkAbove = true;
    bool checkBelow = true;

    int lastRow = ROW - 1;
    int lastCol = COLUMN - 1;

    // last row: check below is false
    if (rowCoordinate == lastRow) {
        checkBelow = false;
    }
    else if (rowCoordinate == 0) {
        checkAbove = false;
    }

    if (colCoordinate == lastCol) {
        checkRight = false;
    }

    else if (colCoordinate == 0) {
        checkLeft = false;
    }

    if (checkAbove) {
        // TODO: check above coordinate
        if ( !this->isEmpty( (rowCoordinate), (colCoordinate - 1) ) ) {
            adjacentNotEmpty = true;
        }
    }

    if (checkBelow) {
        // TODO: check below coordinate
        if ( !this->isEmpty( (rowCoordinate), (colCoordinate + 1) ) ) {
            adjacentNotEmpty = true;
        }
    }

    if (checkLeft) {
        // checks left coordinate
        if ( !this->isEmpty( (rowCoordinate - 1), (colCoordinate) ) ) {
            adjacentNotEmpty = true;
        }
    }

    if (checkRight) {

        // checks the right coordinate
        if ( !this->isEmpty( (rowCoordinate + 1), (colCoordinate) ) ) {
            adjacentNotEmpty = true;
        }
    }

    return adjacentNotEmpty;
}