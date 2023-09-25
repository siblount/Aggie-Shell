#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <cassert>

#include "../cli.hpp"
#include "../environment.hpp"
#include "util/cliutil.hpp"
#include "../commands/path_command.hpp"
#include "fakes/fake_command_factory.hpp"
#include "fakes/fake_environment.hpp"
#include "path_command_tests.hpp"

std::shared_ptr<CLI> PathCommandTests::NewCLI(CLIDependencies* deps) {
    auto cli = ::NewCLI(deps);
    FakeCommandFactory factory{*cli};
    cli->commandFactory = &factory;
    return cli;
}

void PathCommandTests::PathCommandTest() {
    auto deps = new CLIDependencies{};
    auto cli = PathCommandTests::NewCLI(deps);

    try {
        PathCommand cmd{cli.get(), std::vector<std::string>(), cli->standardInput, cli->standardOutput};
    } catch (...) {
        std::cout << "PathCommandTest failed!" << std::endl;
        return;
    }
    
    std::cout << "PathCommandTest passed!" << std::endl;
}

void PathCommandTests::PathCommandNoArgsTest() {
    auto deps = new CLIDependencies{};
    auto cli = PathCommandTests::NewCLI(deps);
    PathCommand cmd{cli.get(), std::vector<std::string>(), cli->standardInput, cli->standardOutput};

    assert(cmd.Execute() == 0);
    assert(deps->env->getenv("PATH") == "");
    assert(deps->cli_error->str().empty());
    std::cout << "PathCommandNoArgsTest passed!" << std::endl;
}

void PathCommandTests::PathCommandOneArgTest() {
    auto deps = new CLIDependencies{};
    auto cli = PathCommandTests::NewCLI(deps);
    PathCommand cmd{cli.get(), std::vector<std::string>{"arg1"}, cli->standardInput, cli->standardOutput};

    assert(cmd.Execute() == 0);
    assert(deps->env->getenv("PATH") == "arg1");
    assert(deps->cli_error->str().empty());
    std::cout << "PathCommandOneArgTest passed!" << std::endl;
}

void PathCommandTests::PathCommandMultipleArgTest() {
    auto deps = new CLIDependencies{};
    auto cli = PathCommandTests::NewCLI(deps);
    PathCommand cmd{cli.get(), std::vector<std::string>{"arg1", "arg2", "arg3"}, cli->standardInput, cli->standardOutput};

    assert(cmd.Execute() == 0);
    assert(deps->env->getenv("PATH") == "arg1:arg2:arg3");
    assert(deps->cli_error->str().empty());
    std::cout << "PathCommandMultipleArgTest passed!" << std::endl;
}

void PathCommandTests::ExecuteTests() {
    PathCommandTests::PathCommandTest();
    PathCommandTests::PathCommandNoArgsTest();
    PathCommandTests::PathCommandOneArgTest();
    PathCommandTests::PathCommandMultipleArgTest();
}
