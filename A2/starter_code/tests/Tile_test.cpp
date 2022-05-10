#include "../Tile.h"
#include <iostream>

int Tile_RunTests();

int Tile_TestGetLetter(){
    int numFailures = 0;

    //arrange
    Tile t;
    t = Tile('F', 16);

    //act
    char letter = t.getLetter();

    //assert
    std::cout << "Test Tile_TestGetLetter ";
    if (letter == 'F'){
        std::cout << "PASSED!" << std::endl;
    } else {
        std::cout << "FAILED!" << std::endl;
        numFailures++;
    }

    return numFailures;
}
int Tile_TestGetValue(){
    int numFailures = 0;

    //arrange
    Tile t;
    t = Tile('F', 16);

    //act
    int value = t.getValue();

    //assert
    std::cout << "Test Tile_TestGetValue ";
    if (value == 16){
        std::cout << "PASSED!" << std::endl;
    } else {
        std::cout << "FAILED!" << std::endl;
        numFailures++;
    }
    
    return numFailures;
}
int Tile_TestAsString(){
    int numFailures = 0;

    //arrange
    Tile t;
    t = Tile('F', 16);

    //act
    std::string s = t.getTileAsString();

    //assert
    std::cout << "Test Tile_TestAsString ";
    if (s == "F-16"){
        std::cout << "PASSED!" << std::endl;
    } else {
        std::cout << "FAILED!" << std::endl;
        numFailures++;
    }
    
    return numFailures;
}


int Tile_RunTests(){
    int numFailures = 0;

    numFailures += Tile_TestGetLetter();
    numFailures += Tile_TestGetValue();
    numFailures += Tile_TestAsString();

    std::cout << "Tile failures: " << numFailures << std::endl << std::endl;
    return numFailures;
}