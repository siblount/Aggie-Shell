#include "command.hpp"

Command::Command(CLI* cli, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stderr, std::ostream* __stdout) : 
    cli(cli), args(args), standardInput(__stdin), standardError(__stderr), standardOutput(__stdout) {}
