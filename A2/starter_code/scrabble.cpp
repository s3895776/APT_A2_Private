#include "Game.h"
#include <iostream>
#include <string>
#include <random>

#define EXIT_SUCCESS    0

int getSeed(int argc, char* argv[]){
   // Seed RNG
   int seed = 0;

   if (argc > 2){
      // Manual Seed
      try {
         std::string s(argv[1]);
         if (s == "-seed"){
            std::string input(argv[2]);
            seed = std::stoi(input);
         } 
      } catch (const std::exception& e){
         std::cout << "Bad seed. Please use an int." << std::endl;
         return 1;
      }
   } else {
      // Auto Seed
      std::random_device rd;
      seed = rd();
   }  

   return seed;
}

int main(int argc, char* argv[]) {

   int seed = getSeed(argc, argv);

   Game game(seed);

   std::string firstPlayer = game.run_menu();

   if (firstPlayer != "") {   
      std::cout << game.gameInput(firstPlayer);
   }

   return EXIT_SUCCESS;
}   