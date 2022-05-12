#include "Game.h"
#include <iostream>

#define EXIT_SUCCESS    0

int main(void) {
   Board_RunTests();
   Game game;
   std::string firstPlayer = game.run_menu();

   if (firstPlayer != "") {   
      std::cout << game.gameInput(firstPlayer);
   }

   return EXIT_SUCCESS;
}   