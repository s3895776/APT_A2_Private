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
    // // DEBUG: print the TileBag after initialising.
    // std::cout<< this->tileBag.ToString() << std::endl;


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
    this->board.saveBoard(file);
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
    // Define consts
    int const num_tiles = 98;
    std::string const filename = "./ScrabbleTiles.txt";

    // Mersenne Twister PRNG
    std::random_device r;
    std::mt19937 rng(1);

    // Import tiles from file into array
    Tile tiles[num_tiles];
    std::ifstream tileFile (filename);
    
    // read letter and value per row
    char letter; int value; int index = 0;
    while (tileFile >> letter >> value) {
        tiles[index] = Tile(letter, value);
        ++index;
    }

    // Fisher–Yates shuffle
    int back = num_tiles - 1;
    while (back > 0) {
        // Pick a random unshuffled elem
        std::uniform_int_distribution<int> dist(0, back);
        int index = dist(rng);

        // Move to back of list
        Tile temp = tiles[back];
        tiles[back] = tiles[index];
        tiles[index] = temp;

        // Slide unshuffled window down
        back--;
    }

    // Insert tiles into bag
    for (int i = 0; i < num_tiles; i++){
        bag.AddTile(tiles[i]);
    }
}

std::string Game::gameInput(std::string firstPlayer) {

    // search for the player beginning their turn

    // use vector size to determine number of players at the start. 

    // validate that player exists. 
    int currentPlayerIndex = searchPlayer(firstPlayer);

    if (currentPlayerIndex == -1) {
        return "\nGoodbye\n";
    }
    
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
                    // check players have skipped two turns
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

            // Don't do this, because idk (causes double free for some reason)
            // Player currPlayer = players[currentPlayerIndex];

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
            std::string playerInput;
            

            while (inputNotReceived) {  
                playerInput = "";
                // this looks kinda strange to have two eof checks
                // but it works if EOF is not on a newline. 
                // i.e. if EOF follows an action, you still want to trigger
                // the action but you don't want to get more input. 
                if (std::cin.eof()) {
                    inputNotReceived = false;
                    gameLoop = false;
                }
                else {
                    std::cout << "> ";
                    // TODO: choose inputs for making the player move.
                    std::getline(std::cin, playerInput);
                }
                // TODO: special character ^D
                // exit the loop.   
                if (std::cin.eof() && (playerInput == "")) {
                    inputNotReceived = false;
                    gameLoop = false;
                }

                else {
                    // dissect the string into parts to get the right string. 
                    size_t pos = 0;
                    std::string playerAction;
                    std::string delimiter = " ";
                    pos = playerInput.find(delimiter);
                    playerAction = playerInput.substr(0, pos);
                    // if player action involves "place" then do the 
                    // appropriate action  
                    if (playerAction == "place") {
                        
                        // input validation: perform once here, perform again
                        // in recursive call. 
                        
                        if (this->validatePlaceTiles(playerInput)) {
                            std::string coordinates = playerInput.substr(11);
                            // check that the Tiles are adjacent to another coordinate,
                            // or some extremely convulted straight line check. 

                            // place V at B10
                            // 01234567891123
                            // if the space is empty, return true. Therefore,
                            // tile can be placed.
                            if (board.validAndEmpty(coordinates)) {
                                // check if player has the correct tile.
                                Letter tileLetter = playerInput[6]; 

                                if (players[currentPlayerIndex].hasTile(tileLetter)) {
                                    Tile tile = players[currentPlayerIndex].dropTile(tileLetter);
                                    std::cout << players[currentPlayerIndex].getHand();

                                    if (this->placeTiles(currentPlayerIndex, true, coordinates)) {

                                        std::string coordinates = playerInput.substr(11);
                                        // start to placeTiles (starts from lowest recursion)
                                        board.placeTile(tile, coordinates);
                                        inputNotReceived = false;
                                    }
                                    else {
                                        players[currentPlayerIndex].fillHand(tile);
                                        std::cout << players[currentPlayerIndex].getHand();

                                    }

                                }

                            }                            

                        }
                        if (inputNotReceived) {
                            std::cout << "Invalid input" << std::endl;
                        }

                    }
            

                    // TODO: implement player action: replace
                    // syntax: replace <tile> (only one can be replaced)
                    // syntax: place <tile1> at <grid location>
                    // question: what order do the Tiles return in if the move
                    // isn't legal?
                    else if (playerAction == "replace") {
                        
                        playerInput.erase(0, pos + delimiter.length());

                        // TEST: EOF follows an action, action should still
                        // trigger.
                        std::cout << "Trigger" << std::endl;
                        // if invalid input, do not accept. 
                        inputNotReceived = false;

                    }

                    // TODO: save testing ground (delete after)
                    // std::string filename;
                    // std::cin >> filename;
                    // this->saveState(filename);
                    // this->saveState("testSave.txt");
                    else if (playerAction == "save") {
                        playerInput.erase(0, pos + delimiter.length());

                        inputNotReceived = false;
                    }
                        
                    // TODO: implement function: quit
                    // syntax: quit
                    else if (playerAction == "quit") {
                        inputNotReceived = false;
                        gameLoop = false;
                    }


                    // TODO: Invalid Input
                    // syntax: any command not shown above
                    else {
                        std::cout << "Invalid Input" << std::endl;
                    }
                }

                // remove at the end of testing
                // inputNotReceived = false;
            }
            
            // remove at the end of testing. 
            // gameLoop = false;
        }

    }

    // TODO: return an appropriate string 
    std::cout << quitGame();
    return "";
}

bool Game::placeTiles(int currentPlayerIndex, bool prevValid, std::string prevCoordinate) {
    // continue until "Done" is reached - do not accept
    // input that isn't formatted correctly.

    if (std::cin.eof()) {
        // for convenience
        // this is for inline EOF. Will only occur given that 
        // place Done does not come before the EOF.  
        return false;
    }

    bool tilesPlaced = false;
    std::string playerInput;
    std::cout << "> ";
    std::getline(std::cin, playerInput);
    // std::string done = playerInput.substr(6);
    // char tileFace = '0';
    bool validMove = false;
    Tile tileToPlace;

    
    if (std::cin.eof() && playerInput == "") {
        // input ends on a newline. Therefore, 
        // no place Done is given. 
        tilesPlaced = false;
    }

    // base case 1: playerInput done. 
    // note that regardless of syntax or valid board placements, 
    // it will allow the user to enter sentences as they wish,
    // until playerInput becoems "place Done".
    else if (playerInput == "place Done") {
        tilesPlaced = true;
    } 

    // if prevValid was not valid, this triggers. 
    // essentially no validation is necessary because its already wrong
    // just waiting for place Done or EOF before recursion can end. 
    else if (!prevValid) {
        this->placeTiles(currentPlayerIndex, false, prevCoordinate);
    }

    else {
        
        if (this->validatePlaceTiles(playerInput)) {
            std::string coordinates = playerInput.substr(11);
            // check if coordinates are adjacent 


            if (board.validAndEmpty(coordinates)) {

                // check if player has the correct tile.
                Letter tileLetter = playerInput[6]; 

                if (players[currentPlayerIndex].hasTile(tileLetter)) {
                    // drop the tile before recursing.
                    tileToPlace = players[currentPlayerIndex].dropTile(tileLetter);
                    // TEST: cheat
                    std::cout << players[currentPlayerIndex].getHand();

                    // the recursion for correct moves. 
                    validMove = this->placeTiles(currentPlayerIndex, true, coordinates);
                    if (!validMove) {
                        players[currentPlayerIndex].fillHand(tileToPlace);
                    }
                }

            }

        }

    }
    
    // all above cases pass.
    if (validMove) {
        std::string coordinates = playerInput.substr(11);
        // Tile tile = players[currentPlayerIndex].dropTile(tileLetter);
        // start to placeTiles (starts from lowest recursion)
        board.placeTile(tileToPlace, coordinates);
        tilesPlaced = true;
    }
    
    // do a pointless recursion (still accept input regardless 
    // of invalid input)
    else if (!tilesPlaced) {
        this->placeTiles(currentPlayerIndex, false, prevCoordinate);
    }

    // TODO: implement player action: placement
    // syntax: place <tile1> at <grid location>
    // need to implement the checks that are necessary.

    // Tile tile;
    // //check if the player has the tile
    // if (players[currentPlayerIndex].hasTile(tileFace)){
    //     tile = players[currentPlayerIndex].dropTile(tileFace);
    // }
    // success = board.placeTile(tile, coord);
    // if (success){
    //     std::cout << "Tile placed" << std::endl;
    // }
    // // Do we need a possible list of actions made in the turn to keep 
    // // track of what we may want to remove from board and replace in hand?
    return tilesPlaced;
    
}

bool Game::validatePlaceTiles(std::string placeSentence) {

    bool validTilePlacement = true;
    size_t pos = 0;
    std::string playerAction;
    std::string delimiter = " ";
    pos = placeSentence.find(delimiter);
    playerAction = placeSentence.substr(0, pos);
    // WORKS
    // TODO: validate
    // source is from stack overflow split string. 

    // erase "place"
    placeSentence.erase(0, pos + delimiter.length());
    std::string TileString = "";
    std::string atToken = "";
    bool continueValidation = true;
    // WORKS

    if ( (pos = placeSentence.find(delimiter) ) 
    != std::string::npos) {
        TileString = placeSentence.substr(0, pos);
        placeSentence.erase(0, pos + delimiter.length());
    }

    // check if the next input is at least one letter. 
    if (TileString.length() != 1) {
        validTilePlacement = false;
        continueValidation = false;
    }   
    // check if the 
    if ( (pos = placeSentence.find(delimiter) ) 
    != std::string::npos && (continueValidation)) {
        atToken = placeSentence.substr(0, pos);
        placeSentence.erase(0, pos + delimiter.length());
    }
    if (atToken != "at" && (continueValidation)) {
        validTilePlacement = false;
        continueValidation = false;
    }

    if (continueValidation) {
        // Don't actually check for correct coordinates, just length.
        // valid coordinates should be checked afterwards.
        if (placeSentence.length() >= 2) {
            
            //B10
            //ROWCOL
            validTilePlacement = board.validCoordinate(placeSentence);
        }
        else {
            validTilePlacement = false;
        }  
    }
    return validTilePlacement;

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



int Game::searchPlayer(std::string currentPlayer) {
    const int NUMBER_OF_PLAYERS = players.size();
    int currentPlayerIndex = -1;

    try {
    int i = 0;

        while (i < NUMBER_OF_PLAYERS) {

            if ((this->players[i].getName() == currentPlayer) &
            (currentPlayerIndex == -1) ) {
                currentPlayerIndex = i;
            }

            ++i;
        }    
        // // TEST: if the error prevents the rest of the code from executing
        // currentPlayerIndex = -1; 

        // if no modifications are made to currentPlayerIndex, 
        // a fatal error has occured. 
        if (currentPlayerIndex == -1) {
            throw currentPlayerIndex;
        }

    }
    catch (int x) {
        std::string Error = "Fatal error has occured: unable to find ";
        Error += "first player. Aborting gameInput.";
        std::cout << Error << std::endl;
    }

    return currentPlayerIndex;
}