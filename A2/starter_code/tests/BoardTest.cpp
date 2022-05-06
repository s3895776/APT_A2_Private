#include "../Board.h"
#include <iostream>



void Board_TestRemoveTile();
void Board_TestPlaceTile();
void Board_TestDisplayBoard();
void runTests();
Board* board;


void Board_TestPlaceTile(){
    Tile* tile1 = new Tile('A', 4);
    board->placeTile(tile1, "6C");
}
void Board_TestRemoveTile(){
    board->removeTile("6C");
}


void runTests(){
    board = new Board();
    std::cout << "Is board vector empty " << std::endl;
    if (board->getBoard().empty() == 0){
        std::cout << "yes" << std::endl;
    } else {
        std::cout << "no" << std::endl;
    }
    Board_TestPlaceTile();
    board->displayBoard();
    Board_TestRemoveTile();
    board->displayBoard();
    
}