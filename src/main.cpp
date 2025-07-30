#include "Engine.h"
#include <iostream>

/*int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path/to/data.csv>\n";
        return 1;
    }

    std::string filepath = argv[1]; // Get CSV filename from command line
    Engine engine(filepath);        // Pass it to the Engine constructor
    engine.Run();                   // Run the engine
    std::cout << "Engine execution completed successfully.\n";
    return 0;
}*/

int main() {
    std::string filepath = "data/data.csv"; // Default path to CSV file
    Engine engine(filepath);        // Pass it to the Engine constructor
    engine.Run();                   // Run the engine
    std::cout << "Engine execution completed successfully.\n";
    return 0;
}
