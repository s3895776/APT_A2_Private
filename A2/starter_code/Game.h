#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "LinkedList.h"
#include "Player.h"
#include "Board.h"
#include "GameMessages.h"
class Game {

    public:

        /*
         * Constructor
         */
        Game();
        Game(int seed);

        /*
        Destructor
        */
        ~Game();

        /*
        Copy constructor
        */
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
        bool saveState(std::string filename, std::string currPlayerName);

        /*
         * Load game from a saved file
         */
        std::string loadGame();       

        /* method to load player hand into game */
        void loadPlayerHand(std::string hand, int playerIndex);
        /* method to load tile bag into the game */
        void loadTileBag(std::string tileBagState);
        /* method to load board into the game */
        void loadBoard(std::string boardState);

        /* Wait for player input and call player methods in this state. 
        */
        std::string gameInput(std::string firstPlayer);

        /*
         * Quit game
         */  
        std::string quitGame();

        /*
         * Check if name contains all uppercase characters 
         and at least one characer long
         */
        bool validName(std::string name);

        /*
         * Check if main menu choice is between 1 and 4
         */
        bool validMainMenuChoice(int choice);

        // I made this public for testing puposes
        void InitaliseBag(LinkedList& bag);
        void AddPlayer(Player player);

        /* recursive case: only activates once gameInput() validates 
        one sentence.  
        passes a vector of coordinates to check if the final placement 
        is correct. Uses the currentPlayerIndex to call the methods of
        the internal player.
        */
        bool placeTiles(int currentPlayerIndex, 
        std::vector<std::string> projectedCoordinates);

        /* 
        made public for testing. 
        this must be able to validate such that a sentence involving place
        is in the following format:
        place A at A00, or 
        place A at A0. Will return false otherwise. Does not need to handle
        place Done. 
        */ 
        bool validatePlaceTiles(std::string placeSentence);

        /* checks projectedCoordinates to see if they are all valid moves.
        only works for when Coordinates are already validated.
        Does not check the emptiness of coordinates within
        projected coordinates.
        */
        bool checkBoardAdjacency(std::vector<std::string> projectedCoordinates);

        /* Return boolean that is true if the current tile is adjacent
            to a non-empty tile
            Coordinate parameters must be valid for Board. 
        */
        bool adjacentNotEmpty(int rowCoordinate, int colCoordinate);

        /* get the score using the first left most tile or the top most tile.
        when scored the following conditions are met: 
        the coordinates are all placed left to right or top to bottom
        the tiles have been placed in the board. */
        int getScore(std::vector<std::string> sortedCoordinates);
        

    private:
        /* Stores a variable number of players.*/
        std::vector<Player> players;

        /* Stores a variable amount of tiles */
        LinkedList tileBag;

        /* store the seed to use within the random generator for tileBag.*/
        int seed;

        /* Display the end of the game information */
        std::string gameEnd();
        /* Stores the board ADT to use in Game */
        Board board;

        // return index of player stored in vector
        int searchPlayer(std::string currentPlayer);

        // /* stores a 2D vector of tiles which is used to score tiles 
        // by using a board method. 
        // */
        // No longer in use for my implementation.
        // std::vector<std::vector<Tile>> scoreTilesPlaced;

        /* Stores a list of sorted coordinates which is used to score 
        based on the coordinates */
        std::vector<std::string> sortedCoordinates;
        
};


#endif // GAME_H