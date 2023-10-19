#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include <sstream>
#include <memory>
#include <unistd.h>

#include "util/cliutil.hpp"
#include "../command_factory.hpp"
#include "../commands/command.hpp"
#include "command_factory_tests.hpp"
#include "../cli.hpp"
#include "fakes/fake_environment.hpp"

void CommandFactoryTests::CommandFactoryTest() {
    CLI cli;
    CommandFactory factory(cli);
    std::cout << "CommandFactoryTest passed!" << std::endl;
}

void CommandFactoryTests::CommandFactoryEchoTest() {
    auto deps = std::make_unique<CLIDependencies>();
    auto cli = ::NewCLI(deps.get());
    deps->env->setenv("PATH", "/usr/bin");
    auto args = std::vector<std::string>{"hello", "world"};
    try {
        cli->commandFactory->GetCommand("echo", args);
    } catch (...) {
        std::cout << "CommandFactoryLocalEchoTest failed!" << std::endl;
        return;
    }
    std::cout << "CommandFactoryEchoTest passed!" << std::endl;
}

void CommandFactoryTests::CommandFactoryLocalEchoTest() {
    auto deps = std::make_unique<CLIDependencies>();
    auto cli = ::NewCLI(deps.get());
    std::string path{getcwd(nullptr, 0)};
    deps->env->setenv("PATH", path);
    auto args = std::vector<std::string>{"hello", "world"};
    try {
        cli->commandFactory->GetCommand("echo", args);
    } catch (...) {
        std::cout << "CommandFactoryLocalEchoTest failed!" << std::endl;
        return;
    }

    std::cout << "CommandFactoryLocalEchoTest passed!" << std::endl;
}

void CommandFactoryTests::CommandFactoryNotFoundTest() {
    auto deps = std::make_unique<CLIDependencies>();
    auto cli = ::NewCLI(deps.get());
    deps->env->setenv("PATH", "");
    auto args = std::vector<std::string>{"hello", "world"};
    try {
        cli->commandFactory->GetCommand("notfound", args);
    } catch (...) {
        std::cout << "CommandFactoryNotFoundTest passed!" << std::endl;
        return;
    }
    std::cout << "CommandFactoryNotFoundTest failed!" << std::endl;
}

void CommandFactoryTests::ExecuteTests() {
    CommandFactoryTest();
    CommandFactoryEchoTest();
    CommandFactoryLocalEchoTest();
    CommandFactoryNotFoundTest();
}