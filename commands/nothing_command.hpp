#pragma once

#include "command.hpp"

/// @brief A command that does everything in it's power to do nothing (yes, it literally does nothing).
/// @note This is used the event where the user inputs nothing but whitespace or an empty string.
class NothingCommand : public Command {
    public:
        NothingCommand();
        NothingCommand(CLI* cli, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stdout);
        int Execute() override;
};