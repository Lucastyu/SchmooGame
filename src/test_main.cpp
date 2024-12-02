#include "test_interface.hpp"
#include <iostream>

int main() {
    TestInterface tester("test_cases.txt", "game_log.txt");
    
    if (tester.runTests()) {
        std::cout << "All tests passed!\n";
        return 0;
    } else {
        std::cout << "Tests failed!\n";
        return 1;
    }
}