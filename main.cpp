#include <iostream>
#include <unistd.h>
#include <string>
#include <memory>

#include "cli.hpp"
#include "os_environment.hpp"

int main(int argc, char** argv) {
    // Setup the CLI with default opts.
    // The CLI will use std::cin, std::cout, and std::cerr for input and output.
    // The CLI will use the environment variables from the current process.
    // The CLI will use the current working directory as the working directory.
    
    return CLI{}.Run();
}

