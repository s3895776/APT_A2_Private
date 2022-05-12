#include "../tests.h"
#include "../Tile.h"
#include <iostream>

int Tile_RunTests();

int Tile_TestGetLetter(){
    // Arrange
    Tile t;
    t = Tile('F', 16);

    // Act
    char letter = t.getLetter();

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport(letter, 'F', "Tile_TestGetLetter");

    return numFailures;
}
int Tile_TestGetValue(){
    // Arrange
    Tile t;
    t = Tile('F', 16);

    // Act
    int value = t.getValue();

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport(value, 16, "Tile_TestGetValue ");
    
    return numFailures;
}
int Tile_TestAsString(){
    // Arrange
    Tile t;
    t = Tile('F', 16);

    // Act
    std::string s = t.getTileAsString();

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport(s, "F-16", "Tile_TestGetValue ");
    
    return numFailures;
}

int Tile_RunTests(){
    int numFailures = 0;

    numFailures += Tile_TestGetLetter();
    numFailures += Tile_TestGetValue();
    numFailures += Tile_TestAsString();

    //std::cout << "    Tile Failures: " << numFailures << std::endl << std::endl;
    std::cout << std::endl;
    return numFailures;
}