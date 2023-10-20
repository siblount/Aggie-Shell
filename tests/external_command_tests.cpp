#include <memory>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <cassert>

#include "../cli.hpp"
#include "../environment.hpp"
#include "util/cliutil.hpp"
#include "../commands/external_command.hpp"
#include "fakes/fake_command_factory.hpp"
#include "fakes/fake_environment.hpp"
#include "external_command_tests.hpp"

std::shared_ptr<CLI> ExternalCommandTests::NewCLI(CLIDependencies* deps) {
    auto cli = ::NewCLI(deps);
    FakeCommandFactory factory{*cli};
    cli->commandFactory = &factory;
    return cli;
}

void ExternalCommandTests::ExternalCommandTest() {
    auto deps = new CLIDependencies{};
    auto cli = ExternalCommandTests::NewCLI(deps);

    try {
        ExternalCommand cmd{cli.get(), std::vector<std::string>(), cli->standardInput, cli->standardError, cli->standardOutput};
    } catch (...) {
        std::cout << "ExternalCommandTest failed!" << std::endl;
        return;
    }
    
    std::cout << "ExternalCommandTest passed!" << std::endl;
}

void ExternalCommandTests::ExternalCommandEchoTest() {
    auto deps = new CLIDependencies{};
    auto cli = ExternalCommandTests::NewCLI(deps);
    auto args = std::vector<std::string>{"echo", "hello", "world"};
    ExternalCommand cmd{cli.get(), args, cli->standardInput, cli->standardError, cli->standardOutput};

    assert(cmd.Execute() == 0);
    assert(deps->cli_output->str().find("hello world") != std::string::npos);
    assert(deps->cli_error->str().empty());
    std::cout << "ExternalCommandEchoTest passed!" << std::endl;
}

void ExternalCommandTests::ExecuteTests() {
    ExternalCommandTests::ExternalCommandTest();
    ExternalCommandTests::ExternalCommandEchoTest();
}