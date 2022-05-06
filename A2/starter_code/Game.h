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

        
    private:
        // std::vector< std::vector<char> > board;
        // Board* board;
        std::vector<Player> players;

        LinkedList tileBag;
        void InitaliseBag(LinkedList& bag);

        /* Display the end of the game information */
        std::string gameEnd();
        // Board board;
};


#endif // GAME_H