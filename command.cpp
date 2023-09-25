#include "command.hpp"

Command::Command(std::vector<std::string> args, std::istream* __stdin, std::ostream* __stdout) : args(args), standard_input(__stdin), standard_output(__stdout) {}
