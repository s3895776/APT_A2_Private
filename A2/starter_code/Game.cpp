#include "Game.h"

Game::Game() {
    tileBag = LinkedList();
}

Game::~Game() {

}

std::string Game::modifyBoard(std::vector<Tile> tilesToPlace, std::vector<std::string> coordinates) {
    std::string boardState;
    // TODO: modify the 2d vector 

    // TODO: revert board if invalid move.

    // TODO: award points if successful move.
    return boardState;
}

std::string Game::awardPoints() {
    // TODO: award points 
    return "Points awarded";
}

std::string Game::invalidMove() {
    // TODO: revert board 
    return "Invalid move";
}

std::string Game::loadGame(std::string saveFile) {
    // TODO: initialise 2d vector with string value

    // TODO: initialise tileBag with string value
    return "Loaded Game";
}

std::string Game::newGame() {
    // TODO: initialise 2d vector with starting values 

    // TODO: initialise tileBag with starting values

    return "Game Start";
}

std::string Game::saveState() {
    // TODO: return string for file to read 
    std::string gameState;
    // TODO: put 2d vector into gameState 

    // TODO: put LinkedList tileBag into gameState

    return gameState;
}

std::string Game::turnEnd() {
    // TODO: switch player control
    return "End turn";
}
