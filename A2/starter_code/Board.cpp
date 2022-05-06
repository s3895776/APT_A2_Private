#include "Board.h"
#include <array>
#include <iostream>

Board::Board(){

    // need to # define and typedef
    int row = 15;
    //int cols = 15;
    
    std::vector<std::vector<Tile>> b(row, std::vector<Tile> ());
    
    this->board = b;
 
}
Board::~Board(){

}
Board::Board(Board& other){

}

std::string Board::placeTile(Tile tile, std::string coordinates){
    /* convert the coordinates into rows and cols */ 
    row = coordinates.back();
    char c = coordinates.front();
    // Make an array or list that has all of the letters and check if the 
    column = 0;
    board[row][column] = tile;
    return "in progress";
}
std::string Board::removeTile(Tile tile, std::string coordinates){
    return "in progress";
}

std::string Board::displayBoard(){
    return "in progress";
}