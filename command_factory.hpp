#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "command_factory.fwd.hpp"
#include "commands/command.fwd.hpp"
#include "cli.fwd.hpp"

/// @brief The command factory.
class CommandFactory {
    public:
        /// @brief The CLI options that will be passed to the commands.
        CLI& cli;
        
        /// @brief Creates a new builtin command factory.
        CommandFactory();
        /// @brief Creates a new builtin command factory.
        /// @note Make sure to delete the command after using it.
        /// @param cli The CLI context.
        CommandFactory(CLI& cli);
        /// @brief Gets a builtin command with the given name and arguments and sets the standard input and output to the CLI's.
        /// @param name The name of the command.
        /// @param args The arguments to the command.
        virtual Command& GetCommand(std::string name, std::vector<std::string> args);
        /// @brief Gets a builtin command with the given name and arguments and sets the standard input and output to the given streams.
        /// @note Make sure to delete the command after using it.
        /// @param name The name of the command.
        /// @param args The arguments to the command.
        /// @param __stdin The standard input stream.
        /// @param __stderr The standard error stream.
        /// @param __stdout The standard output stream.
        /// @exception std::invalid_argument Thrown if the command is not found.
        virtual Command& GetCommand(std::string name, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stderr, std::ostream* __stdout);
};