#pragma once

#include "command.hpp"

/// @brief A command that only checks for it the exit command is valid and sends info to the standard io.
class ExitCommand : public Command {
    public:
        ExitCommand(CLI* cli, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stderr, std::ostream* __stdout);
        int Execute() override;
};