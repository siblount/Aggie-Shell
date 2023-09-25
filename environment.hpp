#pragma once
#include <string>

#include "environment.fwd.hpp"

/// @brief An abstract class representing the environment of the shell.
class Environment {
    public:
    /// @brief Sets the given environment variable to the given value.
    /// @param name The name of the environment variable to set.
    /// @param value The value to set the environment variable to.
    /// @param overwrite Whether to overwrite if it already exists (will return -1 if false and it already exists).
    /// @return -1 if any errors occurred, 0 otherwise.
    virtual int setenv(std::string name, std::string value, bool overwrite = true) = 0;
    /// @brief Gets the value of the given environment variable.
    /// @param name The name of the environment variable to get.
    /// @return The value of the environment variable, or an empty string if it does not exist.
    virtual std::string getenv(std::string name) = 0;
    /// @brief Changes the current working directory to the given path.
    /// @param path The path to change the current working directory to.
    /// @return -1 if any errors occurred, 0 otherwise.
    virtual int chdir(std::string path) = 0;
    /// @brief Gets the current working directory.
    /// @return The current working directory.
    virtual std::string getcwd() = 0;
};