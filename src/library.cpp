#include "moqui_dcm_save/library.hpp"
#include <iostream>

namespace moqui_dcm_save {

void Library::hello() {
    std::cout << "Hello from moqui_dcm_save library!" << std::endl;
}

int Library::add(int a, int b) {
    return a + b;
}

} // namespace moqui_dcm_save