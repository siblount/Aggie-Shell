#pragma once

#include "command.hpp"

/// @brief Changes the PATH environment variable.
class PathCommand : public Command {
    public:
        PathCommand(CLI* cli, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stdout);
        int Execute() override;
};