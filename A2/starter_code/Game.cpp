#include "Game.h"

Game::Game() {
    tileBag = LinkedList();
    playerOne = Player();
    playerTwo = Player();
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

std::string Game::loadGame(std::iostream& saveFile) {
    // saveFile format:
    // <player 1 name>
    // <player 1 score>
    // <player 1 hand>
    // <player 2 name>
    // <player 2 score>
    // <player 2 hand>
    // <Board State>
    // <tile bag contents>
    // <current player name>
    // (For info on the assignment spec)

    // TODO: initialise players' name, score and hand

    // TODO: initialise 2d vector 

    // TODO: initialise tileBag 

    // Give the name of the first player

    return "Loaded Game";
}

std::string Game::newGame() {
    // 1. Print a message for starting a new game
    // TODO: print outputs as appropriate throughout. 
    
    // 2. Ask for the player name
    // TODO: store the players names. 
    std::string playerName;
    
    // playerOne.fillName(playerName);
    // playerTwo.fillName(playerName);

    // 3. Create a new game of Scrabble
    // TODO: initialise Players One and Two LinkedList values with Tiles.

    // TODO: initialise 2d vector with starting values 

    // TODO: initialise tileBag with starting values

    // 4. Proceed with normal gameplay.
    // TODO: begin gameInput();

    return "Game Start";
}

std::string Game::saveState() {
    // TODO: return string for file to read 
    std::string gameState;
    // gameState format:
    // <player 1 name>
    // <player 1 score>
    // <player 1 hand>
    // <player 2 name>
    // <player 2 score>
    // <player 2 hand>
    // <Board State>
    // <tile bag contents>
    // <current player name>
    // (For info on the assignment spec)

    // TODO: put players information into gameState

    // TODO: put 2d vector into gameState 

    // TODO: put LinkedList tileBag as string into gameState

    return gameState;
}

std::string Game::gameInput() {

    // TODO: choose inputs for making the player move.

    // TODO: implement turns within gameInput()
    // Player one takes turn, Player two takes turn,
    // then loop to playerOnes' turn. 

    // TODO: return an appropriate string 
    return "Something";
}

std::string Game::quitGame() {
    // TODO: end gameInput();

}