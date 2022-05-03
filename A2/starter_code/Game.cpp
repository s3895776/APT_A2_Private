#include "Game.h"
#include <fstream>
#include <random>

Game::Game() {
    tileBag = LinkedList();
    // board = Board();
}

Game::~Game() {
}

void Game::run_menu() {

    bool menu = true;

    while (menu) {
        int choice = this->view_mainMenu();

        if (choice == 1) {
            std::cout << this->newGame();
            menu = false;
        }
        else if (choice == 2) {
            this->loadGame();
            std::cout << "loading game" << std::endl;
            menu = false;
        }
        else if (choice == 3) {
            std::cout << this->displayCredits() << std::endl;
        }
        else if (choice == 4) {
            std::cout << this->quitGame() << std::endl;
            menu = false;
        }

        else {
            std::cout << "wrong choice" << std::endl;
        }
    }
}

/*
 * Display prompt for main menu and return the user input choice (1 to 4)
 */
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

std::string Game::newGame() {
    // 1. Print a message for starting a new game
    std::cout << std::endl;
    std::cout << "Starting a New Game" << std::endl;
    std::cout << std::endl;
    
    // 2. Ask for the player names
    // TODO: store the players names. 
    
    // TODO: initialise players in newGame() 
    const int NUMBER_OF_PLAYERS = 2;
    int i = 0;
    
    // for each player, add pointer-to-player in players vector
    while (i < NUMBER_OF_PLAYERS) {
        Player player;
        Player* playerPtr = &player;
        this->players.push_back(playerPtr);
        ++i;
    }

    i = 0;
    std::string playerName;

    while (i < NUMBER_OF_PLAYERS) {
        std::cout << "Enter a name for player " << i + 1 << " (uppercase characters only)" << std::endl;
        std::cout << "> ";
        std::cin >> playerName;
        std::cout << std::endl;
        // TODO: check for uppercase only or ask again
        this->players[i]->setName(playerName);
        // this->(*players)[i]->setName(playerName);
        ++i;
    }

    std::cout << "Let's Play!" << std::endl;

    // 3. Create a new game of Scrabble
    InitaliseBag(tileBag);

    // TODO: initialise Players One and Two LinkedList values with Tiles.

    // TODO: initialise 2d vector with starting values 


    // 4. Proceed with normal gameplay 
    // std::string currentPlayerName = (*players)[i]->getName();
    // Let main call gameInput();
    std::cout << players[0]->getName() << std::endl;
    std::cout << players[1]->getName() << std::endl;

    return "start new game";
    // return std::string("new Game");
}

std::string Game::displayCredits() {
    std::string credits = "";
    credits.append("\n");
    credits.append("-------------------------------------\n");
    credits.append("Name: Dan Podbury\n");
    credits.append("Student ID: s3881206\n");
    credits.append("Email: \n");
    credits.append("\n");
    credits.append("Name: Guo An Liew\n");
    credits.append("Student ID: \n");
    credits.append("Email: \n");
    credits.append("\n");
    credits.append("Name: Kerubo Ndubi\n");
    credits.append("Student ID: \n");
    credits.append("Email: \n");
    credits.append("\n");
    credits.append("Name: Min Min Oo\n");
    credits.append("Student ID: s3860838\n");
    credits.append("Email: s3860838@student.rmit.edu.au\n");
    credits.append("-------------------------------------\n");
    return credits;
}

// std::string Game::modifyBoard(std::vector<Tile> tilesToPlace, std::vector<std::string> coordinates) {
//     std::string boardState;
//     // TODO: modify the 2d vector 

//     // TODO: revert board if invalid move.

//     // TODO: award points if successful move.
//     return boardState;
// }

// std::string Game::awardPoints() {
//     // TODO: award points 
//     return "Points awarded";
// }

// std::string Game::invalidMove() {
//     // TODO: revert board 
//     return "Invalid move";
// }


std::string Game::loadGame() {
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
    // all fields are on newlines. 
    // Format:
    // • Name: ASCII text
    // • Score: Integer
    // • Player hand and tile bag: comma separated ordered list
    // • Current board shape: Height, width
    // • Board State: All tiles currently placed on the board should appear as a list of tile@position.
    // example in spec 
    
    std::string filename;
    std::cout << "Enter the filename to load game" << std::endl;
    std::cout << "> ";
    std::cin >> filename;
    // return false if (filename does not exist)
    // TODO: loop until valid file name
    // return "Failed Load"

    // https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
    std::ifstream fileLoaded("saves/" + filename);
    std::stringstream buffer;
    buffer << fileLoaded.rdbuf();

    // std::cout << buffer.str() << std::endl;

    std::string rawString = buffer.str();
    
    // https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    // split string with the following delimiter
    std::string delimiter = "|";
    std::string allPlayers = rawString.substr(0, buffer.str().find(delimiter));

    // size_t pos = 0;
    // rawString = rawString.substr(pos + delimiter.length());
    rawString.erase(0, rawString.find(delimiter) + delimiter.length());

    std::string boardStatus = rawString.substr(0, buffer.str().find(delimiter));

    rawString.erase(0, rawString.find(delimiter) + delimiter.length());

    std::string currentPlayer = rawString.substr(0, buffer.str().find(delimiter));

    std::cout << "starting now" << std::endl;
    std::cout << allPlayers << std::endl;
    std::cout << boardStatus << std::endl;
    std::cout << currentPlayer << std::endl;

    // TODO: Store the name of the currentPlayer
    return currentPlayer;
}


void Game::InitaliseBag(LinkedList& bag){
    // TODO(dan): test no duplicates, shuffle correct, etc...

    // Define consts
    int const num_tiles = 98;
    std::string const filename = "./ScrabbleTiles.txt";

    // Mersenne Twister PRNG
    std::random_device r;
    std::mt19937 rng{r()};
    
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
    for (int i = 0; i < 99; i++){
        bag.AddTile(tiles[i]);
    }
}

bool Game::saveState(std::string filename) {
    std::string gameState;
    // Suggested format
    // Player | Board | Current Player index

    // <player 1 name>, <player 1 score>, <player 1 hand>
    // <player 2 name>, <player 2 score>, <player 2 hand>
    // |
    // <board state>, <tile bag contents>
    // |
    // <current player index in vector>

    // TODO: 
    // search for filename in dir
    // return false (filename already exists)

    std::ofstream fileToBeSaved;
    fileToBeSaved.open("saves/" + filename);
    fileToBeSaved << "PLAYER A, 100, ABCD\n";
    fileToBeSaved << "PLAYER B, 200, EFGH\n";
    fileToBeSaved << "|\n";
    fileToBeSaved << "board state, tile bag content\n";
    fileToBeSaved << "|\n";
    fileToBeSaved << "0\n";
    fileToBeSaved.close();


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
    // all fields are on newlines. 
    // Format:
    // • Name: ASCII text
    // • Score: Integer
    // • Player hand and tile bag: comma separated ordered list
    // • Current board shape: Height, width
    // • Board State: All tiles currently placed on the board should appear as a list of tile@position.
    // example in spec 

    // TODO: put players information into gameState

    // TODO: put 2d vector into gameState 

    // TODO: put LinkedList tileBag as string into gameState

    // TODO: fill in the file with gameState.

    

    return true;
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
    // std::cin >> string
    // dissect the string into parts to get the right string. 

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

    // TODO: return an appropriate string 
    return std::string("Something");
}

std::string Game::quitGame() {
    return std::string("\nGoodbye\n");
}
