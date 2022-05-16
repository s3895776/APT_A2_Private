#include "../tests.h"
#include "../Board.h"
#include <iostream>
#include <fstream>

//int Board_RunTests();
//
//int Board_TestRemoveTile();
//int Board_TestPlaceTile();
//void Board_TestDisplayBoard();

int Board_TestInitalise(){
    // Arrange
    Board board;

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport(std::to_string(board.getBoard().empty()), "0", "Board_TestInitalise");

    return numFailures;
}

int Board_TestPlaceTile() {
    // Arrange
    Board board;

    int TilesInBoard = 0;

    Tile tile1 = Tile('A', 60);
    board.placeTile(tile1, "A6");
    TilesInBoard += 1;

    board.placeTile(tile1, "B6");
    TilesInBoard += 1;

    board.placeTile(tile1, "C6");
    TilesInBoard += 1;

    board.placeTile(tile1, "D6");
    TilesInBoard += 1;

    board.placeTile(tile1, "E6");
    TilesInBoard += 1;

    board.placeTile(tile1, "F6");
    TilesInBoard += 1;

    const int SELECTED_COLUMN = 6;

    // Act
    // interestingly this will only work for descending rows and the 
    // same column
    std::string state = "TRUE";
    for (int i=0; i < TilesInBoard; i++){
        if (board.getBoard()[i][SELECTED_COLUMN].getLetter() != 'A'){
            state = "FALSE";
        }
    }
   
    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport(state, "TRUE", "Board_TestPlaceTile");

    return numFailures;
}


// int Board_TestRemoveTile(){
//     // Arrange
//     Board board;
//     Tile tile = Tile('G', 10);
//     board.placeTile(tile, "A6");

//     // Act
//     board.removeTile("A6");

//     // Assert 
//     int numFailures = 0;
//     char letter = board.getBoard()[0][6].getLetter();

//     numFailures += AssertAndReport(letter, ' ', "Board_TestRemoveTile");

//     return numFailures;
// }


    // // separate coordinates according to how Board treats coordinates. 
    // // row is first, column is second
    // std::vector<int> separateCoordinates(std::string coordinates);
int Board_Test_SeperateCoordinates() {
    int numFailures = 0;
    Board board;
    std::vector<std::string> coordinateList =
    {"A0", "B0", "C0", "D0", "E0"};

    std::vector<std::vector<int>> seperatedCoordinates;
    for (std::string& string : coordinateList) {
        seperatedCoordinates.push_back(board.separateCoordinates(string));
    }

    int i = 0;
    // int a = 0;
    // int b = 1;
    // int c = 2;
    // int d = 3;
    // int e = 4;

    // this only works given the strings above
    // check that the appropriate coordinates are given in numbers. 
    int size = seperatedCoordinates.size();
    while (i < size) {
        
        numFailures += AssertAndReport(i, seperatedCoordinates[i][0],
         "Board_Test_SeperateCoordinates");
        numFailures += AssertAndReport(0, seperatedCoordinates[i][1],
         "Board_Test_SeperateCoordinates");
        i += 1;
    }

    return numFailures;
}

int Board_Test_Empty_Board() {
    Board board;

    int numFailures = 0;

    if (board.boardEmpty()) {
        numFailures += AssertAndReport("","", "Board_Test_Empty_Board");
    }

    else {
        numFailures += AssertAndReport("Empty","Not empty", "Board_Test_Empty_Board");
    }

    Tile tile = Tile('A', 1);
    board.placeTile(tile, "O14");

    if (board.boardEmpty()) {
        numFailures += AssertAndReport("Empty","Not empty", "Board_Test_Empty_Board");
    }

    else {
        numFailures += AssertAndReport("","", "Board_Test_Empty_Board");
    }

    return numFailures;
}

    // /* Check if the board is empty: done for adjacency checks. */
    // bool boardEmpty();


int Board_checkBoardAdjacency(){
    // Arrange
    Board board;

    // Act
    //TODO

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport("TODO", "", "Game_MainMenuChoices");

    return numFailures;
}

int Board_adjacentNotEmpty() {
    // Arrange
    Board board;
    // setup isolated tiles, boundary tiles and adjacent tiles.
    Tile tile = Tile('A', 1);

    // Act
    //TODO: checks for adjacent coordinates and boundary coordinates.

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport("TODO", "", "Game_MainMenuChoices");

    return numFailures;
}

int Board_RunTests(){
    int numFailures = 0;

    numFailures += Board_TestInitalise();
    numFailures += Board_TestPlaceTile();
    // numFailures += Board_TestRemoveTile();
    numFailures += Board_Test_SeperateCoordinates();
    numFailures += Board_Test_Empty_Board();
    numFailures += Board_adjacentNotEmpty();
    numFailures += Board_checkBoardAdjacency();

    //std::cout << "    Board Failures: " << numFailures << "\n\n";
    std::cout << std::endl;
    return numFailures;
}