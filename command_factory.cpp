#include <unistd.h>
#include <sstream>

#include "cli.hpp"

#include "command_factory.hpp"
#include "commands/command.hpp"
#include "commands/exit_command.hpp"
#include "commands/path_command.hpp"
#include "commands/cd_command.hpp"
#include "commands/external_command.hpp"
#include "environment.hpp"

CommandFactory::CommandFactory() : cli(*new CLI()) {}

CommandFactory::CommandFactory(CLI& cli) : cli(cli) {}

Command& CommandFactory::GetCommand(std::string name, std::vector<std::string> args) {
    return GetCommand(name, args, cli.standardInput, cli.standardError, cli.standardOutput);
}

Command& CommandFactory::GetCommand(std::string name, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stderr, std::ostream* __stdout) {
    if (name == "cd") {
        return *new CDCommand(&cli, args, __stdin, __stderr, __stdout);
    } else if (name == "exit") {
        return *new ExitCommand(&cli, args, __stdin, __stderr, __stdout);
    } else if (name == "path") {
        return *new PathCommand(&cli, args, __stdin, __stderr, __stdout);
    } else if (ExternalCommandExists(name)) {
        // Pass in the name as part of the argument.
        args.insert(args.begin(), name);
        return *new ExternalCommand(&cli, args, __stdin, __stderr, __stdout);
    }

    // If the command was not found in any of the directories, throw an error.
    throw std::runtime_error("Command not found");
}

bool CommandFactory::ExternalCommandExists(std::string name) {
    // First check if it exists in the current directory (or an absolute path was given).

    // Check to see if we can access and execute the program.
    if (access(name.c_str(), X_OK) == 0) return true;
    // If it doesn't exist in the current directory, check through the PATH environment variable.

    // Get the directories listed in the PATH environment variable.
    std::stringstream path(cli.env->getenv("PATH"));
    std::string dir;
    while (std::getline(path, dir, ':')) {
        // Construct the full path to the command.
        std::string full_path = dir + "/" + name;

        // Check to see if we can access and execute the program.
        if (access(full_path.c_str(), X_OK) == 0) return true;
    }

    // We checked in the current directory (or the absolute path) and the PATH environment variable
    // and the program was not executable, does not exist on disk, or do not have permission to execute it.
    return false;
}