#include <iostream>
#include <string>
#include "cnpy.h"

void inspectNpyFile(const std::string& filename)
{
    // Step 1: Load file
    cnpy::NpyArray array = cnpy::npy_load(filename);

    // Step 2: Print dimensions
    std::cout << "Dimensions: "
              << array.shape.size() << "\n";

    // Step 3: Print shape
    std::cout << "Shape: ";

    for (size_t dim : array.shape) {
        std::cout << dim << " ";
    }

    std::cout << "\n";

    // Step 4: Print bytes per value
    std::cout << "Bytes per value: "
              << array.word_size << "\n";

    // Step 5: Print memory order
    std::cout << "Fortran order: "
              << array.fortran_order << "\n";
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: "
                  << argv[0] << " file.npy\n";
        return 1;
    }


    try {
        inspectNpyFile(argv[1]);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}