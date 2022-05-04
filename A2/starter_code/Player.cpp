#include "Player.h"

Player::Player() {
    this->hand = LinkedList();
    score = 0;
}

Player::~Player() {

}

Player::Player(Player& other):
    hand(other.hand),
    name(other.name),
    score(other.score)
{}

Player::Player(const Player& other): 
    hand(other.hand),
    name(other.name),
    score(other.score)
{}


Tile Player::dropTile(Letter letter) {
    // TODO: remove tile from hand if letter exists. 

    Tile droppedTile;
    return droppedTile;
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

std::string Player::fillHand(Tile tile) {
    // TODO: fill a tile in the internal LinkedList player hand.

    return "";
}

std::string Player::getName() {
    return name;
}

std::string Player::addScore(int score) {
    this->score += score;
    return "";
}

int Player::getScore() {
    return this->score;
}