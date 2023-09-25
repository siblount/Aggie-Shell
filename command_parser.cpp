#include <vector>
#include <string>

#include "command_parser.hpp"
#include "command_factory.hpp"
#include "commands/command.hpp"
#include "commands/nothing_command.hpp"

CommandParser::CommandParser(CommandFactory* factory) : factory{factory} {}

Command& CommandParser::Parse(std::string command) {
    // The first token is always the command name.
    // The rest are the arguments.
    std::vector<std::string> tokens;
    std::istringstream iss{command};
    std::string token;
    while (std::getline(iss >> std::ws, token, ' ')) {
        tokens.push_back(token);
    }

    if (tokens.size() == 0) {
        return *new NothingCommand();
    }
    // Remove the first token from the vector.
    std::string commandName = tokens[0];
    tokens.erase(tokens.begin());
    return factory->GetCommand(commandName, tokens);
}
