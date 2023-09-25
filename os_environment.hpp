#pragma once

#include "os_environment.fwd.hpp"
#include "environment.hpp"

/// @brief An implementation of the Environment class that uses the OS's environment.
class OSEnvironment : public Environment {
    public:
        int setenv(std::string name, std::string value, bool overwrite = true) override;
        std::string getenv(std::string name) override;
        int chdir(std::string path) override;
        std::string getcwd() override;
};