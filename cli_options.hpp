#pragma once

#include "environment.hpp"
#include "command_factory.fwd.hpp"

/// @brief Options for the CLI.
struct CLIOptions {
    /// @brief The environment that the CLI is running in.
    Environment* env;
    /// @brief The command factory that the CLI will use to get commands.
    CommandFactory* command_factory;
    /// @brief The standard input stream.
    std::istream* standard_input;
    /// @brief The standard error stream.
    std::ostream* standard_error;
    /// @brief The standard output stream.
    std::ostream* standard_output;

    CLIOptions();
    CLIOptions(Environment* env, CommandFactory* command_factory, std::istream* standard_input, std::ostream* standard_error, std::ostream* standard_output);
};