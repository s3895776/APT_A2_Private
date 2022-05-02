#include "Game.h"
#include <fstream>

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
    // all fields are on newlines. 
    
    // TODO: initialise players' name, score and hand

    // TODO: initialise 2d vector 

    // TODO: initialise tileBag 

    // TODO: Store the name of the currentPlayer
    std::string currentPlayerName;

    return currentPlayerName;
}

std::string Game::newGame() {
    // 1. Print a message for starting a new game
    // TODO: print outputs as appropriate throughout. 
    
    // 2. Ask for the player names
    // TODO: store the players names. 
    
    // TODO: initialise players in newGame() 
    const int NUMBER_PLAYERS = 2;
    int i = 0;
    
    while (i < NUMBER_PLAYERS) {
        players.push_back(Player());
        ++i;
    }

    i = 1;
    std::string playerName;

    while (i <= NUMBER_PLAYERS) {
        std::cout << "Enter a name for player " << i 
        << " (uppercase characters only)";
        std::cin >> playerName;
        players[i].setName(playerName);
    }

    // 3. Create a new game of Scrabble
    InitaliseBag(tileBag);

    // TODO: initialise Players One and Two LinkedList values with Tiles.

    // TODO: initialise 2d vector with starting values 


    // 4. Proceed with normal gameplay 
    std::string currentPlayerName = players[i].getName();
    // Let main call gameInput();

    return currentPlayerName;
}

void Game::InitaliseBag(LinkedList& bag){
    srand(2);   //seed random number
    int const num_tiles = 99;
    int const shuffle_n = 200;

    //import tiles from file into array
    Tile tiles[num_tiles];
    std::ifstream tileFile ("./ScrabbleTiles.txt");
    char letter; int value; int index = 0;
    while (tileFile.good() && index < num_tiles){
        tileFile >> letter;
        tileFile >> value;
        tiles[index] = Tile(letter, value);
        index++;
    }

    // shuffle tiles in array
    for (int i=0; i < shuffle_n; i++){
        int a = rand()%num_tiles;
        int b = rand()%num_tiles;
        //std::cout << "swapping tiles " << a << " <-> " << b << std::endl;
        Tile temp = tiles[a];
        tiles[a] = tiles[b];
        tiles[b] = temp;
    }

    // debug print array contents.
    //for (int i = 0; i < num_tiles; i++){
    //    std::cout << "["<< i <<"]"<< tiles[i].letter << "-" << tiles[i].value << std::endl;
    //}

    // insert tiles into bag
    for (int i = 0; i < 99; i++){
        bag.AddTile(tiles[i]);
    }

}

std::string Game::saveState() {
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
    // all fields are on newlines. 

    // TODO: put players information into gameState

    // TODO: put 2d vector into gameState 

    // TODO: put LinkedList tileBag as string into gameState

    // TODO: fill in the file with gameState.

    

    return "";
}

std::string Game::gameInput(std::string currentPlayerName) {
    // TODO: search for the player beginning their turn

    // TODO: Special Operation: Ending a Game
    // Condition: 1. The tile bag is empty, and
    // 2. One player has no more tiles in their hand or passes his turn twice.
    // • Display the end game message
    // • Display the scores
    // • Display the name of the winning player
    // • Then quit, according to Section 2.2.4.
    
    // TODO: implement turns within gameInput()
    // currentPlayer takes a turn, and the following 
    // player in vector players will continue
    // at the end, next player chosen will be the starting player

    // TODO: choose inputs for making the player move.

    // TODO: implement player action: placement
    // syntax: place <tile1> at <grid location>

    // TODO: implement player action: replace
    // syntax: replace <tile> (only one can be replaced)

    // TODO: implement player action: pass
    // syntax: pass

    // TODO: implement function: save
    // syntax: save saveFile

    // TODO: implement function: quit
    // syntax: quit

    // TODO: special character ^D
    // use the quit command.    

    // TODO: Invalid Input
    // syntax: any command not shown above

    // TODO: return an appropriate string 
    return "Something";
}

std::string Game::quitGame() {
    // TODO: end gameInput();

}

