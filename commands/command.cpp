#include "command.hpp"

Command::Command(CLI* cli, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stdout) : 
    cli(cli), args(args), standardInput(__stdin), standardOutput(__stdout) {}
