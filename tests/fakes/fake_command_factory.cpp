#include "fake_command_factory.hpp"

FakeCommandFactory::FakeCommandFactory(CLI& cli) : CommandFactory(cli) {}

Command& FakeCommandFactory::GetCommand(std::string input, std::vector<std::string> args) {
    if (commands.find(input) == commands.end()) {
        throw std::runtime_error("Command not found");
    }
    return *commands[input];
}

Command& FakeCommandFactory::GetCommand(std::string input, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stderr, std::ostream* __stdout) {
    if (commands.find(input) == commands.end()) {
        throw std::runtime_error("Command not found");
    }
    return *commands[input];
}