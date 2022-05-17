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
    Board emptyBoard;
    Board filledBoard;
    Tile tile = Tile('A', 1);

    std::vector<std::string> projectedCoordinates;
    int numFailures = 0;

    // Act
    //TODO: returns if the tile placement is not next to anything

    // 1: empty board, one tile 
    projectedCoordinates.push_back("A1");
    // place A1: expect true
    if (!emptyBoard.checkBoardAdjacency(projectedCoordinates) ) {
        numFailures += 1;
    }

    // 2: non-empty board, one tile 
    filledBoard.placeTile(tile, "A0");
    // place A1 next to A0: expect true
    if (!filledBoard.checkBoardAdjacency(projectedCoordinates)) {
        numFailures += 1;

    }
    

    // 3: empty board, invalid placement of several tiles
    projectedCoordinates.push_back("A3");
    // place A3 and A1: expect false
    if (emptyBoard.checkBoardAdjacency(projectedCoordinates)) {

    }

    // 4: empty board, placement valid of several tiles
    projectedCoordinates.push_back("A2");

    // place A1, A2, A3, empty board, expect true.

    if (!emptyBoard.checkBoardAdjacency(projectedCoordinates)) {
        numFailures += 1;

    }
    // 5: board non-empty, invalid placement
    projectedCoordinates.empty();
    projectedCoordinates.push_back("A3");
    projectedCoordinates.push_back("A2");

    // place A2, A3, expect false.

    if (filledBoard.checkBoardAdjacency(projectedCoordinates)) {
        numFailures += 1;

    }
    // 6: board non-empty, valid placement. 
    // place A1, A2, A3, expect true.
    projectedCoordinates.push_back("A1");
    if (!filledBoard.checkBoardAdjacency(projectedCoordinates)) {
        numFailures += 1;
    }

    // Assert
    AssertAndReport(numFailures, 0, "Board_checkBoardAdjacency");

    return numFailures;
}

int Board_adjacentNotEmpty() {
    // Arrange
    Board board;
    // setup isolated tiles, boundary tiles and adjacent tiles.
    Tile tile = Tile('A', 1);

    // Act
    //TODO: checks for adjacent coordinates and boundary coordinates.
    board.placeTile(tile,"A0");
    board.placeTile(tile,"A14");
    board.placeTile(tile,"O0");
    board.placeTile(tile,"O14");
    board.placeTile(tile, "G5");


    // Assert
    int numFailures = 0;
    
    // check B0, A1, B1
    // B0 is true
    if (!board.adjacentNotEmpty(1,0)) {
        numFailures += 1;
    }
    if (!board.adjacentNotEmpty(0,1)) {
        numFailures += 1;
    }

    // B1 should be false
    if (board.adjacentNotEmpty(1,1)) {
        numFailures += 1;
    }

    // check B14, A13, B13
    if (!board.adjacentNotEmpty(1,14)) {
            numFailures += 1;
        }

    if (!board.adjacentNotEmpty(0,13)) {
            numFailures += 1;
        }

    if (board.adjacentNotEmpty(1,13)) {
            numFailures += 1;
        }

    // check O1
    if (!board.adjacentNotEmpty(14,1)) {
        numFailures += 1;
    }

    // check O13
    if (!board.adjacentNotEmpty(14,13)) {
        numFailures += 1;
    }

    // check G6, G4, F5, H5,(true)  F4, H6 (false)
    // G == 6
    // F == 5
    // H == 7 
    if (!board.adjacentNotEmpty(6,6)) {
        numFailures += 1;
    }
    if (!board.adjacentNotEmpty(6,4)) {
        numFailures += 1;
    }
    if (!board.adjacentNotEmpty(5,5)) {
        numFailures += 1;
    }
    if (!board.adjacentNotEmpty(7,5)) {
        numFailures += 1;
    }
    if (board.adjacentNotEmpty(5,4)) {
        numFailures += 1;
    }
    if (board.adjacentNotEmpty(7,6)) {
        numFailures += 1;
    }

    
    AssertAndReport(numFailures, 0, "Board_adjacentNotEmpty()");
    

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