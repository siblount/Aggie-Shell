#include <vector>
#include <string>

#include "nothing_command.hpp"
#include "../environment.hpp"
#include "../cli.hpp"

NothingCommand::NothingCommand() : Command(nullptr, std::vector<std::string>{}, nullptr, nullptr, nullptr) {}

NothingCommand::NothingCommand(CLI* cli, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stderr, std::ostream* __stdout) : 
    Command(cli, args, __stdin, __stderr, __stdout) {}

// see I told you it does nothing.
int NothingCommand::Execute() {
    return 0;
}