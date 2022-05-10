#include "../Board.h"
#include <iostream>
#include <fstream>



void Board_TestRemoveTile();
void Board_TestPlaceTile();
void Board_TestDisplayBoard();
void runTests();


void Board_TestPlaceTile(Board& board) {
    Tile tile1 = Tile('A', 60);
    board.placeTile(tile1, "A6");
    board.placeTile(tile1, "B6");
    board.placeTile(tile1, "C6");
    board.placeTile(tile1, "D6");
    board.placeTile(tile1, "E6");
    board.placeTile(tile1, "F6");
}
void Board_TestRemoveTile(Board& board){
    board.removeTile("A6");
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
    std::string gameState;
    std::string path = "tests/boardtest.txt";

    std::ofstream file(path);
    board.saveBoard(file);
    
}