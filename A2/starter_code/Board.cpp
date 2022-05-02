#include "Board.h"

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
    return "in progress";
}
std::string Board::removeTile(Tile tile, std::string coordinates){
    return "in progress";
}

std::string Board::displayBoard(){
    return "in progress";
}