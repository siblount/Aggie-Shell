#include "cli.hpp"

#include "command_factory.hpp"
#include "commands/command.hpp"
#include "commands/exit_command.hpp"
#include "commands/path_command.hpp"
#include "commands/cd_command.hpp"

CommandFactory::CommandFactory() : cli(*new CLI()) {}

CommandFactory::CommandFactory(CLI& cli) : cli(cli) {}

Command& CommandFactory::GetCommand(std::string name, std::vector<std::string> args) {
    return GetCommand(name, args, cli.standardInput, cli.standardError, cli.standardOutput);
}

Command& CommandFactory::GetCommand(std::string name, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stderr, std::ostream* __stdout) {
    if (name == "cd") {
        return *new CDCommand(&cli, args, __stdin, __stdout);
    } else if (name == "exit") {
        return *new ExitCommand(&cli, args, __stdin, __stdout);
    } else if (name == "path") {
        return *new PathCommand(&cli, args, __stdin, __stdout);
    } else {
        throw std::runtime_error("Command not found");
    }
}