#include "../Board.h"
#include <iostream>

int Board_RunTests();

int Board_TestRemoveTile();
int Board_TestPlaceTile();
void Board_TestDisplayBoard();

int Board_TestPlaceTile(Board& board) {
    int numFailures = 0;
    Tile tile1 = Tile('A', 60);
    board.placeTile(tile1, "A6");
    board.placeTile(tile1, "B6");
    board.placeTile(tile1, "C6");
    board.placeTile(tile1, "D6");
    board.placeTile(tile1, "E6");
    board.placeTile(tile1, "F6");
    board.placeTile(tile1, "6A");
    board.placeTile(tile1, "6B");
    board.placeTile(tile1, "6C");
    board.placeTile(tile1, "6D");
    board.placeTile(tile1, "6E");
    board.placeTile(tile1, "6F");

    bool pass = true;
    for (int i=0; i < 6; i++){
        if (board.getBoard()[i][6].getLetter() != 'A'){
            std::cout << "Expected 'A'" << std::endl;
            std::cout << "Returned: -"<< board.getBoard()[i][6].getLetter() << "-" << std::endl;
            
            pass = false;
        }
    }

    std::cout << "Test Board_TestPlaceTile ";
    if (pass){
        std::cout << "PASSED!" << std::endl;
    } else {
        std::cout << "FAILED!" << std::endl;
        numFailures++;
    }

    return numFailures;
}

int Board_TestRemoveTile(Board& board){
    int numFailures = 0;

    board.removeTile("A6");

    std::cout << "Test Board_TestRemoveTile ";

    // after the tile is removed displayTile should return an empty string
    if (board.getBoard()[0][6].getLetter() == ' '){
        std::cout << "PASSED!" << std::endl;
    } else {
        std::cout << "FAILED!" << std::endl;
        numFailures++;
    }

    return numFailures;
}

int Board_RunTests(){
    int numFailures = 0;

    Board board;
    board = Board();

    //std::cout << "Is board vector empty " << std::endl;

    std::cout << "Test Board_InitalisedEmpty ";
    if (board.getBoard().empty() == 0){
        std::cout << "PASSED!" << std::endl;
    } else {
        std::cout << "FAILED!" << std::endl;
        numFailures++;
    }
    //board.displayBoard();

    numFailures += Board_TestPlaceTile(board);
    //board.displayBoard();

    numFailures += Board_TestRemoveTile(board);
    //board.displayBoard();

    std::cout << "Board failures: " << numFailures << std::endl << std::endl;
    return numFailures;
}