#include "Game.h"
#include <iostream>
#include "./tests/LinkedList_test.cpp"
#include "./tests/BoardTest.cpp"

#define EXIT_SUCCESS    0

int main(void) {
   Game game;
   std::string firstPlayer = game.run_menu();

   if (firstPlayer != "") {   
      std::cout << game.gameInput(firstPlayer);
   }

   return EXIT_SUCCESS;
}   