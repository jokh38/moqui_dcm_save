#include <iostream>

#include "library.h"

int main() {
    std::cout << "Moqui DCM Save Application" << std::endl;
    std::cout << "==========================" << std::endl;

    // Test our library functions
    int a = 5, b = 3;
    std::cout << "Testing add(" << a << ", " << b << ") = " << add(a, b) << std::endl;
    std::cout << "Testing multiply(" << a << ", " << b << ") = " << multiply(a, b) << std::endl;

    greet("User");

    return 0;
}
