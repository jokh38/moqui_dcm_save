#include <iostream>
#include "moqui_dcm_save/library.hpp"

int main() {
    std::cout << "Hello, moqui_dcm_save!" << std::endl;

    moqui_dcm_save::Library lib;
    lib.hello();

    int result = lib.add(5, 3);
    std::cout << "5 + 3 = " << result << std::endl;

    return 0;
}
