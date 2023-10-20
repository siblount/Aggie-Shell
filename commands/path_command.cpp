#include <vector>
#include <string>

#include "path_command.hpp"
#include "../environment.hpp"
#include "../cli.hpp"

PathCommand::PathCommand(CLI* cli, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stderr, std::ostream* __stdout) : 
    Command(cli, args, __stdin, __stderr, __stdout) {}

int PathCommand::Execute() {
    std::string newPath;
    for (const auto& path : args) {
        newPath += path + ":";
    }
    
    // Remove the trailing ':'
    if (!newPath.empty()) {
        newPath.pop_back();
    }

    if (cli->env->setenv("PATH", newPath, true) == 0) return 0;
    *cli->standardError << "An error has occurred\n";
    return -1;
}