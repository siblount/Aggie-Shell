#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <cassert>

#include "../cli.hpp"
#include "../environment.hpp"
#include "util/cliutil.hpp"
#include "../commands/exit_command.hpp"
#include "fakes/fake_command_factory.hpp"
#include "exit_command_tests.hpp"

std::shared_ptr<CLI> ExitCommandTests::NewCLI(CLIDependencies* deps) {
    auto cli = ::NewCLI(deps);
    FakeCommandFactory factory{*cli};
    cli->commandFactory = &factory;
    return cli;
}

void ExitCommandTests::ExitCommandTest() {
    auto deps = new CLIDependencies{};
    auto cli = ExitCommandTests::NewCLI(deps);

    try {
        ExitCommand cmd{cli.get(), std::vector<std::string>(), cli->standardInput, cli->standardOutput};
    } catch (...) {
        std::cout << "ExitCommandTest failed!" << std::endl;
        return;
    }
    
    std::cout << "ExitCommandTest passed!" << std::endl;
}

void ExitCommandTests::ExitCommandNoArgsTest() {
    auto deps = new CLIDependencies{};
    auto cli = ExitCommandTests::NewCLI(deps);
    ExitCommand cmd{cli.get(), std::vector<std::string>(), cli->standardInput, cli->standardOutput};

    assert(cmd.Execute() == 0);
    assert(deps->cli_output->str().find("Exiting Aggie Shell by Solomon Blount...") != std::string::npos);
    assert(deps->cli_error->str().empty());
    std::cout << "ExitCommandNoArgsTest passed!" << std::endl;
}

void ExitCommandTests::ExitCommandTooManyArgsTest() {
    auto deps = new CLIDependencies{};
    auto cli = ExitCommandTests::NewCLI(deps);
    ExitCommand cmd{cli.get(), std::vector<std::string>{"arg1"}, cli->standardInput, cli->standardOutput};

    assert(cmd.Execute() == -1);
    assert(deps->cli_output->str().empty());
    assert(deps->cli_error->str().find("An error has occurred") != std::string::npos);
    std::cout << "ExitCommandTooManyArgsTest passed!" << std::endl;
}

void ExitCommandTests::ExecuteTests() {
    ExitCommandTests::ExitCommandTest();
    ExitCommandTests::ExitCommandNoArgsTest();
    ExitCommandTests::ExitCommandTooManyArgsTest();
}