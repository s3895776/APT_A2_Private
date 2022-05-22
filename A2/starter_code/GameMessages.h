#ifndef GAME_MESSAGES
#define GAME_MESSAGES

#include <iostream>

/* Desc:
    create messages for the scrabble game to use. 
    add anything that can be a message
    as a method.
*/
class GameMessages {
    public:
    // format is print<action><message_name> for input validation for actions
    // other format is print<message_name> for non-input related messages. 
        static void printCommandMessages();
        static void printPlaceInvalidPlacement();
        static void printPlaceInvalidCoordinate();
        static void printPlaceTileNotInHand();
        static void printValidPlaceSyntax();
        static void printPlaceInvalidPlaceSyntax();
        static void printReplaceButBagEmpty();
        static void printReplaceTileNotInHand();
        static void printStartGameNoFirstPlayer();
        static void printLoadGameFileDoesNotExist();
        static void printValidName();
        static void printValidPlayerCount();

        // for use within other methods.
        // format is return<message_name>
        private: 
        static std::string returnValidLetters();
        static std::string returnValidCoordinates();
        
};


#endif //GAME_MESSAGES