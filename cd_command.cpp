#include <stdlib.h>
#include "cd_command.hpp"

CDCommand::CDCommand(std::vector<std::string> args, std::istream* __stdin, std::ostream* __stdout) : Command(args, __stdin, __stdout) {}

int CDCommand::Execute() {
    setenv("PWD", args[0].c_str(), 1);
}