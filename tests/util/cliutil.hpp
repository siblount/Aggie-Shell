#pragma once
#include <memory>
#include "../../cli.fwd.hpp"
#include "../../command_factory.fwd.hpp"
#include "../fakes/fake_environment.fwd.hpp"

struct CLIDependencies {
    std::shared_ptr<CLI> cli;
    std::shared_ptr<FakeEnvironment> env;
    std::shared_ptr<CommandFactory> commandFactory;
    std::shared_ptr<std::istringstream> cli_input;
    std::shared_ptr<std::ostringstream> cli_output;
    std::shared_ptr<std::ostringstream> cli_error;
};

/// @brief Runs the CLI in a separate thread and waits for the result.
/// @param cli The CLI to run.
int RunCLI(CLI* cli);

std::shared_ptr<CLI> NewCLI(CLIDependencies* deps);