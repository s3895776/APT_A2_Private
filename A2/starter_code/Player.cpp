#include "Player.h"

Player::Player() {
    this->game = Game();
    this->hand = LinkedList();
}

Player::~Player() {
    // the ADT's will delete themselves
    // when the scope finishes. 
}

std::string Player::loadGame(std::ifstream& fileLoad) {
    // TODO: fill in proper values to load the board state
    // required values to fill: board 2d vector, LinkedList tileBag
    std::string boardState = "";

    // TODO: test loadGame function
    game.loadGame(boardState);

    // TODO: do something with hand 
    std::string handState = "";
    
    return "Loaded game";
}

std::string Player::saveGame(std::ifstream& fileSave) {
    // TODO: store game as text
    std::string saveState = game.saveState();
    // TODO: store hand as text 
    std::string handState;
    
    return "Saved game";
}

std::string Player::placeTiles() {
    // TODO: modify hand
    // TODO: modify game
    // game.modifyBoard();
    return "Placed Tiles";
}

std::string Player::replaceTiles() {
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
