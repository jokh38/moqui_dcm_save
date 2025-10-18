#include "library.h"

#include <iostream>

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

void greet(const std::string& name) {
    std::cout << "Hello, " << name << "!" << std::endl;
}
