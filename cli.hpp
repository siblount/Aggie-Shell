#pragma once
#include <iostream>

#include "cli.fwd.hpp"
#include "environment.fwd.hpp"
#include "command_factory.fwd.hpp"

struct CLI {
    /// @brief The options of the CLI.
    Environment* env;
    /// @brief The factory to use to create commands.
    CommandFactory* commandFactory;
    /// @brief The input stream to read from.
    std::istream* standardInput;
    /// @brief The error stream to write to.
    std::ostream* standardError;
    /// @brief The output stream to write to.
    std::ostream* standardOutput;

    /// @brief Initializes a new instance of the CLI with default options.
    CLI();
    /// @brief Initializes a new instance of the CLI with the given options.
    /// @param env The environment to use for the CLI.
    /// @param commandFactory The factory to use to create commands.
    /// @param standardInput The input stream to read from.
    /// @param standardError The error stream to write to.
    /// @param standardOutput The output stream to write to.
    CLI(Environment* env, CommandFactory* commandFactory, std::istream* standardInput, std::ostream* standardError, std::ostream* standardOutput);

    /// @brief Runs the CLI in interactive mode.
    /// @return The exit code of the CLI.
    int Run();
    /// @brief Runs the CLI in batch mode with the given input.
    /// @param input The input to run the CLI with.
    /// @return The exit code of the CLI.
    int Run(std::istream& input);
    private:
        /// @brief Gets the suffix to display after the command prompt.
        /// @return "ash>" if the current working directory is the home directory, otherwise "ash:cwd>"
        std::string GetAshSuffix();
};