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
        Game(int seed);
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
        bool saveState(std::string filename, std::string currPlayerName);

        /*
         * Load game from a saved file
         */
        std::string loadGame();       

        void loadPlayerHand(std::string hand, int playerIndex);
        void loadTileBag(std::string tileBagState);
        void loadBoard(std::string boardState);

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

        /*
         * Check if main menu choice is between 1 and 4
         */
        bool validMainMenuChoice(int choice);

        // I made this public for testing puposes
        void InitaliseBag(LinkedList& bag);
        void AddPlayer(Player player);

        /* recursive case: only activates once gameInput() validates 
        one sentence.  prevValid indicates that the previous recursion must be valid.
        If not, the case is automatically false.
        */
        bool placeTiles(int currentPlayerIndex, std::vector<std::string> projectedCoordinates);
        void replaceTiles(std::string currentPlayer);

        /* this must be able to validate such that a sentence involving place
        is in the following format:
        place A at A00, or 
        place A at A0. Will return false otherwise. Does not need to handle
        place Done. 
        */ 
        // made public for testing. 
        bool validatePlaceTiles(std::string placeSentence);

        /* checks projectedCoordinates to see if they are all valid moves.
        only works for when Coordinates are already validated.
        Does not check the emptiness of coordinates in projected coordinates.

        */
        bool checkBoardAdjacency(std::vector<std::string> projectedCoordinates);

        /* Return boolean that tells if the current tile is adjacent
            to a non-empty tile
            Coordinate parameters must be valid for Board. 
         */
        bool adjacentNotEmpty(int rowCoordinate, int colCoordinate);

    private:
        std::vector<Player> players;

        LinkedList tileBag;
        int seed;

        /* Display the end of the game information */
        std::string gameEnd();
        Board board;
        // return index of player stored in vector
        int searchPlayer(std::string currentPlayer);
        std::vector<std::vector<Tile>> scoreTilesPlaced;
        
};


#endif // GAME_H