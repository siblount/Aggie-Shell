#include <vector>
#include <string>
#include <regex>
#include <sstream>

#include "command_parser.hpp"
#include "command_factory.hpp"
#include "commands/command.hpp"
#include "commands/nothing_command.hpp"
#include "ofstream_extended.hpp"

CommandParser::CommandParser(CommandFactory* factory) : factory{factory} {}

// TODO: Fails when the following is passed 'echo 'hello world' > 'file.txt'
std::vector<std::string> ParseCommandLine(std::string commandLine) {
    // This regex matches quoted strings and non-whitespace strings.
    // Such as "echo 'hello world'" as "echo", "'hello world'".
    // Or "echo hello world" as "echo", "hello", "world".
    // ("[^"]*"|'[^']*')|(`\S+`|\S+) <-- hangs
    // ((\"[^\"]*\")|(\'[^\']*\')|(`[^`]*`)|(\S+))
    // (?<=\s|^)(?:"[^"]*"|'[^']*'|\S+)
    // std::regex re(R"(".+"|\'.+\'|\S+)"); // <-- old regex
    std::regex re("(\"[^\"]*\")|('[^']*')|(`[^`]*`)|(\\S+)"); 

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

    // If there is more than one ">" character, then the command is invalid.
    if (std::count(tokens.begin(), tokens.end(), ">") > 1) {
        throw std::runtime_error("Too many redirects");
    }

    // Verify to see if we have redirected standard output to a file.
    // If it contains the ">" character, then create a file stream to the next token in the vector.
    auto it = std::find(tokens.begin(), tokens.end(), ">");
    if (it != tokens.end()) {
        // Create a file stream to the next token in the vector.
        std::string fileName = *(it + 1);
        auto file = new ofstream_extended(fileName);
        // Remove both the ">" character and the token after that from the vector.
        tokens.erase(it, it + 2);
        return factory->GetCommand(commandName, tokens, &std::cin, file, file);
    }
    // Otherwise, use default stdin, stdout, and stderr.
    return factory->GetCommand(commandName, tokens);
}
