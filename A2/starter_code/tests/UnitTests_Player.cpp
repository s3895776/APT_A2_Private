#include "../tests.h"
#include "../Player.h"
#include <iostream>

Player CreateTestPlayer(){
    Player p;
    Tile t1 = Tile('A',1);
    Tile t2 = Tile('B',2);
    Tile t3 = Tile('C',3);

    p.fillHand(t1);
    p.fillHand(t2);
    p.fillHand(t3);

    return p;
}

// DEFINE TESTS
int Player_GetHand(){
    // Arrange
    Player p = CreateTestPlayer();

    // Act
    std::string hand = p.getHand();

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport(hand, "A-1, B-2, C-3", "Player_GetHand");
    
    return numFailures;
}

int Player_DropTile(){
    // Arrange
    Player p = CreateTestPlayer();

    // Act
    Tile t = p.dropTile('B');
    std::string hand = p.getHand();

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport(t.getTileAsString(), "B-2", "Player_DropTile_ReturnsTile");
    numFailures += AssertAndReport(hand, "A-1, C-3", "Player_DropTile_HandUpdated");

    return numFailures;
}

int Player_FillHand(){
    // Arrange
    Player p = CreateTestPlayer();

    // Act
    Tile t = Tile('D', 4);
    p.fillHand(t);
    std::string hand = p.getHand();

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport(hand, "A-1, B-2, C-3, D-4", "Player_FillHand");

    return numFailures;
}
int Player_ChangeScore(){
    // Arrange
    Player p = CreateTestPlayer();

    // Act
    p.addScore(5);
    int score = p.getScore();

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport(score, 5, "Player_ChangeScore");

    return numFailures;
}

// RUN TESTS
int Player_RunTests(){
    int numFailures = 0;

    numFailures += Player_ChangeScore();
    numFailures += Player_FillHand();
    numFailures += Player_GetHand();
    numFailures += Player_DropTile();

    //std::cout << "Player failures: " << numFailures << std::endl << std::endl;
    std::cout << std::endl;
    return numFailures;
}