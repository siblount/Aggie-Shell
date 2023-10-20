#include <vector>
#include <string>
#include <regex>
#include <sstream>

#include "command_parser.hpp"
#include "command_factory.hpp"
#include "commands/command.hpp"
#include "commands/nothing_command.hpp"

CommandParser::CommandParser(CommandFactory* factory) : factory{factory} {}

std::vector<std::string> ParseCommandLine(std::string commandLine) {
    // This regex matches quoted strings and non-whitespace strings.
    // Such as "echo 'hello world'" as "echo", "'hello world'".
    // Or "echo hello world" as "echo", "hello", "world".
    std::regex re(R"(".+"|\'.+\'|\S+)"); 
    std::sregex_iterator it(commandLine.begin(), commandLine.end(), re);
    std::sregex_iterator reg_end;
    std::vector<std::string> matches;

    for (; it != reg_end; ++it) {
        std::string match = it->str();
        // Remove quotes from the match.
        if (match.front() == '"' && match.back() == '"') {
            match = match.substr(1, match.length() - 2);
        } else if (match.front() == '\'' && match.back() == '\'') {
            match = match.substr(1, match.length() - 2);
        }
        matches.push_back(match);
    }

    return matches;
}

Command& CommandParser::Parse(std::string command) {
    std::vector<std::string> tokens = ParseCommandLine(command);

    if (tokens.size() == 0) {
        return *new NothingCommand();
    }
    // Remove the first token from the vector.
    std::string commandName = tokens[0];
    tokens.erase(tokens.begin());
    return factory->GetCommand(commandName, tokens);
}
