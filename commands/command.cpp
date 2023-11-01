#include "command.hpp"
#include "../ofstream_extended.hpp"

Command::Command(CLI* cli, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stderr, std::ostream* __stdout) : 
    cli(cli), args(args), standardInput(__stdin), standardError(__stderr), standardOutput(__stdout) {}

Command::~Command() {
    // Delete the standard output, input, and error streams if they are ofstream_extended.
    try {
        if (dynamic_cast<ofstream_extended*>(standardOutput)) {
            delete standardOutput;
        }
    } catch (...) {}
    try {
        if (dynamic_cast<ofstream_extended*>(standardInput)) {
            delete standardInput;
        }
    } catch (...) {}
}