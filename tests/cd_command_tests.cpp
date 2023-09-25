#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <cassert>

#include "cd_command_tests.hpp"
#include "../commands/cd_command.hpp"
#include "util/cliutil.hpp"
#include "fakes/fake_command_factory.hpp"
#include "../environment.hpp"
#include "../os_environment.hpp"
#include "../cli.hpp"

std::shared_ptr<CLI> CDCommandTests::NewCLI(CLIDependencies* deps) {
    auto cli = ::NewCLI(deps);
    FakeCommandFactory factory{*cli};
    cli->commandFactory = &factory;
    return cli;
}

void CDCommandTests::CDCommandTest() {
    CLIDependencies deps;
    auto cli = CDCommandTests::NewCLI(&deps);

    try {
        CDCommand(cli.get(), std::vector<std::string>(), cli->standardInput, cli->standardOutput);
    } catch (std::exception& ex) {
        std::cout << "CDCommandTest failed!" << std::endl;
        return;
    }
    std::cout << "CDCommandTest passed!" << std::endl;
}

void CDCommandTests::CDCommandValidPathTest() {
    CLIDependencies deps;
    auto cli = CDCommandTests::NewCLI(&deps);

    CDCommand cdCommand(cli.get(), std::vector<std::string>{"/loser"}, cli->standardInput, cli->standardOutput);
    cdCommand.Execute();

    assert(cli->env->getenv("PWD") == "/loser");
    std::cout << "CDCommandValidPathTest passed!" << std::endl;
}

void CDCommandTests::CDCommandNoArgsTest() {
    CLIDependencies deps;
    auto cli = CDCommandTests::NewCLI(&deps);

    CDCommand cdCommand(cli.get(), std::vector<std::string>(), cli->standardInput, cli->standardOutput);
    cdCommand.Execute();

    assert(cli->env->getenv("PWD") == cli->env->getenv("HOME"));
    assert(deps.cli_error->str().empty());
    std::cout << "CDCommandNoArgsTest passed!" << std::endl;
}

void CDCommandTests::CDCommandBadPathTest() {
    CLIDependencies deps;
    OSEnvironment env;

    // NOTE: This time we are using the real OS environment, but this path better not exist on anyone's computer.
    auto cli = CDCommandTests::NewCLI(&deps);
    cli->env = &env;

    CDCommand cdCommand(cli.get(), std::vector<std::string>{"/the/secret/krabby/patty/formula/secure1234"}, cli->standardInput, cli->standardOutput);
    cdCommand.Execute();

    assert(deps.cli_error->str().find("An error has occurred") != std::string::npos);
    assert(cli->env->getenv("PWD") != "/the/secret/krabby/patty/formula/secure1234");
    std::cout << "CDCommandBadPathTest passed!" << std::endl;
}


void CDCommandTests::CDCommandTooManyArgsTest() {
    CLIDependencies deps;
    auto cli = CDCommandTests::NewCLI(&deps);

    CDCommand cdCommand(cli.get(), std::vector<std::string>{"/loser", "/loser2"}, cli->standardInput, cli->standardOutput);
    cdCommand.Execute();

    assert(deps.cli_error->str().find("An error has occurred") != std::string::npos);
    assert(cli->env->getenv("PWD") == cli->env->getenv("HOME"));
    std::cout << "CDCommandTooManyArgsTest passed!" << std::endl;
}

void CDCommandTests::ExecuteTests() {
    CDCommandTest();
    CDCommandValidPathTest();
    CDCommandBadPathTest();
    CDCommandNoArgsTest();
}