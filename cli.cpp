#include <iostream>
#include <unistd.h>
#include <sstream>
#include <filesystem>
#include <memory>

#include "cli.hpp"
#include "os_environment.hpp"
#include "command_factory.hpp"
#include "commands/command.hpp"
#include "commands/exit_command.hpp"
#include "command_parser.hpp"


CLI::CLI() : CLI(new OSEnvironment(), new CommandFactory(*this), &std::cin, &std::cerr, &std::cout) {}

CLI::CLI(Environment* env, CommandFactory* commandFactory, std::istream* standardInput, std::ostream* standard_error, std::ostream* standardOutput) : 
    env(env), commandFactory(commandFactory), standardInput(standardInput), standardError(standard_error), standardOutput(standardOutput) {}

int CLI::Run() {
    // Simply get the input from standard input and exit the while loop when the input is exactly "exit"
    std::string input;

    while (input != "force exit") {
        *standardOutput << GetAshSuffix();
        std::getline(*standardInput, input);
        try {
            std::unique_ptr<Command> command(&CommandParser{commandFactory}.Parse(input));
            command->Execute();

            // Special check if the command is the exit command.
            if (typeid(*command.get()) == typeid(ExitCommand) && command->args.size() == 0) {
                break;
            }
        } catch (std::exception& e) {
            *standardError << "An error has occurred\n";
        }
    }
    return 0;
}

int CLI::Run(std::istream& input) {
    std::string line;
    while (std::getline(input, line)) {
        // If it fails, then we stop and return the exit code.
        try {
            std::unique_ptr<Command> command(&CommandParser{commandFactory}.Parse(line));
            command->Execute();

            // Special check if the command is the exit command.
            if (typeid(command) == typeid(ExitCommand) && command->args.size() == 0) {
                return 0;
            }
        } catch (std::exception& e) {
            *standardError << "An error has occurred\n";
            break;
        }
    }
    commandFactory->GetCommand("exit", std::vector<std::string>{}).Execute();
    return 0;
}

std::string CLI::GetAshSuffix() {
    auto cwd = env->getcwd();
    auto home = env->getenv("HOME");

    // Create string builder (not really needed, I'm just exploring C++)
    std::ostringstream sb;
    // Insert "ash" into the string builder
    sb << "ash";
    // If the current working directory is the home directory, then just add a ">" to the string builder
    
    if (cwd == home) {
        sb << " > ";
    } else // Otherwise, add the current working directory to the string builder
    { 
        sb << " " << cwd << "> ";
    }
    std::string suffix = sb.str(); // Put everything in the string builder into a string (and free the buffer in the string builder)
    return suffix;
}