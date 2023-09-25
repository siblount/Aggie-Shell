#include <unistd.h>
#include <iostream>

#include "os_environment.hpp"

int OSEnvironment::setenv(std::string name, std::string value, bool overwrite) {
    return ::setenv(name.c_str(), value.c_str(), overwrite);
}

std::string OSEnvironment::getenv(std::string name) {
    return ::getenv(name.c_str());
}

int OSEnvironment::chdir(std::string path) {
    return ::chdir(path.c_str());
}

std::string OSEnvironment::getcwd() {
    char* cwd = ::getcwd(NULL, 0);
    std::string cwd_str(cwd);
    delete[] cwd;
    return cwd_str;
}