#ifndef TESTS_H
#define TESTS_H

#include <string>
#include <iostream>

int AssertAndReport(std::string got, std::string expected, std::string testName){

    if (got == expected){
        std::cout << "PASS " << testName << std::endl;
    } else {
        std::cout << "FAIL " << testName << std::endl;
        std::cout << "  Expected :" << expected << "\n"; 
        std::cout << "  Got: " << got << "\n\n";
    }

    return (got != expected);
}
int AssertAndReport(char got, char expected, std::string testName){
    if (got == expected){
        std::cout << "PASS " << testName << std::endl;
    } else {
        std::cout << "FAIL " << testName << std::endl;
        std::cout << "  Expected :" << expected << "\n"; 
        std::cout << "  Got: " << got << "\n\n";
    }

    return (got != expected);
}
int AssertAndReport(int got, int expected, std::string testName){
    if (got == expected){
        std::cout << "PASS " << testName << std::endl;
    } else {
        std::cout << "FAIL " << testName << std::endl;
        std::cout << "  Expected :" << expected << "\n"; 
        std::cout << "  Got: " << got << "\n\n";
    }

    return (got != expected);
}

#endif // TESTS_H