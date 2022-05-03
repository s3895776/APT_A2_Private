#include "Game.h"
#include <iostream>
#include "./tests/LinkedList_test.cpp"

#define EXIT_SUCCESS    0

int main(void) {

   std::cout << "TODO: Implement Scrabble!" << std::endl;
   LL_RunTests();
   Game game;
   //    game->view_mainMenu();
   //  std::cout << game << std::endl;
   game.run_game();
   //  game->view_mainMenu();
   

   return EXIT_SUCCESS;
}