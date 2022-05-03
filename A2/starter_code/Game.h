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
        void run_menu();

        /*
         * Display prompt for main menu
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

        /*Modify the board */
        // std::string modifyBoard(std::vector<Tile> tilesToPlace, std::vector<std::string> coordinates);

        

        /* Wait for player input and call player methods in this state. 
        */
        std::string gameInput(std::string currentPlayerName);

        /*
         * Quit game
         */  
        std::string quitGame();

        
    private:
        // std::vector< std::vector<char> > board;

        std::vector<Player*> players;

        // /*Award points to the player for a legal move.*/
        // std::string awardPoints();

        /*Return the board to its original state.*/
        std::string invalidMove();

        LinkedList tileBag;
        void InitaliseBag(LinkedList& bag);
        // Board board;
};


#endif // GAME_H