#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "LinkedList.h"
#include "Player.h"
#include "Board.h"
class Game {

    public:

        /*
         * Constructor, destructor, copy constructor
         */
        Game();
        ~Game();
        Game(Game& other);

        /*
         * Run game loop
         */
        std::string run_menu();

        /*
         * Display prompt for main menu and return the user input choice (1 to 4)
         */
        int view_mainMenu();

        /*
         * Create a new game 
         */
        std::string newGame();

        /*
         * Display Credits
         */
        std::string displayCredits();

        /*
         * Save board information 
         */
        bool saveState(std::string filename);

        /*
         * Load game from a saved file
         */
        std::string loadGame();       

        /* Wait for player input and call player methods in this state. 
        */
        std::string gameInput(std::string firstPlayer);

        /*
         * Quit game
         */  
        std::string quitGame();

        /*
         * Check if name contains all uppercase characters and at least one characer long
         */
        bool validName(std::string name);

        // I made this public for testing puposes
        void InitaliseBag(LinkedList& bag);
        void AddPlayer(Player player);

        // recursive case: only activates once gameInput() validates one sentence.
        bool placeTiles(int currentPlayerIndex, bool prevValid, std::string prevCoordinate);
        void replaceTiles(std::string currentPlayer);

        /* this must be able to validate such that a sentence involving place
        is in the following format:
        place A at A00, or 
        place A at A0. Will return false otherwise. Does not need to handle
        place Done. 
        */ 
        // made public for testing. 
        bool validatePlaceTiles(std::string placeSentence);

    private:
        std::vector<Player> players;

        LinkedList tileBag;

        /* Display the end of the game information */
        std::string gameEnd();
        Board board;
        // return index of player stored in vector
        int searchPlayer(std::string currentPlayer);

        
};


#endif // GAME_H