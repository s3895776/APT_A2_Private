#include "tests.h"

#include "tests/UnitTests_Board.cpp"
#include "tests/UnitTests_LinkedList.cpp"
#include "tests/UnitTests_Tile.cpp"
#include "tests/UnitTests_Player.cpp"
#include "tests/UnitTests_Game.cpp"

// UNIT TESTS

// Runs tests and tallies failures. 
// Returns this value so github Actions can determine is the tests passed.

// Usage:
// make Testing
// ./Testing

int main(){
    std::cout << "UNIT TESTING\n\n";
    int numFailures = 0;

    numFailures += Board_RunTests();
    numFailures += LL_RunTests();
    numFailures += Tile_RunTests();
    numFailures += Player_RunTests();
    numFailures += Game_RunTests();

    std::cout << "Total Failures: " << numFailures << std::endl;

    return (int)(bool)numFailures;
}