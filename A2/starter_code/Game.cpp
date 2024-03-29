#include "Game.h"
#include <fstream>
#include <random>
#include <iostream>
#include <algorithm>

Game::Game() {
    tileBag = LinkedList();  
    std::vector<std::vector<Tile>> b(ROW, std::vector<Tile>(COLUMN, Tile()));
    // this->scoreTilesPlaced = b;
    std::random_device seed;
    this->seed = seed();

}

Game::Game(int seed) {
    tileBag = LinkedList(); 
    std::vector<std::vector<Tile>> b(ROW, std::vector<Tile>(COLUMN, Tile()));
    // this->scoreTilesPlaced = b;
    this->seed = seed; 
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
            menu = false;
        }
        else if (choice == 3) {
            std::cout << this->displayCredits() << std::endl;
        }
        else if (choice == 4) {
            std::cout << this->quitGame() << std::endl;
            menu = false;
        }

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

        // reject input if it is not between 1 and 4
        if (!(std::cin >> choice) || !(validMainMenuChoice(choice))) {
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

bool Game::validMainMenuChoice(int choice) {
    bool validChoice = false;
    if (choice >= 1 && choice <= 4) {
        validChoice = true;
    }
    return validChoice;
}

bool Game::validName(std::string name) {
    bool validName = true;
    // check if name is at least a single character long
    if (name.size() == 0) {
        validName = false;
    }
    // check if there is lowercase character
    for (char& c: name) {
        if (!isupper(c)) {
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
    std::cin.ignore();
    
    // Initialise players
    // get the number of players from the player first 
    bool numberOfPlayersGiven = false;
    int num_players = 0;

    while (!numberOfPlayersGiven) {
        GameMessages::printValidPlayerCount();
        // reset on each loop is necessary.
        num_players = 0;
        std::string string_num_players;

        if (std::cin.eof()) {
            numberOfPlayersGiven = true;
        }

        else {
            std::cout << "> ";
            // TODO: choose inputs for making the player move.
            std::getline(std::cin, string_num_players);
        }

        // ignore the rest of input
        if (std::cin.eof() ) {
            numberOfPlayersGiven = true;
        }

        else {
            try {
                num_players = std::stoi(string_num_players);
                const int MAX_PLAYERS = 4;
                const int MIN_PLAYERS = 2;
                if (num_players < MIN_PLAYERS || num_players > MAX_PLAYERS) {
                    throw num_players;
                }
                numberOfPlayersGiven = true;
            }

            catch (std::invalid_argument& e) {
                std::cout << "Invalid number of players" << std::endl;
            }

            catch (int x) {
                std::cout << "Invalid number of players" << std::endl;
            }

        }


    }

    // bit of a strange assignment here now that I've converted 
    // the number of players to an integer 
    std::string firstPlayer = "";
    if (num_players == 0) {
        // do nothing 
    }
    
    else {
        const int NUMBER_OF_PLAYERS = num_players;
        // for each player, add pointer-to-player in players vector
        for (int i=0; i < NUMBER_OF_PLAYERS; i++) {
            Game::AddPlayer(Player());
        }

        // 2. Ask for the player names

        // fixed some printing errors with this method
        // I assume this flushes out std::cin? 
        // I believe this will cause an extra line to be ignored if called twice.
        // I was correct, so I have commented this out for reference.
        // std::cin.ignore();

        for (int i=0; i < NUMBER_OF_PLAYERS; i++) {   
            std::string playerName;
            // keep asking for player name until it is valid

            while (!validName(playerName)) {
                GameMessages::printValidName();
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
        const int INITIAL_HAND = 7;
        
        // int drawnHand = INITIAL_HAND - NUMBER_OF_PLAYERS;
        // uncertain about the rules saying less players == less drawnHand
        int drawnHand = INITIAL_HAND;

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
        firstPlayer = this->players[0].getName();
    }

    return firstPlayer;
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
bool Game::saveState(std::string filename, std::string currPlayerName) {
    std::string gameState;
    std::string path = "saves/";
    path.append(filename);
    path.append(".txt");

    std::ofstream file(path);
    
    // save name, score and hand of each player

    int playersSize = this->players.size();
    file << playersSize << "\n";
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

    // save board state
    this->board.saveBoard(file);
    // save tile bag contents
    file << this->tileBag.ToString() << "\n";
    // save current player name
    file << currPlayerName << "\n";
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
        GameMessages::printLoadGameFileDoesNotExist();
        return "";
    }
    // file successfully read
    else {
        std::string string_num_players;
        std::getline(fileLoaded, string_num_players);
        int num_players = 0;
        
        try {
            num_players = std::stoi(string_num_players);
        }
        catch (std::invalid_argument& e) {
            std::cout << "File read incorrectly" << std::endl;
            this->gameEnd();
            return "";
        }
        
        // add players into vector
        for (int i=0; i < num_players; ++i) {
            Game::AddPlayer(Player());
        }
        // load name, score and hand of each player
        std::string name, hand, score;
        for (int i=0; i < num_players; ++i) {
            std::getline(fileLoaded, name);
            std::getline(fileLoaded, score);
            std::getline(fileLoaded, hand);
            // cast score from string to int
            int scoreInt = std::stoi(score);
            // load name, score
            this->players[i].setName(name);
            this->players[i].addScore(scoreInt);
            // load hand
            this->loadPlayerHand(hand, i);
        }
        // load board state
        std::string boardState;
        std::getline(fileLoaded, boardState);
        this->loadBoard(boardState);
        // load tile bag contents
        std::string tileBagState;
        std::getline(fileLoaded, tileBagState);
        this->loadTileBag(tileBagState);
    
        // load current player
        std::string currPlayerName;
        std::getline(fileLoaded, currPlayerName);

        // DEBUG: loaded
        // std::cout << "LOAD START" << std::endl;
        // std::cout << this->players[0].getName() << std::endl;
        // std::cout << this->players[0].getScore() << std::endl;
        // std::cout << this->players[0].getHand() << std::endl; // terminal shows V-4, T-1, E-1, S-1, E-1, Z-10,  --1
        
        // std::cout << this->players[1].getName() << std::endl;
        // std::cout << this->players[1].getScore() << std::endl;
        // std::cout << this->players[1].getHand() << std::endl;

        // this->board.displayBoard();
        // std::cout << this->tileBag.ToString() << std::endl;
        // std::cout << this->currPlayerName << std::endl;
        // std::cout << "LOAD END" << std::endl;
        
        return currPlayerName;
    }
}

// Helper method for loading: load player's hand
void Game::loadPlayerHand(std::string hand, int playerIndex) {
    while (hand != "") {
        // store each tile in tileString
        std::string tileString = "";
        int j = 0;
        // append the first tile from the hand so long as the char is not comma
        // keep doing it only if index does not exceed the length of hand string
        while ((hand[j] != ',') && (j < (int)hand.length())) {
            tileString += hand[j];
            ++j;
        }
        // parse tileString to extract char and value
        char letter = tileString[0];
        std::string valueString = tileString.substr(2);
        int value = std::stoi(valueString); // cast valueString into int
        // add tile to the player's hand
        Tile tile = Tile(letter, value);
        this->players[playerIndex].fillHand(Tile(letter, value));

        // the last tile in hand
        if (j == (int)hand.length()) {
            hand = "";
        }
        // not last tile in hand so accounts for ", " which is index + 2
        else {
            hand = hand.substr(j + 2);
        }
    }
}

// Helper method for loading: load board state
void Game::loadBoard(std::string boardState) {
    std::string delimiter = " ";
    std::string tileCoordinate;
    // extract each tile and coordinate with delimiter
    while (boardState != "") {
        // extract each tile and its coordinate
        size_t pos = boardState.find(delimiter);
        tileCoordinate = boardState.substr(0, pos);

        // extract letter and value from each tileString
        char letter = tileCoordinate[0];
        std::string coordinate = tileCoordinate.substr(2);
        boardState.erase(0, pos + delimiter.length());
        // place each tile on the boars
        board.placeTile(Tile(letter, 0), coordinate);
    }
}

// Helper method for loading: load tile bag
void Game::loadTileBag(std::string tileBagState) {
    // extract tiles until tileBagState is exhausted
    while (tileBagState != "") {
        // store each tile in tileString
        std::string tileString = "";
        int j = 0;
        // append the first tile from the state so long as the char is not comma
        // keep doing it only if index does not exceed the length of tileBagState string
        while ((tileBagState[j] != ',') && (j < (int)tileBagState.length())) {
            tileString += tileBagState[j];
            ++j;
        }
        // parse tileString to extract char and value
        char letter = tileString[0];
        std::string valueString = tileString.substr(2);
        int value = std::stoi(valueString); // cast valueString into int
        // add tile to the bag
        Tile tile = Tile(letter, value);
        this->tileBag.AddTile(tile);

        // the last tile in bag
        if (j == (int)tileBagState.length()) {
            tileBagState = "";
        }
        // not last tile in bag so accounts for ", " which is index + 2
        else {
            tileBagState = tileBagState.substr(j + 2);
        }
    }
}

void Game::InitaliseBag(LinkedList& bag){
    // Define consts
    int const num_tiles = 98;
    std::string const filename = "./ScrabbleTiles.txt";

    std::mt19937 rng(this->seed);

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
    const int MAX_HAND_CAPACITY = 7;
    
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
                // If EOF follows an action, you still want to trigger
                // the action but you don't want to get more input. 
                // note: this will pass playerInput into the next 
                // if block and will return true for that if statement. 
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
                            // check that the Tiles are adjacent to another 
                            // coordinate,
                            // or some extremely convulted straight line check. 

                            // place V at B10
                            // 01234567891123
                            // if the space is empty, return true. Therefore,
                            // tile can be placed.
                            if (board.validAndEmpty(coordinates)) {
                                // check if player has the correct tile.
                                Letter tileLetter = playerInput[6]; 

                                if (players[currentPlayerIndex].hasTile(
                                    tileLetter)) {
                                    Tile tile = players[currentPlayerIndex].dropTile(tileLetter);
                                    std::vector<std::string> projectedCoordinates;
                                    projectedCoordinates.push_back(
                                        coordinates);
                                    
                                   
                                    if (this->placeTiles(currentPlayerIndex,
                                     projectedCoordinates)) {
                                        // start to placeTiles (starts 
                                        // from lowest recursion)
                                        board.placeTile(tile, coordinates);
                                        // int row = board.getRow(coordinates);
                                        // int col = board.getCol(coordinates);
                                        // scoreTilesPlaced[row][col] = tile;

                                        // int playerScore = board.getScore(
                                        //     scoreTilesPlaced);

                                        int playerScore = this->getScore(sortedCoordinates);

                                        players[currentPlayerIndex].addScore(
                                            playerScore);
                                        inputNotReceived = false;
                                        // replace all tiles.
                                        // keep calling the players 
                                        // hand size until
                                        // the hand reaches seven. 
                                        // or there is no more tiles in bag. 
                                        while ( (players[currentPlayerIndex].sizeOfHand()
                                        < MAX_HAND_CAPACITY) 
                                        && (tileBag.Count() > 0)) {
                                            players[currentPlayerIndex].fillHand(
                                                tileBag.DrawTile());
                                        }

                                        // players turn not skipped. 
                                        players[currentPlayerIndex].turnNotSkipped();

                                        // // reset scoring placed tiles. 
                                        // for (int i = 0; i < ROW; ++i) {

                                        //     for (int j = 0; j < COLUMN; ++j) {
                                        //         scoreTilesPlaced[i][j] 
                                        //         = Tile();
                                        //     }
                                        // }

                                    } 
                                    
                                    else {
                                        players[currentPlayerIndex].fillHand(
                                            tile);
                                        GameMessages::printPlaceInvalidPlacement();
                                    }
                                    
                                }
                                
                                else {
                                    GameMessages::printPlaceTileNotInHand();
                                }

                            }                             

                            else {
                                GameMessages::printPlaceInvalidCoordinate();
                            }
                        }

                        else {
                            GameMessages::printPlaceInvalidPlaceSyntax();
                        }

                    }
                                       
                    // TODO: implement player action: replace
                    // syntax: replace <tile> (only one can be replaced)
                    // syntax: place <tile1> at <grid location>
                    else if (playerAction == "replace") {
                        // only allow replace if there is at least one 
                        // tile in the tileBag

                        if (this->tileBag.Count()) {
                            playerInput.erase(0, pos + delimiter.length());
                            Letter letter = playerInput[0];
                            // check if player's hand has the letter from player input

                            if (this->players[currentPlayerIndex].hasLetter(
                                letter)) {
                                // drop the tile
                                Tile droppedTile 
                                = this->players[currentPlayerIndex].dropTile(letter);

                                // add the dropped tile back to the end of bag
                                this->tileBag.AddTile(droppedTile);

                                // grab the first tile from bag
                                Tile frontTile 
                                = this->tileBag.DrawTile();

                                // add the new tile to the player's hand
                                this->players[currentPlayerIndex].fillHand(frontTile);

                                // replace action done
                                inputNotReceived = false;
                                playerInput.erase(0, pos + delimiter.length());

                                // player has not skipped turn
                                players[currentPlayerIndex].turnNotSkipped();
                            }

                            // failed to replace the letter: 
                            // cannot replace what player doesn't have
                            else {
                                GameMessages::printReplaceTileNotInHand();

                            }
                        }
                        
                        // failed to replace the letter: no tile left in bag
                        else {
                            GameMessages::printReplaceButBagEmpty();
                        }

                    }

                    // pass
                    else if (playerAction == "pass") {
                        inputNotReceived = false;
                        players[currentPlayerIndex].skippedTurn();
                    }

                    // save game
                    else if (playerAction == "save") {
                        // get filename from input
                        playerInput.erase(0, pos + delimiter.length());
                        // save game
                        if (this->saveState(playerInput, currPlayerName)) {
                            std::cout << "Game successfully saved" 
                            << std::endl;
                        }
                    }
                        
                    // TODO: implement function: quit
                    // syntax: quit
                    else if (playerAction == "quit") {
                        inputNotReceived = false;
                        gameLoop = false;
                    }

                    else if (playerAction == "help") {
                        GameMessages::printCommandMessages();
                    }


                    // TODO: Invalid Input
                    // syntax: any command not shown above
                    else {
                        std::cout << "Invalid Input." << std::endl;
                        GameMessages::printCommandMessages();
                    }
                }

                // remove at the end of testing
                // inputNotReceived = false;
            }

            // switch player
            currentPlayerIndex += 1;
            // players.size gives the amount of players in the game
            if (currentPlayerIndex == (int)players.size()) {
                currentPlayerIndex = 0;
            }
            
            // remove at the end of testing. 
            // gameLoop = false;
        }

    }

    // TODO: return an appropriate string 
    std::cout << quitGame();
    return "";
}

bool Game::placeTiles(int currentPlayerIndex, 
std::vector<std::string> projectedCoordinates) {
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
    // until playerInput becomes "place Done".
    else if (playerInput == "place Done") {        
        // one final check: validates the positions of the tiles on the board.
        // this can only be determined to be true once
        // all projectedCoordinates are given, thus it is given here. 
        tilesPlaced = board.checkBoardAdjacency(projectedCoordinates);
        if ( tilesPlaced ) {
            const int MAX_PLACEMENT_AMOUNT = 7;
            if (projectedCoordinates.size() == MAX_PLACEMENT_AMOUNT) {
                // bingo baby
                std::cout << "BINGO" << std::endl;
                const int BINGO_SCORE = 50;
                players[currentPlayerIndex].addScore(BINGO_SCORE);
            }            
            
            this->sortedCoordinates = projectedCoordinates;
            // if this works fine, sorted coordinates should be sorted 
            // for the getScore to function properly. 
            // alternatively, use the projected coordinates 
            // and find the left most or right most based on that. 
            std::sort( sortedCoordinates.begin(), sortedCoordinates.end());
        }
        
    } 

    else {
        
        if (this->validatePlaceTiles(playerInput)) {
            std::string coordinates = playerInput.substr(11);

            if (board.validAndEmpty(coordinates)) {

                // check if player has the correct tile.
                Letter tileLetter = playerInput[6]; 

                if (players[currentPlayerIndex].hasTile(tileLetter)) {
                    // drop the tile before recursing.
                    tileToPlace = players[currentPlayerIndex].dropTile(
                        tileLetter);
                    
                    // // TEST: cheat knowledge on tiles in the hand. 
                    // std::cout << players[currentPlayerIndex].getHand();

                    // push projectedCoordinates
                    projectedCoordinates.push_back(coordinates);

                    // the recursion for correct moves. 
                    // if this is false, do not place tiles. 
                    // add the tile to place to the tiles placed vector, the scores will be tallied at the end of the turn
                    validMove = this->placeTiles(currentPlayerIndex, 
                    projectedCoordinates);
                    if (!validMove) {
                        players[currentPlayerIndex].fillHand(tileToPlace);                    
                    }

                }

                else {
                    GameMessages::printPlaceTileNotInHand();
                }

            }
            
            else {
                GameMessages::printPlaceInvalidCoordinate();
            }

        }

        else {
            GameMessages::printPlaceInvalidPlaceSyntax();
        }

    }

    // all above cases pass.
    if (validMove) {
        std::string coordinates = playerInput.substr(11);
        // Tile tile = players[currentPlayerIndex].dropTile(tileLetter);
        // start to placeTiles (starts from lowest recursion)
        
        board.placeTile(tileToPlace, coordinates);
        // int row = board.getRow(coordinates);
        // int col = board.getCol(coordinates);
        // scoreTilesPlaced[row][col] = tileToPlace;
        tilesPlaced = true;
    }
    
    return tilesPlaced;
    
}

bool Game::validatePlaceTiles(std::string placeSentence) {

    bool validTilePlacement = true;
    size_t pos = 0;
    std::string playerAction;
    std::string delimiter = " ";
    pos = placeSentence.find(delimiter);
    playerAction = placeSentence.substr(0, pos);
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
        const int COORDINATE_SIZE = 2;
        if (placeSentence.length() >= COORDINATE_SIZE) {
            validTilePlacement = true;
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
    int highestScore = players[0].getScore();
    std::string winnerName = players[0].getName();

    for (Player& player : players) {
        player.printScore();

        if (highestScore < player.getScore()) {
            highestScore = player.getScore();
            winnerName = player.getName();
        }

    }

    std::cout << "Player " << winnerName << " won!" 
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

            if ((this->players[i].getName() == currentPlayer) &&
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
        GameMessages::printStartGameNoFirstPlayer();
    }

    return currentPlayerIndex;
}

int Game::getScore(std::vector<std::string> sortedCoordinates) {
    // determine if the tiles are placed left to right
    // or top to bottom: just check the first and second element
    // which applies for all elements if the contract is met. 

    std::vector<std::vector<int>> separatedCoordinates;

    for (std::string& coordinateString : sortedCoordinates) {
        separatedCoordinates.push_back(
            board.separateCoordinates(coordinateString));
    }

    bool rowIsSame = false;
    const int ROW_INDEX = 0;
    const int COLUMN_INDEX = 1;

    // if the size is one, doesn't really matter which way you calculate
    if (sortedCoordinates.size() == 1) {
        rowIsSame = true;
    }

    else {
        // compare the rows of the first and second coordinate 
        if (separatedCoordinates[0][ROW_INDEX] == separatedCoordinates[1][ROW_INDEX]) {
            rowIsSame = true;
        }

    } 
    
    

    // score from top to bottom/left to right excluding the coordinates given 
    // in the sorted coordinates. Just iterate through separatedCoordinates 
    // individually and score appropriately. If scoring top to bottom, 
    // the sorted coordinates are from left to right.

    const int FIRST_COL = 0;
    const int FIRST_ROW = 0;
    const int LAST_ROW = ROW - 1;
    const int LAST_COL = COLUMN - 1;

    int totalScore = 0;
    if (rowIsSame) {

        // care not to change coordinates OR big trouble.
        for (const std::vector<int>& coordinates :separatedCoordinates) {
            
            std::vector<int> currentCoordinate = coordinates;   
             
            // start with the top layer
            while (currentCoordinate[ROW_INDEX] != FIRST_ROW
            && !board.isEmpty(currentCoordinate[ROW_INDEX],
             currentCoordinate[COLUMN_INDEX] ) ) {
                currentCoordinate[ROW_INDEX] -= 1;
                // add the value of the coordinate above. 
                // If empty, zero is added.
                // will not seg fault since currentCoordinate column is 
                // not equal to FIRST_COL
                totalScore += board.getTileScore(currentCoordinate[ROW_INDEX],
                currentCoordinate[COLUMN_INDEX]);
            }

            // reset the coordinate.
            currentCoordinate = coordinates;

            // bottom layer.
            while (currentCoordinate[ROW_INDEX] != LAST_ROW
            && !board.isEmpty(currentCoordinate[ROW_INDEX],
             currentCoordinate[COLUMN_INDEX] )) {
                currentCoordinate[ROW_INDEX] += 1;

                totalScore += board.getTileScore(currentCoordinate[ROW_INDEX],
                currentCoordinate[COLUMN_INDEX]);
            }
        }
            
        // then starting from the left most/ top most coordinate from inline, score
        // from left to right / top to bottom until hitting a dead end. If scoring
        // from left to right, the sorted coordinates are from left to right. 

        // get the left most coordinate along the same row as the 
        // sorted coordinates.
        // the first coordinate of the separatedCoordinates will be used.
        std::vector<int> currentCoordinate = separatedCoordinates[0];   

        // from left to right
        while (currentCoordinate[COLUMN_INDEX] != FIRST_COL
            && !board.isEmpty(currentCoordinate[ROW_INDEX],
             currentCoordinate[COLUMN_INDEX] ) ) {
                currentCoordinate[COLUMN_INDEX] -= 1;
        }       
        
        // this is justifiable given that the occupied coordinate is not 
        // empty, which is when the occupied coordinate is at the edge.
        // if empty, go back to non-empty space.  
        if (board.isEmpty(currentCoordinate[ROW_INDEX],
             currentCoordinate[COLUMN_INDEX]) ) {
                 currentCoordinate[COLUMN_INDEX] += 1;
        }

        // while the currentCoordinate has not reached an empty tile or 
        // end_col, count some tiles.
        while (currentCoordinate[COLUMN_INDEX] != LAST_COL
            && !board.isEmpty(currentCoordinate[ROW_INDEX],
             currentCoordinate[COLUMN_INDEX] ) ) {
                totalScore += board.getTileScore(
                    currentCoordinate[ROW_INDEX],
                     currentCoordinate[COLUMN_INDEX]);
                currentCoordinate[COLUMN_INDEX] += 1;
        }       

    }

    // score left to right
    else {

        // care not to change coordinates OR big trouble.
        // actually just const it 
        for (const std::vector<int>& coordinates :separatedCoordinates) {
            
            std::vector<int> currentCoordinate = coordinates;   
             
            // start with the left layer
            while (currentCoordinate[COLUMN_INDEX] != LAST_COL
            && !board.isEmpty(currentCoordinate[ROW_INDEX],
             currentCoordinate[COLUMN_INDEX] ) ) {
                currentCoordinate[COLUMN_INDEX] -= 1;
                // add the value of the coordinate to the left. 
                // If empty, zero is added.
                // will not seg fault since currentCoordinate column is 
                // not equal to FIRST_COL
                totalScore += board.getTileScore(currentCoordinate[ROW_INDEX],
                currentCoordinate[COLUMN_INDEX]);
            }
            
            // reset the coordinate 
            currentCoordinate = coordinates;

            // right layer.
            while (currentCoordinate[COLUMN_INDEX] != LAST_COL
            && !board.isEmpty(currentCoordinate[ROW_INDEX],
             currentCoordinate[COLUMN_INDEX] )) {
                currentCoordinate[COLUMN_INDEX] += 1;

                totalScore += board.getTileScore(currentCoordinate[ROW_INDEX],
                currentCoordinate[COLUMN_INDEX]);
            }
            
        }

            
        // then starting from the left most/ top most coordinate from inline, score
        // from left to right / top to bottom until hitting a dead end. If scoring
        // from left to right, the sorted coordinates are from left to right. 

        // get top most coordinate along the same column as the 
        // sorted coordinates.
        // the first coordinate of the separatedCoordinates will be used.
        std::vector<int> currentCoordinate = separatedCoordinates[0];   

        // well you need the boundary case where the edges are non-empty 
        while (currentCoordinate[ROW_INDEX] != FIRST_ROW
            && !board.isEmpty(currentCoordinate[ROW_INDEX],
             currentCoordinate[COLUMN_INDEX] ) ) {
                currentCoordinate[ROW_INDEX] -= 1;
        }       

        // this is justifiable given that the occupied coordinate is not 
        // empty, only during boundary cases though.
        // if empty, go back to non-empty space.  
        if (board.isEmpty(currentCoordinate[ROW_INDEX],
             currentCoordinate[COLUMN_INDEX]) ) {
                 currentCoordinate[ROW_INDEX] += 1;
        }

        // while the currentCoordinate has not reached an empty tile or 
        // end_col, count some tiles.
        while (currentCoordinate[ROW_INDEX] != LAST_ROW
            && !board.isEmpty(currentCoordinate[ROW_INDEX],
             currentCoordinate[COLUMN_INDEX] ) ) {
                totalScore += board.getTileScore(
                    currentCoordinate[ROW_INDEX],
                     currentCoordinate[COLUMN_INDEX]);
                currentCoordinate[ROW_INDEX] += 1;
        }      

    }
    return totalScore;
}