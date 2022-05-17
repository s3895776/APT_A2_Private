#include "Game.h"
#include <fstream>
#include <random>
#include <iostream>
#include <algorithm>

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
bool Game::saveState(std::string filename, std::string currPlayerName) {
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
        std::string name, hand, score;
        for (int i=0; i < NO_OF_PLAYERS; ++i) {
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
        while ((hand[j] != ',') && (j < hand.length())) {
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
        if (j == hand.length()) {
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
    size_t pos = boardState.find(delimiter);
    std::string tileCoordinate;
    // extract each tile and coordinate with delimiter
    while (boardState != "") {
        // extract each tile and itss coordinate
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
        while ((tileBagState[j] != ',') && (j < tileBagState.length())) {
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
        if (j == tileBagState.length()) {
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
                                    std::vector<std::string> projectedCoordinates;
                                    projectedCoordinates.push_back(coordinates);
                                    if (this->placeTiles(currentPlayerIndex, true, projectedCoordinates)) {

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

                    // save game
                    else if (playerAction == "save") {
                        // get filename from input
                        playerInput.erase(0, pos + delimiter.length());
                        // save game
                        if (this->saveState(playerInput, currPlayerName)) {
                            std::cout << "Game successfully saved" << std::endl;
                        }
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

            // switch player
            currentPlayerIndex += 1;
            if (currentPlayerIndex == 2) {
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

bool Game::placeTiles(int currentPlayerIndex, bool prevValid, std::vector<std::string> projectedCoordinates) {
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
        tilesPlaced = true;
        // perform check for adjacency here. 
        // if (prevValid) {
        //     tilesPlaced = board.checkBoardAdjacency(projectedCoordinates);
        // }

    } 

    // if prevValid was not valid, this triggers. 
    // essentially no validation is necessary because its already wrong
    // just waiting for place Done or EOF before recursion can end. 
    else if (!prevValid) {
        this->placeTiles(currentPlayerIndex, false, projectedCoordinates);
    }

    else {
        bool recurse = false;
        if (this->validatePlaceTiles(playerInput)) {
            std::string coordinates = playerInput.substr(11);

            if (board.validAndEmpty(coordinates)) {

                // check if player has the correct tile.
                Letter tileLetter = playerInput[6]; 

                if (players[currentPlayerIndex].hasTile(tileLetter)) {
                    // drop the tile before recursing.
                    tileToPlace = players[currentPlayerIndex].dropTile(tileLetter);
                    // TEST: cheat
                    std::cout << players[currentPlayerIndex].getHand();

                    // push projectedCoordinates
                    projectedCoordinates.push_back(coordinates);

                    // the recursion for correct moves. 
                    // if this is false, do not place tiles. 
                    recurse = true;
                    validMove = this->placeTiles(currentPlayerIndex, true, projectedCoordinates);
                    if (!validMove) {
                        players[currentPlayerIndex].fillHand(tileToPlace);
                    }

                }

            }

        }

        // do a pointless recursion (still accept input regardless 
        // of invalid input) if not recursing already. 
        if (!recurse) {
            this->placeTiles(currentPlayerIndex, false, projectedCoordinates);
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

// bool Game::checkBoardAdjacency(std::vector<std::string> projectedCoordinates) {
//     bool canBePlaced = false;
//     // separate the projectedCoordinates to expect normal input.
//     // each cell should have two spaces with the first representing row 
//     // and the second representing column
//     // this lets us compare coordinates defined by the board.
//     std::vector<std::vector<int>> separateCoordinates;
    
//     // case where projectedCoordinates is zero is not checked

//     // should also check if the board is empty: 
//     // if so, no need to check for existent tiles.

//     bool boardIsEmpty = board.boardEmpty();


//     if (projectedCoordinates.size() == 1) {
//         // TODO: if the board is empty, it will be a valid move. 
//         if (boardIsEmpty) {
//             canBePlaced = true;
//         }

//         else {
//             // TODO: check all adjacent tiles. 
//             // If at least one is not empty, than it can be placed.
//             separateCoordinates.push_back(
//                 this->board.separateCoordinates(projectedCoordinates[0]));

//             // do not check if coordinate is on a boundary. 
//             // initiate boundary checks. 
//             // enter the row as first param and the column as second param. 
//             canBePlaced = this->adjacentNotEmpty(
//                 separateCoordinates[0][0], separateCoordinates[0][1]);
//         }

//     }

//     else {
//         canBePlaced = true;
//         std::sort(projectedCoordinates.begin(), projectedCoordinates.end());
        
//         // TODO: check if there are any duplicate coordinates. 
//         // since its sorted, can check one element to the next. 

//         for (std::string& coordinateString : projectedCoordinates) {
//             separateCoordinates.push_back(
//                 this->board.separateCoordinates(coordinateString));
//         }

        
//         // TODO: check if all coordinates belong on the same line. 
//         // i.e. letter == letter or number == number 
//         int i = 0;
//         int projectedSize = projectedCoordinates.size();
//         bool rowIsSame = false;
//         bool columnIsSame = false;

//         // coordinates must be the same
//         if (separateCoordinates[0][0] != separateCoordinates[1][0]) {
//             columnIsSame = true;
//         }
//         // letters must be the same
//         else {
//             rowIsSame = true;
//         }

//         // must check for adjacency. 
//         // if no tiles are adjacent to at least an existing tile,
//         // the move is invalid. 
//         // alternatively, if the board is empty, no need to check 
//         // for adjacency.  

//         // if notAdjacentToTile is true at end of while loop,
//         // the board is not empty and tiles are not placed next to 
//         // a non-empty space, therefore canBePlaced will also be false. 
//         bool notAdjacentToTile = true;

//         if (boardIsEmpty) {
//             notAdjacentToTile = false;
//         }

//         // checks for coordinates belonging on the same line 
//         // and if two coordinates are the same. 
//         // checks if the board is empty, if not at least one tile
//         // must belong next to an existing tile. 
//         while (i < projectedSize - 1 && canBePlaced) {
//             int currentRow = separateCoordinates[i][0];
//             int currentCol = separateCoordinates[i][1];
//             int nextRow = separateCoordinates[i + 1][0];
//             int nextCol = separateCoordinates[i + 1][1];

//             // TODO: check if there are any duplicate coordinates. 
//             // since its sorted, can check one element to the next. 
//             if (currentRow == nextRow && currentCol == nextCol) {
//                 // cannot be placed.      
//                 canBePlaced = false;   

//             } 

//             if (columnIsSame) {

//                 // number is not the same: compare second cell
//                 if (currentCol != nextCol) {
//                     // cannot be placed.                
//                     canBePlaced = false;          
//                 }

//             }

//             else if (rowIsSame) {
                
//                 // letter is not the same: compare first cell. 
//                 if (currentRow != nextRow) {
//                     // cannot be placed.                
//                     canBePlaced = false;          
//                 }              

//             }

//             if (notAdjacentToTile) {
//                 // check that adjacent is not empty.
//                 // if it is, the check no longer occurs.
//                 // if it isn't, the check continues in
//                 // the next loop. 
//                 notAdjacentToTile = this->adjacentNotEmpty(
//                     currentRow, currentCol);
//             }

//             i += 1;
//         }
        
//         // based on above spec, if this is true, canBePlaced 
//         // is false.
//         if (notAdjacentToTile) {
//             canBePlaced = false;
//         }

//         // all tiles are in a straight line. 
//         // check for emptiness between tiles.
//         // example: for C11 and C15, check C12 to C14. 
//         // note that the straight line comparison depends 
//         // on what line the user places tiles across.
//         if (canBePlaced) {
//             // check in between for the column
//             int i = 0;

//             // use this in place of a row or column.
//             int numCoordinates = separateCoordinates.size();

//             if (columnIsSame) {
//                 int columnIndex = 1;
//                 int columnNum = separateCoordinates[0][columnIndex];
//                 while ( i < numCoordinates) {
//                     // whether its a row or column, increment to check 
//                     // that the space between this and the next coordinate
//                     // is not empty.
//                     int rowCheck = separateCoordinates[i][columnIndex] + 1;
//                     int nextRowCol = separateCoordinates[i + 1][columnIndex];
                    

//                     while (rowCheck < nextRowCol) {
//                         // if the cell is empty, the move is invalid. 
//                         if (board.isEmpty(rowCheck, columnNum)) {
//                             canBePlaced = false;
//                         }
//                         rowCheck += 1;
//                     }

//                     i += 1;
//                 }
//             }
            
//             // row is same
//             else {
//                 int rowIndex = 0;
//                 int rowNum = separateCoordinates[0][rowIndex];
                
//                 while ( i < numCoordinates) {
//                     // whether its a row or column, increment to check 
//                     // that the space between this and the next coordinate
//                     // is not empty.
//                     int colCheck = separateCoordinates[i][rowIndex] + 1;
//                     int nextRowCol = separateCoordinates[i + 1][rowIndex];
                    

//                     while (colCheck < nextRowCol) {
//                         // if the cell is empty, the move is invalid. 
//                         if (board.isEmpty(rowNum, colCheck)) {
//                             canBePlaced = false;
//                         }

//                         colCheck += 1;
//                     }

//                     i += 1;
//                 }

//             }

//         }

//     }
//     return canBePlaced;
// }

// bool Game::adjacentNotEmpty(int rowCoordinate, int colCoordinate) {
//     // initiate boundary checks. 
//     bool adjacentNotEmpty = false;
//     bool checkLeft = true;
//     bool checkRight = true;
//     bool checkAbove = true;
//     bool checkBelow = true;

//     if (rowCoordinate == ROW) {
//         checkRight = false;
//     }
//     else if (rowCoordinate == 0) {
//         checkLeft = false;
//     }

//     if (colCoordinate == COLUMN) {
//         checkBelow = false;
//     }

//     else if (colCoordinate == 0) {
//         checkAbove = false;
//     }

//     if (checkAbove) {
//         // TODO: check above coordinate
//         if ( !board.isEmpty( (rowCoordinate), (colCoordinate - 1) ) ) {
//             adjacentNotEmpty = true;
//         }
//     }

//     if (checkBelow) {
//         // TODO: check below coordinate
//         if ( !board.isEmpty( (rowCoordinate), (colCoordinate + 1) ) ) {
//             adjacentNotEmpty = true;
//         }
//     }

//     if (checkLeft) {
//         // checks left coordinate
//         if ( !board.isEmpty( (rowCoordinate - 1), (colCoordinate) ) ) {
//             adjacentNotEmpty = true;
//         }
//     }

//     if (checkRight) {

//         // checks the right coordinate
//         if ( !board.isEmpty( (rowCoordinate + 1), (colCoordinate) ) ) {
//             adjacentNotEmpty = true;
//         }
//     }
//     return adjacentNotEmpty;
// }

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