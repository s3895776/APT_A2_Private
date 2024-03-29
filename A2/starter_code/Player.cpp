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
    score(other.score),
    turnsSkipped(other.turnsSkipped)
{}

Player::Player(const Player& other): 
    hand(other.hand),
    name(other.name),
    score(other.score),
    turnsSkipped(other.turnsSkipped)
{}

bool Player::hasTile(Letter letter){
    return this->hand.ContainsTile(letter);
}

Tile Player::dropTile(Letter letter) {
    Tile dummyTile = Tile(letter, 0);
    Tile& dummyTileRef = dummyTile;
    // get the first letter in hand to do things with

    Tile droppedTile = hand.DrawTile( dummyTileRef );
    return droppedTile;
}
// need a replace tile in the case that the turn is not valid and all the tiles need to be replaced?

std::string Player::setName(std::string name) {
    this->name = name;
    return "";
}

std::string Player::getHand() {
    return this->hand.ToString();
}

void Player::fillHand(Tile tile) {
    // Fill a tile in the internal LinkedList player hand.
    // just copy the tile and let LinkedList manage pointers to tile
    this->hand.AddTile(tile);
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
    // Determine if hand is empty
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

    return (turnsSkipped >= 2);
}

std::string Player::printScore() {
    std::cout << "Score for " << this->getName();
    std::cout << ": " << this->getScore() << std::endl;
    return "";
}

bool Player::hasLetter(Letter letter) {
    bool letterFound = false;
    std::string handString = this->getHand();
    int handStringLength = handString.length();
    for (int i = 0; i < handStringLength; ++i) {
        if (handString[i] == letter) {
            letterFound = true;
        }
    }
    return letterFound;
}

int Player::sizeOfHand() {
    return this->hand.Count();
}