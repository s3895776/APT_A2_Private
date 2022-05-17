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
    board.placeTile(tile, "A0");

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
    Board filledBoard2;
    Board filledBoard3;
    Tile tile = Tile('A', 1);
    filledBoard.placeTile(tile, "A0");

    if ( filledBoard.boardEmpty()) {
        std::cout << "yo this board ain't filled at all";
    }

    std::vector<std::string> projectedCoordinates;
    int numFailures = 0;

    // Act

    // 1: empty board, one tile 
    projectedCoordinates.push_back("A1");
    // place A1: expect true
    if (!emptyBoard.checkBoardAdjacency(projectedCoordinates) ) {
        std::cout << "Failed for empty board, one tile" << std::endl;
        numFailures += 1;
    }

    // 2: A0 filled, one tile 
    // place A1 next to A0: expect true
    if (!filledBoard.checkBoardAdjacency(projectedCoordinates)) {
        std::cout << "Failed for A0 filled, one tile" << std::endl;
        numFailures += 1;
    }
    

    // 3: empty board, invalid placement of several tiles
    projectedCoordinates.push_back("A3");
    // place A3 and A1: expect false
    if (emptyBoard.checkBoardAdjacency(projectedCoordinates)) {
        std::cout << "Failed for empty board, invalid placement of several tiles" << std::endl;
        numFailures += 1;
    }

    // 4: empty board, placement valid of several tiles
    projectedCoordinates.push_back("A2");

    // check A1, A2, A3, empty board, expect true.

    if (!emptyBoard.checkBoardAdjacency(projectedCoordinates)) {
        std::cout << "Failed for empty board, placement valid of several tiles" << std::endl;
        numFailures += 1;

    }

    // 5: A0 filled, invalid placement
    projectedCoordinates.clear();
    projectedCoordinates.push_back("A3");
    projectedCoordinates.push_back("A2");
    // for (std::string& coordinates : projectedCoordinates) {
    //     std::cout << coordinates << std::endl;
    // }

    // place A2, A3, expect false.

    if (filledBoard.checkBoardAdjacency(projectedCoordinates)) {
        std::cout << "Failed for A0 filled invalid placement" << std::endl;
        numFailures += 1;

    }

    // 6: A0 filled, valid placement. 
    // place A1, A2, A3, expect true.
    projectedCoordinates.push_back("A1");

    // for (std::string& coordinate : projectedCoordinates) {
    //     std::cout << coordinate << std::endl;
    // }
    if (!filledBoard.checkBoardAdjacency(projectedCoordinates)) {
        std::cout << "Failed for A0 filled, valid placement." << std::endl;
        numFailures += 1;
    }

    
    projectedCoordinates.clear();
    projectedCoordinates.push_back("A5");
    projectedCoordinates.push_back("A8");
    // between A5 and A8, some check for A6 should appear 
    // also ensure that the other non-empty check does not 
    // get in the way. 
    filledBoard2.placeTile(tile, "B5");
    

    // 7. No tiles exist between two. 
    // expect false.
    if (filledBoard2.checkBoardAdjacency(projectedCoordinates)) {
        std::cout << "Failed for A5-A8, none filled, invalid placement." << std::endl;
        numFailures += 1;
    }

    // 8. One tile exists but others do not. 
    // expect false
    filledBoard2.placeTile(tile, "A6");

    if (filledBoard2.checkBoardAdjacency(projectedCoordinates)) {
        std::cout << "Failed for for A5-A8, A6 filled, invalid placement." << std::endl;
        numFailures += 1;
    }

    // 9. Tiles exist between two of them
    // expect true.
    filledBoard2.placeTile(tile, "A7");
    if (!filledBoard2.checkBoardAdjacency(projectedCoordinates)) {
        std::cout << "Failed for for A5-A8, A6-A7 filled, valid placement." << std::endl;
        numFailures += 1;
    }

    // do the same for 10-12 but with the same row instead.

    // 10. No tiles exist between two. 
    // expect false.

    projectedCoordinates.clear();
    projectedCoordinates.push_back("A5");
    projectedCoordinates.push_back("D5");
    filledBoard3.placeTile(tile, "A4");

    if (filledBoard3.checkBoardAdjacency(projectedCoordinates)) {
        std::cout << "Failed for A5-D5, none filled, invalid placement." << std::endl;
        numFailures += 1;
    }

    // 11. One tile exists but others do not. 
    // expect false
    filledBoard3.placeTile(tile, "B5");

    if (filledBoard3.checkBoardAdjacency(projectedCoordinates)) {
        std::cout << "Failed for for A5-D5, B5 filled, invalid placement." << std::endl;
        numFailures += 1;
    }

    // 12. Tiles exist between two of them
    // expect true.
    filledBoard3.placeTile(tile, "C5");
    if (!filledBoard3.checkBoardAdjacency(projectedCoordinates)) {
        std::cout << "Failed for for A5-D5, B5-C5 filled, valid placement." << std::endl;
        numFailures += 1;
    }

    // 13: for board3, check B6 and A5: should be false,
    //  can't place in different directions.
    projectedCoordinates.clear();
    projectedCoordinates.push_back("A5");
    projectedCoordinates.push_back("B6");
    projectedCoordinates.push_back("B7");
    projectedCoordinates.push_back("B8");
    projectedCoordinates.push_back("B9");
    

    if (filledBoard3.checkBoardAdjacency(projectedCoordinates)) {
        std::cout << "Failed for for A5 & B6-B9, B5 filled, invalid placement." << std::endl;
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
    
    // check A2 
    if (board.adjacentNotEmpty(0,2)) {
        numFailures += 1;
    }

    // check A3 
    if (board.adjacentNotEmpty(0,3)) {
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
int Board_TestGetScore(){
    int numFailures = 0;
    Board board;
    std::vector<std::vector<Tile>> tilesPlaced(15, std::vector<Tile>(15, Tile()));
    /* BOARD OUTPUT VISUALISATION
         0   1   2   3   4   5   6   7   8   9  10  11  12  13  14 
       -------------------------------------------------------------
     A |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     B |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     C |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     D |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     E |   |   |   |   | S |   |   |   |   |   |   |   |   |   |   |
     F |   |   |   |   | T |   |   |   |   |   |   |   |   |   |   |
     G |   |   | B | O | A | R | D |   |   |   |   |   |   |   |   |
     H |   |   | R |   | R | E |   |   |   |   |   |   |   |   |   |
     I |   |   | E |   | E | E |   |   |   |   |   |   |   |   |   |
     J |   |   | E |   |   | D |   |   |   |   |   |   |   |   |   |
     K |   |   | Z |   |   |   |   |   |   |   |   |   |   |   |   |
     L |   |   | E | V | E | R |   |   |   |   |   |   |   |   |   |
     M |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     N |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     O |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    */
    
    /* Value Cheat Sheet 
        Value   Letter
        1       A, E, I, O, U, L, N, S, T, R
        2       D, G
        3       B, C, M, P
        4       F, H, V, W, Y
        5       K
        8       J, X
        10      Q, Z
    */

    //Setup Board
    Tile A = Tile('A',1);
    Tile B = Tile('B',3);
    Tile D = Tile('D',2);
    Tile E = Tile('E',1);
    Tile R = Tile('R',1);
    Tile T = Tile('T',1);
    Tile S = Tile('S',1);
    Tile O = Tile('O',1);
    Tile V = Tile('V', 4);
    Tile Z = Tile('Z',10);
    //state before turn
    int score = 0;
    board.placeTile(A,"G4");
    board.placeTile(R,"G5");
    board.placeTile(D,"G6");
    board.placeTile(O,"G3");
    board.placeTile(B,"G2");
    // state during turn
    // score should equal 4, board.getScore should equal 4
    
    board.placeTile(S,"E4");
    tilesPlaced[board.getRow("E4")][board.getCol("E4")] = S;
    board.placeTile(T,"F4");
    tilesPlaced[board.getRow("F4")][board.getCol("F4")] = T;
    board.placeTile(R,"H4");
    tilesPlaced[board.getRow("H4")][board.getCol("H4")] = R;
    score += board.getScore(tilesPlaced);
    if (score != 4){
        numFailures += 1;
    }
    for (int i = 0; i < ROW; ++i){
        for (int j = 0; j < COLUMN; ++j){
            tilesPlaced[i][j] = Tile();
        }
    }
    // score should equal 9, board.getScore should equal 5
    board.placeTile(E,"I4");
    tilesPlaced[board.getRow("I4")][board.getCol("I4")] = E;
    score += board.getScore(tilesPlaced);
    std::cout << score <<std::endl;
    if (score != 9){
        numFailures += 1;
    }
    for (int i = 0; i < ROW; ++i){
        for (int j = 0; j < COLUMN; ++j){
            tilesPlaced[i][j] = Tile();
        }
    }
    // Score should equal 26, board.getScore should equal 17
    board.placeTile(R,"H2");
    tilesPlaced[board.getRow("H2")][board.getCol("H2")] = R;
    board.placeTile(E,"I2");
    tilesPlaced[board.getRow("I2")][board.getCol("I2")] = E;
    board.placeTile(E,"J2");
    tilesPlaced[board.getRow("J2")][board.getCol("J2")] = E;
    board.placeTile(Z,"K2");
    tilesPlaced[board.getRow("K2")][board.getCol("K2")] = Z;
    board.placeTile(E,"L2");
    tilesPlaced[board.getRow("L2")][board.getCol("L2")] = E;
    score += board.getScore(tilesPlaced);
    if (score != 26){
        numFailures += 1;
    }
    for (int i = 0; i < ROW; ++i){
        for (int j = 0; j < COLUMN; ++j){
            tilesPlaced[i][j] = Tile();
        }
    }
    // score should equal 31
    board.placeTile(E,"H5");
    tilesPlaced[board.getRow("H5")][board.getCol("H5")] = E;
    board.placeTile(E,"I5");
    tilesPlaced[board.getRow("I5")][board.getCol("I5")] = E;
    board.placeTile(D,"J5");
    tilesPlaced[board.getRow("J5")][board.getCol("J5")] = D;
    score += board.getScore(tilesPlaced);
    
    if (score != 32){
        numFailures += 1;
    }
    for (int i = 0; i < ROW; ++i){
        for (int j = 0; j < COLUMN; ++j){
            tilesPlaced[i][j] = Tile();
        }
    }
    board.placeTile(V,"L3");
    tilesPlaced[board.getRow("L3")][board.getCol("L3")] = V;
    board.placeTile(E,"L4");
    tilesPlaced[board.getRow("L4")][board.getCol("L4")] = E;
    board.placeTile(R,"L5");
    tilesPlaced[board.getRow("L5")][board.getCol("L5")] = R;
    score += board.getScore(tilesPlaced);
    if (score != 39){
        numFailures += 1;
    }

    AssertAndReport(numFailures, 0, "Board_getScore");
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
    numFailures += Board_TestGetScore();

    //std::cout << "    Board Failures: " << numFailures << "\n\n";
    std::cout << std::endl;
    return numFailures;
}