#include "GameMessages.h"
#include <iostream>

void GameMessages::printCommandMessages() {
    // print all gameInput() commands
    std::cout << "Commands: " << std::endl;
    printValidPlaceSyntax();
    std::cout << "replace <letter> " << std::endl;
    std::cout << "pass " << std::endl;
    std::cout << "save <savedFile> " << std::endl;
    std::cout << "quit " << std::endl;
}

void GameMessages::printPlaceInvalidPlacement() {
    std::cout << "One or more tiles have invalid placements. " << std::endl;
    std::cout << "Tiles are not placed in a straight line or if ";
    std::cout << "the board is not empty, ";
    std::cout << "they are not placed adjacent to a current tile." 
    << std::endl;
}

void GameMessages::printPlaceInvalidCoordinate() {
    std::cout << "Invalid coordinates." << std::endl;
    std::cout << "Coordinate does not exist or ";
    std::cout << " coordinate is occupied. " << std::endl;

}

void GameMessages::printPlaceTileNotInHand() {
    std::cout << "Tile is not in player's hand." << std::endl;
    std::cout << "It is possible that you have tried to place ";
    std::cout << "a tile more times than your hand possesses." << std::endl;
}

void GameMessages::printValidPlaceSyntax() {
    std::cout << "place <letter> at <coordinate>" << std::endl;
    std::cout << "letter: A-Z, coordinates: A0 to O15";
    std::cout << " (single digits must be single)" << std::endl;
}

void GameMessages::printPlaceInvalidPlaceSyntax() {
    std::cout << "Placement input is invalid. Format: " << std::endl;
    printValidPlaceSyntax();
}

void GameMessages::printReplaceButBagEmpty() {
    std::cout << "Failed to replace. No tile left in the bag." << std::endl;
}

void GameMessages::printReplaceTileNotInHand() {
    std::cout << "Cannot replace tiles that do no exist in hand." << std::endl;
}

void GameMessages::printStartGameNoFirstPlayer() {
    std::cout << "Fatal error has occured: unable to find "
    << "first player. Aborting gameInput."
    << std::endl;
}

void GameMessages::printLoadGameFileDoesNotExist() {
    std::cout << "File was not found. Aborting load." << std::endl;
}
