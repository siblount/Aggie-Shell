#include "exit_command.hpp"
#include "../cli.hpp"
#include <thread>
#include <cstdlib>

ExitCommand::ExitCommand(CLI* cli, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stdout) : Command(cli, args, __stdin, __stdout) {}

int ExitCommand::Execute() {
    if (!args.empty()) {
        *cli->standardError << "An error has occurred\n";
        return -1;
    }
    *cli->standardOutput << "Exiting Aggie Shell by Solomon Blount..." << std::endl;
    return 0;
}