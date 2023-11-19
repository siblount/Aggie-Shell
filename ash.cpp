// Solomon Blount
// 9/25/2023
// COMP350
// This is the main file for the ash shell. 

// WARNING: THIS WILL NOT BUILD IF YOU ATTEMPT TO BUILD ONLY WITH ash.cpp. YOU MUST BUILD WITH THE INSTRUCTIONS IN THE README FILE!!!
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <memory>

#include "cli.hpp"

int main(int argc, char** argv) {
    // Setup the CLI with default opts.
    // The CLI will use std::cin, std::cout, and std::cerr for input and output.
    // The CLI will use the environment variables from the current process.
    // The CLI will use the current working directory as the working directory.
    if (argc > 1) {
        std::string input = argv[1];
        try {
            std::ifstream fileStream(input);
            return CLI{}.Run(fileStream);
        } catch (...) {
            std::cerr << "An error has occurred\n";
            return 0;
        }
    } else return CLI{}.Run();
}

