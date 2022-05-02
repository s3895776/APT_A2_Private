
#include "Board.h"

Board::Board(){

    int n = 15;
    int m = 15;
    Tile* tile = nullptr;
    std::vector<std::vector<Tile>> b(n, std::vector<Tile> (m, *tile));
    
    this->board = b;
 
}
Board::~Board(){

}
Board::Board(Board& other){

}

std::string Board::placeTile(Tile tile, std::string coordinates){

}
std::string Board::removeTile(Tile tile, std::string coordinates){

}

std::string Board::displayBoard(){

}