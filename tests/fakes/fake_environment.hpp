#pragma once
#include <unordered_map>

#include "../../environment.hpp"

class FakeEnvironment : public Environment {
    public:
        /// @brief The environment variable collection used for faking the environment (setenv, getenv, and get_all_env)/
        std::unordered_map<std::string, std::string> env;

        /// @brief Sets the environment variable to the internal map.
        /// @param name The name of the environment variable to set.
        /// @param value The value of the environment variable to set.
        /// @param overwrite Whether or not to overwrite the environment variable if it already exists. If it exists, -1 will be returned.
        /// @return -1 for any errors, otherwise 0.
        int setenv(std::string name, std::string value, bool overwrite = true) override;
        /// @brief Gets the environment variable from the internal map.
        /// @param name The name of the environment variable to get.
        /// @return An empty string if the environment variable does not exist, otherwise the value of the environment variable.
        std::string getenv(std::string name) override;
        
        /// @brief Changes the current working directory by modifying the "PWD" environment variable.
        /// @param path The path to set the current working directory.
        /// @return 0 for success, -1 for any errors.
        int chdir(std::string path) override;

        /// @brief Returns the PWD environment variable.
        /// @return The value of the PWD environment variable or an empty string if it does not exist.
        std::string getcwd() override;
};