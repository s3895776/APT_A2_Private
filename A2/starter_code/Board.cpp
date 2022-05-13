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
    Row row;
    char row_letters[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O'};
    for (int i = 0; i < ROW; ++i) {
        if (r == row_letters[i]){
            row = i;
        }
    }
    return row;
}
Column Board::getCol(std::string coordinates){
    std::string c = coordinates.substr(1);
    Column col = std::stoi(c);
    return col;
}
bool Board::placeTile(Tile tile, std::string coordinates){
    bool success = false;
    /* convert the coordinates into rows and cols */ 
    // TODO: maybe find a better way to do this, or just leave it as it is
    // B10
    Column col = getCol(coordinates);
    if (col >= 0 && col < COLUMN){
        success = true;
    } 
    // Check the coordinates 
    // this method probably needs to be boolean
    // Column col = coordinates[1] - '0';
    
    Row row = getRow(coordinates);
    //todo define const and remove magic numbers
    if (row>=0 && row < ROW){
        success = true;
    } else {
        success = false;
    }
    std::cout << row << std::endl;
    // TODO: Call validMove to check if the move is valid, if the board is notEmpty
    // TODO: add validation for the string, that its in the right order
    if (isEmpty(coordinates) && success){
        board[row][col] = tile;
    }
    
    //do we need a return? cause this could theoretically be a void method
    return success;
}

bool Board::isEmpty(std::string coordinates){
    Row row = getRow(coordinates);
    Column col = getCol(coordinates);
    bool empty = false;
    if (board[row][col].isEmpty()){
        empty = true;
    }
    return empty;
}

bool Board::validMove(std::string coordinates){
    return true;
}

std::string Board::removeTile(std::string coordinates){
    // TODO: maybe find a better way to do this, or just leave it as it is
    // Column col = coordinates[0] - '0';
   
    Column col = getCol(coordinates);
    
    Row row = getRow(coordinates);
    board[row][col] = Tile();
    // no need to clean up if it ain't a pointer kekw
    //do we need a return? cause this could theoretically be a void method
    return "in progress";
}

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
    file << "    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14 " << std::endl;
    file << "  -------------------------------------------------------------" << std::endl;
    file << printRow(0,"A") << std::endl;
    file << printRow(1,"B") << std::endl;
    file << printRow(2,"C") << std::endl;
    file << printRow(3,"D") << std::endl;
    file << printRow(4,"E") << std::endl;
    file << printRow(5,"F") << std::endl;
    file << printRow(6,"G") << std::endl;
    file << printRow(7,"H") << std::endl;
    file << printRow(8,"I") << std::endl;
    file << printRow(9,"J") << std::endl;
    file << printRow(10,"K") << std::endl;
    file << printRow(11,"L") << std::endl;
    file << printRow(12,"M") << std::endl;
    file << printRow(13,"N") << std::endl;
    file << printRow(14,"O") << std::endl;
 
}
