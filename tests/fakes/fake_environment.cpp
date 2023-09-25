#include "fake_environment.hpp"

int FakeEnvironment::setenv(std::string name, std::string value, bool overwrite) {
    if (env.find(name) != env.end() && !overwrite) {
        return -1;
    }
    env[name] = value;
    return 0;
}

std::string FakeEnvironment::getenv(std::string name) {
    if (env.find(name) == env.end()) {
        return "";
    }
    return env[name];
}

int FakeEnvironment::chdir(std::string path) {
    return setenv("PWD", path);
}

std::string FakeEnvironment::getcwd() {
    return getenv("PWD");
}