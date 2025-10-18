#include "moqui_dcm_save/library.hpp"

#include <iostream>

void moqui_dcm_save::Library::hello() {
    std::cout << "Hello from Library!" << std::endl;
}

int moqui_dcm_save::Library::add(int first_value, int second_value) {
    return first_value + second_value;
}
