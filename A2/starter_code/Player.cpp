#include "Player.h"

Player::Player() {
    this->hand = LinkedList();
    score = 0;
    turnsSkipped = 0;
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
    Tile dummyTile = Tile(letter, 0);
    Tile& dummyTileRef = dummyTile;
    // get the first letter in hand to do things with

    Tile droppedTile = hand.DrawTile( dummyTileRef );
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

    return this->hand.ToString();
}

std::string Player::fillHand(Tile tile) {
    // TODO: fill a tile in the internal LinkedList player hand.
    // just copy the tile and let LinkedList manage pointers to tile
    this->hand.AddTile(tile);
    
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

bool Player::handEmpty() {
    // TODO:: determine if hand is empty
    bool handIsEmpty = false;

    // hard to determine if this is the right method
    if (hand.Count() == 0) {
        handIsEmpty = true;
    }

    return handIsEmpty;
}

std::string Player::skippedTurn() {
    turnsSkipped += 1;
    return "";
}

std::string Player::turnNotSkipped() {
    turnsSkipped = 0;
    return "";
}

bool Player::skippedTwoTurns() {
    bool twoOrMoreTurns = false;

    if (turnsSkipped >= 2) {
        twoOrMoreTurns = true;
    }

    return twoOrMoreTurns;
}

std::string Player::printScore() {
    std::cout << "Score for " << this->getName();
    std::cout << ": " << this->getScore() << std::endl;
    return "";
}