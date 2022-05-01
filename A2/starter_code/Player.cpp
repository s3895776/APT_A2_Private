#include "Player.h"

Player::Player() {
    this->hand = LinkedList();
}

Player::~Player() {

}


std::string Player::saveGame() {

    // TODO: store hand as text 
    std::string handState;
    
    return handState;
}

std::string Player::placeTiles(LinkedList* tileBag) {
    // TODO: modify hand
    // TODO: modify game
    return "Placed Tiles";
}

std::string Player::replaceTile(LinkedList* tileBag) {
    // TODO: modify hand
    return "Replaced Tiles";
}

std::string Player::skip() {
    // TODO: skip turn
    return "Skipped Turn";
}

std::string Player::quit() {
    // TODO: delete all instances.
    return "Quit game";
}

std::string Player::setName(std::string name) {
    this->name = name;
    return "";
}

std::string Player::getHand() {
    // TODO: Return all elements of LinkedList as strings 
    // note: use Tile.getTileAsString(); to return 
    // the Tile in the appropriate string format. 
    // string format: Letter-Value

    std::string playerHand;
    return playerHand;
}

std::string Player::setHand(LinkedList* tileBag) {
    // TODO: fill in player hand to predefined max 
    // TODO: empty tileBag corresponding to the amount taken by player hand

    return "";
}

std::string Player::getName() {
    return name;
}