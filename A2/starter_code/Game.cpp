#include "Game.h"
#include <fstream>
#include <random>
#include <iostream>

Game::Game() {
    tileBag = LinkedList();
    // board = new Board();
    
}

Game::~Game() {
}

std::string Game::run_menu() {
    std::string firstPlayer = "";
    bool menu = true;

    while (menu) {
        int choice = this->view_mainMenu();

        if (choice == 1) {
            firstPlayer = this->newGame();
            menu = false;

        }
        else if (choice == 2) {
            firstPlayer = this->loadGame();
            std::cout << "loading game" << std::endl;
            menu = false;
        }
        else if (choice == 3) {
            std::cout << this->displayCredits() << std::endl;
        }
        else if (choice == 4) {
            firstPlayer = "";
            std::cout << this->quitGame() << std::endl;
            menu = false;
        }

        // This is uncessary considering view_mainMenu() validates input
        // else {
        //     std::cout << "wrong choice" << std::endl;
        // }
    }

    return firstPlayer;

}

int Game::view_mainMenu() {
    int choice;
    bool inputReceived = false;

    // keep asking user for input until choice is initialised with a valid integer
    while (!inputReceived) {
        // prompt
        std::cout << std::endl;
        std::cout << "Menu" << std::endl;
        std::cout << "----" << std::endl;
        std::cout << "1. New Game" << std::endl;
        std::cout << "2. Load Game" << std::endl;
        std::cout << "3. Credits (Show student information)" << std::endl;
        std::cout << "4. Quit" << std::endl;
        std::cout << std::endl;

        // get integer input
        std::cout << "> ";

        if (std::cin.eof()){
            this->quitGame();
            return 4;
        }

        // reject invalid input which is not an integer between 1 and 4
        if (!(std::cin >> choice) || choice > 4 || choice < 1) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << std::endl;
            std::cout << "Input must be an integer between 1 and 4" << std::endl;
        }
        // accept valid input and end the loop
        else {
            inputReceived = true;
        }
    }
    return choice;
}

bool Game::validName(std::string name) {
    bool validName = true;
    // check if name is at least a single character long
    if (name.size() == 0) {
        validName = false;
    }
    // check if there is lowercase character
    for (char& c: name) {
        if (islower(c)) {
            validName = false;
        }
    }
    return validName;
}



std::string Game::newGame() {
    // 1. Print a message for starting a new game
    std::cout << std::endl;
    std::cout << "Starting a New Game" << std::endl;
    std::cout << std::endl;
    
    // Initialise players
    const int NUMBER_OF_PLAYERS = 2;
    // for each player, add pointer-to-player in players vector
    for (int i=0; i < NUMBER_OF_PLAYERS; i++) {
        Game::AddPlayer(Player());
    }

    // 2. Ask for the player names

    // fixed some printing errors with this method
    // I assume this flushes out std::cin? 
    std::cin.ignore();
    for (int i=0; i < NUMBER_OF_PLAYERS; i++) {   
        std::string playerName;
        // keep asking for player name until it is valid
        

        while (!validName(playerName)) {
            if (std::cin.eof()) {
                std::cout << this->quitGame();
                return "";
            }
            std::cout << "Enter a name for player " << i + 1 << " (uppercase characters only)" << std::endl;
            std::cout << "> ";
            std::getline(std::cin, playerName);
            // std::cout << playerName << std::endl;
            std::cout << std::endl;

        }

        // set the player's name
        this->players[i].setName(playerName);
    }

    // DEBUG: print the players names
    // for (int i=0; i < NUMBER_OF_PLAYERS; i++) { 
    //     std::cout << players[i].getName() << std::endl;
    // }

    std::cout << "Let's Play!" << std::endl;

    // 3. Create a new game of Scrabble
    InitaliseBag(tileBag);
    
    // Initialise Players hands with tiles from bag
    const int INITIAL_HAND = 10;
    int drawnHand = INITIAL_HAND - NUMBER_OF_PLAYERS;

    for (int i=0; i < NUMBER_OF_PLAYERS; i++) { 
        // number of players correlate to hand size 
        for (int j=0; j < drawnHand; j++) {  
            this->players[i].fillHand(tileBag.DrawTile());
        }
    }

    // TODO: initialise 2d vector with starting values 
    board = Board();

    // 4. Proceed with normal gameplay 
    // Let main call gameInput();

    return this->players[0].getName();
}

std::string Game::displayCredits() {
    std::string credits = "";
    credits.append("\n");
    credits.append("-------------------------------------\n");
    credits.append("Name: Dan Podbury\n");
    credits.append("Student ID: s3881206\n");
    credits.append("Email: s3881206@student.rmit.edu.au\n");
    credits.append("\n");
    credits.append("Name: Guo An Liew\n");
    credits.append("Student ID: s3895776\n");
    credits.append("Email: s3895776@student.rmit.edu.au\n");
    credits.append("\n");
    credits.append("Name: Kerubo Ndubi\n");
    credits.append("Student ID: s3844734\n");
    credits.append("Email: s3844734@student.rmit.edu.au\n");
    credits.append("\n");
    credits.append("Name: Min Min Oo\n");
    credits.append("Student ID: s3860838\n");
    credits.append("Email: s3860838@student.rmit.edu.au\n");
    credits.append("-------------------------------------\n");
    return credits;
}

/**
 * Save the state of game in the specified format:
 *      <player 1 name>
        <player 1 score>
        <player 1 hand>
        <player 2 name>
        <player 2 score>
        <player 2 hand>
        <Board State>
        <tile bag contents>
        <current player name>
    all fields are on newlines. 
        Format:
    • Name: ASCII text
    • Score: Integer
    • Player hand and tile bag: comma separated ordered list
    • Current board shape: Height, width
    • Board State: All tiles currently placed on the board should appear as a list of tile@position.
 */
bool Game::saveState(std::string filename) {
    std::string gameState;
    std::string path = "saves/";
    path.append(filename);
    path.append(".txt");

    std::ofstream file(path);
    
    // save name, score and hand of each player
    int playersSize = this->players.size();
    for (int i = 0; i < playersSize; ++i) {
        file << this->players[i].getName() << "\n";
        file << this->players[i].getScore() << "\n";
        file << this->players[i].getHand() << "\n";

        // DEBUG: preview output
        //std::cout << this->players[i].getName() << "\n";
        //std::cout << this->players[i].getScore() << "\n";
        //std::cout << this->players[i].getHand() << "\n";
    }

    // DEBUG: preview output
    //this->board.displayBoard();
    //std::cout << this->tileBag.ToString() << std::endl;

    // TODO: resolve - save board state
    // file << this->board.getBoard() << "\n";
    // TODO: resolve - save tile bag content
    // file << this->board.getTileContents() << "\n";
    // TODO: save cuurent player name
    // file << this->currentPlayer() << "\n";
    return true;
}

/**
 * Load the state of game in the specified format:
 *      <player 1 name>
        <player 1 score>
        <player 1 hand>
        <player 2 name>
        <player 2 score>
        <player 2 hand>
        <Board State>
        <tile bag contents>
        <current player name>
 */
std::string Game::loadGame() {  
    // get the filename to load
    std::string file;
    std::cout << "Enter the filename to load game" << std::endl;
    std::cout << "> ";
    std::cin >> file;

    std::string path = "saves/";
    path.append(file);
    path.append(".txt");

    std::ifstream fileLoaded(path);

    // file does not exist
    if (fileLoaded.fail()) {
        return "Failed Load / False";
    }
    // file successfully read
    else {
        const int NO_OF_PLAYERS = 2;
        // add players into vector
        for (int i=0; i < NO_OF_PLAYERS; ++i) {
             Game::AddPlayer(Player());
        }
        // load name, score and hand of each player
        std::string name, hand;
        int score;
        for (int i=0; i < NO_OF_PLAYERS; ++i) {
            fileLoaded >> name;
            fileLoaded >> score;
            fileLoaded >> hand;
            this->players[i].setName(name);
            this->players[i].addScore(score);
            // TODO: resolve - set player hand
            // this->players[i].fillHand(hand);
        }
        // TODO: resolve - load board state
        // fileLoaded >> this->board.loadBoard();
        // TODO: resolve - save tile bag content
        // fileLoaded >> this->board.loadTileContents();
        // TODO: load cuurent player name
        // std::string currentPlayer;
        // fileLoaded >> currentPlayer;
        // this->setCurrentPlayer(currentPlayer);
        return "Game Loaded / True";
    }
}

void Game::InitaliseBag(LinkedList& bag){
    // TODO(dan): test no duplicates, shuffle correct, etc...

    // Define consts
    int const num_tiles = 98;
    std::string const filename = "./ScrabbleTiles.txt";

    // Mersenne Twister PRNG
    //std::random_device r;
    //std::mt19937 rng(1);
    //TODO(dan): fix
    
    // Import tiles from file into array
    Tile tiles[num_tiles];
    std::ifstream tileFile (filename);
    char letter; int value; int index = 0;
    while (tileFile.good() && index <= num_tiles){
        tileFile >> letter;
        tileFile >> value;
        tiles[index] = Tile(letter, value);
        index++;
    }

    // Fisher–Yates shuffle
    int back = num_tiles - 1;
    while (back > 0){
        // Pick a random unshuffled elem
        //std::uniform_int_distribution<int> dist(0, back);
        int index = rand() % num_tiles;//dist(rand());

        // Move to back of list
        Tile temp = tiles[back];
        tiles[back] = tiles[index];
        tiles[index] = temp;

        // Slide unshuffled window down
        back--;
    }

    // Insert tiles into bag
    for (int i = 0; i < 99; i++){
        bag.AddTile(tiles[i]);
    }
}

std::string Game::gameInput(std::string firstPlayer) {

    // search for the player beginning their turn

    // use vector size to determine number of players at the start. 
    const int NUMBER_OF_PLAYERS = players.size();
    int currentPlayerIndex = -1;

    try {
    int i = 0;

        while (i < NUMBER_OF_PLAYERS) {

            if ((this->players[i].getName() == firstPlayer) &
            (currentPlayerIndex == -1) ) {
                currentPlayerIndex = i;
            }

            ++i;
        }    
        // // TEST: if the error prevents the rest of the code from executing
        // firstPlayerIndex = -1; 

        // if no modifications are made to firstPlayerIndex, 
        // a fatal error has occured. 
        if (currentPlayerIndex == -1) {
            throw currentPlayerIndex;
        }

    }
    catch (int x) {
        std::string Error = "Fatal error has occured: unable to find ";
        Error += "first player. Aborting gameInput.";
        std::cout << Error << std::endl;
        return "Goodbye\n";
    }

    // // try block will return Error message and end input for faulty
    // input. std::cout << "Success" << std::endl;
    
    // TODO: implement turns within gameInput()
    // currentPlayer takes a turn, and the following 
    // player in vector players will continue
    // at the end, next player chosen will be the starting player
    bool gameLoop = true;

    while (gameLoop) {

        // TODO: Special Operation: Ending a Game
        // Condition: 1. The tile bag is empty, and
        // 2. One player has no more tiles in their hand or passes his turn twice.
        // • Display the end game message
        // • Display the scores
        // • Display the name of the winning player
        // • Then quit, according to Section 2.2.4.

        if (tileBag.Count() == 0) {
            // stop conditions if the game has already ended

            // check every player in the vector. 
            for (Player& player : players) {

                if (gameLoop) {
                    // check players hand is empty
                    if (player.handEmpty()) {
                        // TODO: call method to display the end of the game. 
                        this->gameEnd();
                        gameLoop = false;
                    }

                    else if (player.skippedTwoTurns()) {
                        // TODO: call method to display the end of the game. 
                        this->gameEnd(); 
                        gameLoop = false;
                    }

                }

            }

        }

        // necessary if game ends in previous condition. 
        if (gameLoop) {
            std::string currPlayerName;
            std::string currHand;
            currPlayerName = players[currentPlayerIndex].getName();
            currHand = players[currentPlayerIndex].getHand(); 

            std::cout << currPlayerName << ", it's your turn" << std::endl;

            for (Player& player : players) {
                player.printScore();
            }

            // print the board
            this->board.displayBoard();

            std::cout << "Your hand is: " << std::endl;
            std::cout << currHand << std::endl;
            std::cout << std::endl;

            bool inputNotReceived = true;

            while (inputNotReceived) {
                std::cout << ">";

                // TODO: choose inputs for making the player move.
                // std::cin >> string
                // dissect the string into parts to get the right string. 
                std::string playerAction;
                std::cin >> playerAction;
                
                // TODO: remove after testing
                std::cout << playerAction << std::endl;

                // TODO: implement player action: placement
                // syntax: place <tile1> at <grid location>

                // TODO: implement player action: replace
                // syntax: replace <tile> (only one can be replaced)
                // syntax: place <tile1> at <grid location>
                // question: what order do the Tiles return in if the move
                // isn't legal?

                // TODO: save testing ground (delete after)
                // std::string filename;
                // std::cin >> filename;
                // this->saveState(filename);
                    
                // TODO: implement function: quit
                // syntax: quit

                // TODO: special character ^D
                // use the quit command.    

                // TODO: Invalid Input
                // syntax: any command not shown above

                //this->saveState("testSave.txt");

                // remove at the end of testing
                inputNotReceived = false;
            }
            
            // remove at the end of testing. 
            gameLoop = false;
        }

    }

    // TODO: return an appropriate string 
    std::cout << quitGame();
    return ("");
}

std::string Game::quitGame() {
    return "\nGoodbye\n";
}

std::string Game::gameEnd() {
    // Game over
    // Score for <player 1 name>: 000
    // Score for <player 2 name>: 000
    // Player <winner player name> won!
    std::cout << "Game over" << std::endl;
    Player playerHighestScore = players[0];

    for (Player& player : players) {
        player.printScore();

        if (playerHighestScore.getScore() < player.getScore()) {
            playerHighestScore = player;
        }

    }

    std::cout << "Player " << playerHighestScore.getName() << " won!" 
    << std::endl;

    return "";
}

void Game::AddPlayer(Player player){
    this->players.push_back(player);
}