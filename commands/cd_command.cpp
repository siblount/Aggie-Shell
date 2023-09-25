#include <stdlib.h>
#include <unistd.h>

#include "cd_command.hpp"
#include "../environment.hpp"
#include "../cli.hpp"

CDCommand::CDCommand(CLI* cli, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stdout) : Command(cli, args, __stdin, __stdout) {}

int CDCommand::Execute() {
    if (args.size() > 1) {
        *cli->standardError << "An error has occurred\n";
        return -1;
    }
    else if (args.empty() || args[0] == "~") {
        if (cli->env->chdir(cli->env->getenv("HOME")) == 0) {
            return 0;
        } else {
            *cli->standardError << "An error has occurred\n";
            return -1;
        }
    }
    else if (!args.empty() && cli->env->chdir(args[0]) == 0) {
        return 0;
    } else {
        *cli->standardError << "An error has occurred\n";
        return -1;
    }
}