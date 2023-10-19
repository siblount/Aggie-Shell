#pragma once

#include "command.hpp"

/// @brief A command that runs a program with the given arguments and standard io streams.
/// The command runs a program in a seperate thread and waits for it to finish.
class ExternalCommand : public Command {
    public:
        ExternalCommand(CLI* cli, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stdout);
        int Execute() override;
};