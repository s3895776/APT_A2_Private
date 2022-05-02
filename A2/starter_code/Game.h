#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
// #include "LinkedList.h"
#include "Player.h"

class Game {

    public:

        /* Constructor, destructor, copy constructor
        */
        Game();
        ~Game();
        Game(Game& other);

        /*
         * Run game loop
         */
        void run_game();

        /*
         * Display prompt for main menu
         */
        int view_mainMenu();

        /*Modify the board */
        // std::string modifyBoard(std::vector<Tile> tilesToPlace, std::vector<std::string> coordinates);

        // /* Load a game from a saveFile
        // param: take a saveFile TODO: determine saveFile type 
        // */
        // std::string loadGame(std::iostream& saveFile);

        /*
         * Create a new game 
         */
        std::string newGame();

        /*
         * Display Credits
         */
        std::string displayCredits();

        // /* Save board information 
        // */
        // std::string saveState();

        // /* Wait for player input and call player methods in this state. 
        // */
        // std::string gameInput(std::string currentPlayerName);

        /*
         * Quit game
         */  
        std::string quitGame();


    private:
        // std::vector< std::vector<char> > board;
        // LinkedList tileBag;
        std::vector<Player*> *players;

        // /*Award points to the player for a legal move.*/
        // std::string awardPoints();

        // /*Return the board to its original state.*/
        // std::string invalidMove();
};


#endif // GAME_H