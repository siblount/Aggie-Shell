#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "command.fwd.hpp"
#include "../cli.fwd.hpp"

/// @brief An abstract class representing a command to be executed.
class Command {
    public:
        /// @brief The corresponding CLI to perform actions on.
        CLI* cli;
        /// @brief The arguments to send to the command; do not include the command name itself or dashes.
        std::vector<std::string> args;
        /// @brief The standard input stream to use for the command.
        std::ostream* standardOutput;
        /// @brief The standard error stream to use for the command.
        std::ostream* standardError;
        /// @brief The standard output stream to use for the command.
        std::istream* standardInput;
        /// @brief Creates a new command with the given arguments, standard input, and standard output.
        /// @param cli The corresponding CLI to perform actions on.
        /// @param args The arguments to send to the command; do not include the command name itself or dashes.
        /// @param __stdin The standard input stream to use for the command. If NULL, will use default standard input.
        /// @param __stdout The standard output stream to use for the command. If NULL, will use default standard output.
        Command(CLI* cli, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stderr, std::ostream* __stdout);
        
        /// @brief Destroys the command and releases any streams if they are ofstream_extended.
        ~Command();
        
        /// @brief Executes the command.
        /// @return The exit code of the command.
        virtual int Execute() = 0;
        
};