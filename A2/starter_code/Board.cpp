#include "Board.h"
#include <fstream>
#include <iostream>

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
void Board::placeTile(Tile tile, std::string coordinates){
    /* convert the coordinates into rows and cols */ 
    
    // TODO: add validation for the string, that its in the right order
    Column col = getCol(coordinates);
    Row row = getRow(coordinates);

    // place the tile given conditions
    // return success

    // TODO: Call validMove to check if the move is valid, if the board is notEmpty
    if (validAndEmpty(row, col)) {
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
    } else {
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
    if (validMove(row, col)) {
        
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
