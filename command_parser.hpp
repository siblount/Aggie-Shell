#pragma once
#include <string>
#include <sstream>

#include "command_factory.fwd.hpp"
#include "commands/command.fwd.hpp"

class CommandParser {
    public:
        CommandFactory* factory;
        CommandParser(CommandFactory* factory);
        Command& Parse(std::string command);
};