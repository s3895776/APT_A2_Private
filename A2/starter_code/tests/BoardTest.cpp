#include "../Board.h"
#include <iostream>



void Board_TestRemoveTile();
void Board_TestPlaceTile();
void Board_TestDisplayBoard();
void runTests();


void Board_TestPlaceTile(Board& board) {
    Tile tile1 = Tile('A', 60);
    board.placeTile(tile1, "6A");
    board.placeTile(tile1, "6B");
    board.placeTile(tile1, "6C");
    board.placeTile(tile1, "6D");
    board.placeTile(tile1, "6E");
    board.placeTile(tile1, "6O");
}
void Board_TestRemoveTile(Board& board){
    board.removeTile("6A");
}


void runTests(){
    Board board;

    board = Board();
    std::cout << "Is board vector empty " << std::endl;
    if (board.getBoard().empty() == 0){
        std::cout << "yes" << std::endl;
    } else {
        std::cout << "no" << std::endl;
    }
    board.displayBoard();
    Board_TestPlaceTile(board);
    board.displayBoard();
    Board_TestRemoveTile(board);
    board.displayBoard();
    
}