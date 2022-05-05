#include "Game.h"
#include <iostream>
#include "./tests/LinkedList_test.cpp"

#define EXIT_SUCCESS    0

int main(void) {

   Game game;
   std::string firstPlayer = game.run_menu();   
   std::cout << "First player: " << firstPlayer << std::endl;
   std::cout << game.gameInput(firstPlayer) << std::endl;

   return EXIT_SUCCESS;
}