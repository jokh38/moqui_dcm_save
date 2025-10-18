#include <iostream>

#include "moqui_dcm_save/library.hpp"

int main() {
    std::cout << "Moqui DCM Save Application" << std::endl;
    std::cout << "==========================" << std::endl;

    // Test our library functions
    moqui_dcm_save::Library lib{};
    lib.hello();

    int first_value = 5;
    int second_value = 3;
    std::cout << "Testing add(" << first_value << ", " << second_value
              << ") = " << lib.add(first_value, second_value) << std::endl;

    return 0;
}
