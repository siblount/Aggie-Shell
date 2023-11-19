#include <future>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <sstream>


#include "cliutil.hpp"
#include "../../cli.hpp"
#include "../../command_factory.hpp"
#include "../fakes/fake_environment.hpp"


std::shared_ptr<CLI> NewCLI(CLIDependencies* deps) {
    deps = deps ? deps : new CLIDependencies();
    deps->env = std::make_shared<FakeEnvironment>();
    deps->commandFactory = std::make_shared<CommandFactory>();
    deps->cli_input = std::make_shared<std::istringstream>("exit");
    deps->cli_output = std::make_shared<std::ostringstream>();
    deps->cli_error = std::make_shared<std::ostringstream>();
    deps->cli = std::make_shared<CLI>(deps->env.get(), deps->commandFactory.get(), deps->cli_input.get(), deps->cli_error.get(), deps->cli_output.get() );
    deps->commandFactory->cli = *deps->cli;

    deps->cli->env->setenv("HOME", "/home/user");
    deps->cli->env->setenv("PWD", "/home/user");
    return deps->cli;
}

int RunCLI(CLI* cli) {
    // Wrap the function call in a lambda to pass to std::async
    auto future = std::async(std::launch::async, [cli](){
        try {
            return cli->Run();
        } catch (const std::exception& e) {
            std::cerr << "Exception caught in async task: " << e.what() << '\n';
            return -1;
        }
    });

    // Wait for the result for a certain amount of time
    try {
        if (!future.valid()) {
            throw std::runtime_error("CLI run future is invalid");
        }
        if (future.wait_for(std::chrono::seconds(5)) == std::future_status::timeout) {
            throw std::runtime_error("CLI run future timed out");
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught while waiting for async task: " << e.what() << '\n';
        return -1;
    }
    
    // Retrieve the result from the future
    int result = future.get();

    // Check if the result is the exit code
    if (result != 0) {
        std::cerr << "CLI exited with code " << char(result) << '\n';
        return -1;
    }

    return result;
}

int RunCLI(CLI* cli, std::istream& input) {
    // Wrap the function call in a lambda to pass to std::async
    auto future = std::async(std::launch::async, [cli, &input](){
        try {
            return cli->Run(input);
        } catch (const std::exception& e) {
            std::cerr << "Exception caught in async task: " << e.what() << '\n';
            return -1;
        }
    });

    // Wait for the result for a certain amount of time
    try {
        if (!future.valid()) {
            throw std::runtime_error("CLI run future is invalid");
        }
        if (future.wait_for(std::chrono::seconds(5)) == std::future_status::timeout) {
            throw std::runtime_error("CLI run future timed out");
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught while waiting for async task: " << e.what() << '\n';
        return -1;
    }
    
    // Retrieve the result from the future
    int result = future.get();

    // Check if the result is the exit code
    if (result != 0) {
        std::cerr << "CLI exited with code " << char(result) << '\n';
        return -1;
    }

    return result;
}