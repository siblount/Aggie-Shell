#pragma once

#include "command.hpp"

/// @brief A built-in command to change the current working directory.
class CDCommand : public Command {
    public:
        CDCommand(CLI* cli, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stdout);
        int Execute() override;
};