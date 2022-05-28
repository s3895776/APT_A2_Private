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
Row Board::getRow(const std::string coordinates){
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
Column Board::getCol(const std::string coordinates){
    
    // Check the coordinates 
    // this method probably needs to be boolean
    // Column col = coordinates[1] - '0'
    std::string c = coordinates.substr(1);

    // default is negative, which will return false in 
    // valid and empty method. 
    Column col = -1;

    try {
        col = std::stoi(c);
    }
    catch (std::invalid_argument& e) {
        std::cout << "Column invalid" << std::endl;
    }

    return col;
}

int Board::getScore(std::vector<std::vector<Tile>> openList){
    int turnScore = 0;
    
    // check if the tiles are in the lists
    // add a vertical list, to prevent counting the value of a tile twice
    std::vector<std::vector<Tile>> vertCloseList(rows, std::vector<Tile>(columns, Tile()));
    
    // add a horizontal list, to prevent counting the value of a tile twice
    std::vector<std::vector<Tile>> horzCloseList(rows, std::vector<Tile>(columns, Tile()));

    int lastRow = ROW - 1;
    int lastCol = COLUMN - 1;

    for (int i = 0; i < COLUMN; ++i){

        for (int j = 0; j< ROW; ++j){
            Row row = j;
            Column col = i;

            bool checkLeft = true;
            bool checkRight = true;
            bool checkAbove = true;
            bool checkBelow = true;

            Tile curr = board[j][i];

            if (!curr.isEmpty() && (vertCloseList[row][col].isEmpty() || horzCloseList[row][col].isEmpty()) ){
               
                if (!vertCloseList[row][col].isEmpty()){
                    checkAbove = false;
                    checkBelow = false;
                }

                if (!horzCloseList[row][col].isEmpty()){
                    checkLeft = false;
                    checkRight = false;
                }

                if (curr.getLetter() == openList[row][col].getLetter()){
                    turnScore += curr.getValue();
                    openList[row][col] = Tile();
                    vertCloseList[row][col] = curr;
                    horzCloseList[row][col] = curr;
                   
                } 
                
                else {
                    checkAbove = false;
                    checkBelow = false;
                    checkLeft = false;
                    checkRight = false;
                }
                
                // check the value of the letters below until an empty space is hit or boundary of board
                while (checkBelow){
                    if (row == lastRow) {
                        checkBelow = false; 
                    } 
                    else if (board[row+1][col].isEmpty()){
                        checkBelow = false;
                    } 
                    else {
                    if (vertCloseList[row+1][col].isEmpty() && checkBelow){
                        Tile tile = board[row+1][col];
                        turnScore += tile.getValue();
                        vertCloseList[row+1][col] = tile;
                        openList[row+1][col] = Tile();
                    }
                    }
                    ++row;
                }
                
                // check the value of the letters above until an empty space is hit or boundary of board
                while (checkAbove){

                    if (row == 0) {
                        checkAbove = false; 
                    } 

                    else if (board[row-1][col].isEmpty()){
                        checkAbove = false;
                    } 

                    else {

                        if (vertCloseList[row-1][col].isEmpty()){
                            Tile tile = board[row-1][col];
                            turnScore += tile.getValue();
                            vertCloseList[row-1][col] = tile;
                            openList[row-1][col] = Tile();
                        }

                    }

                    --row;
                }
               
                row = j;
                col = i;

                // check the value of the letters below until an empty space is hit or boundary of board
                while (checkRight){
                    if (col == lastCol) {
                        checkRight = false;
                    } 

                    else if (board[row][col+1].isEmpty()) {
                        checkRight = false;
                    } 

                    else {

                        if (horzCloseList[row][col+1].isEmpty()) {
                            Tile tile = board[row][col+1];
                            turnScore += tile.getValue();
                            horzCloseList[row][col+1] = tile;
                            openList[row][col+1] = Tile();
                        }

                    }

                    ++col;
                }

                // check the value of the letters below until an empty space is hit or boundary of board
                while (checkLeft){

                    if (col == 0) {
                        checkLeft = false;
                    } 

                    else if (board[row][col-1].isEmpty()) {
                        checkLeft = false;
                    } 

                    else {

                        if (horzCloseList[row][col-1].isEmpty()){
                            Tile tile = board[row][col-1];
                            turnScore += tile.getValue();
                            horzCloseList[row][col-1] = tile;
                            openList[row][col-1] = Tile();
                        }

                    }

                    --col;
                }
            
            }
        
        }
    
    }
    
    // check if the coordinates are left, right, up or down of the given tile
    // get the value of the coordinates to the direction
    // repeat until there is no coordinate to check
    //return the score
    return turnScore;
}

void Board::placeTile(Tile tile, std::string coordinates){
    
    // add validation for the string, that its in the right order
    if (validAndEmpty(coordinates)) {
        /* convert the coordinates into rows and cols */ 
        Column col = getCol(coordinates);
        Row row = getRow(coordinates);
        board[row][col] = tile;
    }
    
}

bool Board::isEmpty(std::string coordinates) {
    Row row = getRow(coordinates);
    Column col = getCol(coordinates);
    // bool empty = false;
    
    // if (board[row][col].isEmpty()){
    //     empty = true;
    // }
    
    return board[row][col].isEmpty();
}

bool Board::validCoordinate(const std::string coordinates) {
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
    // bool empty = false;
    // if (board[row][col].isEmpty()){
    //     empty = true;
    // }
    return board[row][col].isEmpty();
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

    if (validCoordinate(coordinates)) {
        Column col = getCol(coordinates);
        Row row = getRow(coordinates);

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

std::string Board::displayTile(int row, int col){
    std::string tile = " ";
    
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
std::vector<int> Board::separateCoordinates(const std::string coordinates) {
    // verify coordinates
    std::vector<int> separatedCoordinates;

    if (this->validCoordinate(coordinates)) {
        // use std::to_string on Row and Col types.
        int row = ( getRow(coordinates));
        int col = ( getCol(coordinates));
        separatedCoordinates.push_back(row);
        separatedCoordinates.push_back(col);
    }
    
    return separatedCoordinates;
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
    std::vector<std::vector<int>> separatedCoordinates;
    const int COLUMN_INDEX = 1;
    const int ROW_INDEX = 0;
    
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
            separatedCoordinates.push_back(
                this->separateCoordinates(projectedCoordinates[0]));

            // do not check if coordinate is on a boundary. 
            // initiate boundary checks. 
            // enter the row as first param and the column as second param. 
            canBePlaced = this->adjacentNotEmpty(
                separatedCoordinates[0][ROW_INDEX],
                 separatedCoordinates[0][COLUMN_INDEX]);
        }

    }

    else {
        canBePlaced = true;
        std::sort(projectedCoordinates.begin(), projectedCoordinates.end());
        
        // TODO: check if there are any duplicate coordinates. 
        // since its sorted, can check one element to the next. 

        for (std::string& coordinateString : projectedCoordinates) {
            separatedCoordinates.push_back(
                this->separateCoordinates(coordinateString));
        }

        // TODO: check if all coordinates belong on the same line. 
        // i.e. row == row or column == column 
        int i = 0;
        int projectedSize = projectedCoordinates.size();
        bool rowIsSame = false;
        bool columnIsSame = false;

        // column must be the same
        // compare first coordinate to second coordinate. 
        // if the row is not equal, the column must be equal.
        if (separatedCoordinates[0][ROW_INDEX] 
        != separatedCoordinates[1][ROW_INDEX]) {
            columnIsSame = true;
        }

        // rows must be the same
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
            int currentRow = separatedCoordinates[i][ROW_INDEX];
            int currentCol = separatedCoordinates[i][COLUMN_INDEX];
            int nextRow = separatedCoordinates[i + 1][ROW_INDEX];
            int nextCol = separatedCoordinates[i + 1][COLUMN_INDEX];

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
                // the NOT indicates that if the adjacent is 
                // not empty, notAdjacentToTile is false.
                notAdjacentToTile = !this->adjacentNotEmpty(
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
            int numCoordinates = separatedCoordinates.size();

            // placement of row and column in the std::vector<int>
            // from separate coordinates. 

            if (columnIsSame) {
                // grab the first coordinates column (all must be the
                // same)
                int columnNum = separatedCoordinates[0][COLUMN_INDEX];
                while ( i < numCoordinates - 1) {
                    // whether its a row or column, increment to check 
                    // that the space between this and the next coordinate
                    // is not empty. Coordinates are sorted, therefore only 
                    // incrementing is required. 
                    int rowCheck = separatedCoordinates[i][ROW_INDEX] + 1;
                    int nextRowCheck = separatedCoordinates[i + 1][ROW_INDEX];
                    

                    while (rowCheck < nextRowCheck) {
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
                // grab the first coordinates row (all must be the
                // same)
                int rowNum = separatedCoordinates[0][ROW_INDEX];
                
                while ( i < numCoordinates - 1) {
                    // whether its a row or column, increment to check 
                    // that the space between this and the next coordinate
                    // is not empty. Coordinates are sorted, therefore only 
                    // incrementing is required. 
                    int colCheck = separatedCoordinates[i][COLUMN_INDEX] + 1;
                    int nextColCheck = separatedCoordinates[i + 1][COLUMN_INDEX];
                    

                    while (colCheck < nextColCheck) {
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
        if ( !this->isEmpty( (rowCoordinate - 1), (colCoordinate) ) ) {
            adjacentNotEmpty = true;
        }
    }

    if (checkBelow) {
        // TODO: check below coordinate
        if ( !this->isEmpty( (rowCoordinate + 1), (colCoordinate ) ) ) {
            adjacentNotEmpty = true;
        }
    }

    if (checkLeft) {
        // checks left coordinate
        if ( !this->isEmpty( (rowCoordinate), (colCoordinate - 1) ) ) {
            adjacentNotEmpty = true;
        }
    }

    if (checkRight) {

        // checks the right coordinate
        if ( !this->isEmpty( (rowCoordinate), (colCoordinate + 1) ) ) {
            adjacentNotEmpty = true;
        }
    }

    return adjacentNotEmpty;
}

int Board::getTileScore(Row row, Column col) {
    return this->board[row][col].getValue();
}
