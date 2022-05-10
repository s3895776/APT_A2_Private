#include "tests/BoardTest.cpp"
#include "tests/LinkedList_test.cpp"

int main(){
    int numFailures = 0;

    numFailures += Board_RunTests();
    numFailures += LL_RunTests();

    std::cout << "Total failures: " << numFailures << std::endl;

    return (int)(bool)numFailures; //blame jake
}