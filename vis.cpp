#include "./src/matrixmap.hpp"
#include <iostream>


int main(int argc, char *argv[]) {
    if (argc <= 1) {
        std::cout << "Map file not specified.\n";
        return 0;
    }
    const char *f = argv[1];
    BinaryMatrixMap map(f);
    map.exportBMP("map.bmp");
    return 0;
}
