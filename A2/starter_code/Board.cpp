#include "Board.h"
#include <array>
#include <iostream>

Board::Board(){
    rows = ROW;
    columns = COLUMN;
    std::vector<std::vector<Tile*>> b(rows, std::vector<Tile*> (columns, nullptr));
    
    this->board = b;
}
Board::~Board(){

}
Board::Board(Board& other){
    board = other.board;
    rows = other.rows;
    columns = other.columns;
}
std::vector<std::vector<Tile*>> Board::getBoard(){
    return board;
}


std::string Board::placeTile(Tile* tile, std::string coordinates){
    /* convert the coordinates into rows and cols */ 
    Column col = coordinates.back();
    char r = coordinates.back();
    Row row = 0;
    
    char row_letters[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O'};
    for (int i = 0; i < ROW; ++i) {
        if (r == row_letters[i]){
            row = i;
        }
    }
    
    board[row][col] = tile;
    return "in progress";
}
std::string Board::removeTile(Tile* tile, std::string coordinates){
    return "in progress";
}
std::string Board::displayTile(int row, int col){
    std::string tile = " ";
    if (board[row][col] != nullptr) {
        char letter = board[row][col]->letter;
        tile += letter;
        tile += " ";
    } else {
        tile = "   ";
    }  
    return tile;
}
void Board::printRow(int row, std::string colLetter){
    std::cout << colLetter+" |";
    for (int i = 0; i < COLUMN; ++i){
        std::cout << displayTile(row, i)+"|";
    }
    std::cout<<std::endl;
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
    printRow(0,"A");
    printRow(1,"B");
    printRow(2,"C");
    printRow(3,"D");
    printRow(4,"E");
    printRow(5,"F");
    printRow(6,"G");
    printRow(7,"H");
    printRow(8,"I");
    printRow(9,"J");
    printRow(10,"K");
    printRow(11,"L");
    printRow(12,"M");
    printRow(13,"N");
    printRow(14,"O");


}