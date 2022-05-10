#include "tests/BoardTest.cpp"
#include "tests/LinkedList_test.cpp"
#include "tests/Tile_test.cpp"

// Use 'make tests' to compile
// Then ./Testing to run

int main(){
    int numFailures = 0;

    numFailures += Board_RunTests();
    numFailures += LL_RunTests();
    numFailures += Tile_RunTests();

    std::cout << "Total failures: " << numFailures << std::endl;

    return (int)(bool)numFailures; //blame jake
}