#include <cassert>
#include <memory>
#include <sstream>
#include <iostream>

#include "cli_tests.hpp"
#include "util/cliutil.hpp"
#include "../cli.hpp"
#include "fakes/fake_environment.hpp"
#include "../command_factory.hpp"

/// @brief Tests the CLI class does not throw any exceptions.
void CLITests::CLITest() {
    try {
        NewCLI(nullptr);
    } catch (...) {
        std::cout << "CLITest failed!" << std::endl;
    }
    std::cout << "CLITest passed!" << std::endl;
}

/// @brief Tests the CLI will exit when the input is "exit", the current error code is returned, and 
/// "ash>" is printed to standard output.
void CLITests::CLIHomeCursorTest() {
    CLIDependencies deps;
    auto cli = NewCLI(&deps);
    assert(RunCLI(cli.get()) == 0);
    assert(deps.cli_output->str().find("ash >") != std::string::npos);
    assert(deps.cli_error->str().empty());
    std::cout << "CLIHomeCursorTest passed!" << std::endl;
}

/// @brief Tests the CLI will exit when the input is "exit", the current error code is returned, and 
/// "ash /clearly/not/the/home/path>" is printed to standard output.
void CLITests::CLINonHomeCursorTest() {    
    CLIDependencies deps;
    auto cli = NewCLI(&deps);
    cli->env->setenv("PWD", "/clearly/not/the/home/path");

    assert(RunCLI(cli.get()) == 0);
    assert(deps.cli_output->str().find("ash /clearly/not/the/home/path>") != std::string::npos);
    assert(deps.cli_error->str().empty());
    std::cout << "CLINonHomeCursorTest passed!" << std::endl;
}

/// @brief Tests that the CLI does not exit when an exception is thrown.
void CLITests::CLIDoesntExitOnError() {
    CLIDependencies deps;
    auto cli = NewCLI(&deps);
    deps.cli_input->clear();
    deps.cli_input->str("not_a_valid_cmd\nexit");
    cli->env->setenv("PWD", "/clearly/not/the/home/path");

    assert(RunCLI(cli.get()) == 0);
    std::cout << "CLIDoesntExitOnError passed!" << std::endl;
}

void CLITests::CLIBatchTest() {
    CLIDependencies deps;
    auto cli = NewCLI(&deps);
    std::istringstream input("exit");

    assert(RunCLI(cli.get(), input) == 0);
    assert(deps.cli_output->str().find("Exiting Aggie Shell by Solomon Blount...") != std::string::npos);
    assert(deps.cli_error->str().empty());
    std::cout << "CLIBatchTest passed!" << std::endl;
}

void CLITests::CLIBatchMultilineTest() {
    CLIDependencies deps;
    auto cli = NewCLI(&deps);
    std::istringstream input("cd /ligma \n exit");

    assert(RunCLI(cli.get(), input) == 0);
    assert(deps.env->getenv("PWD") == "/ligma");
    assert(deps.cli_output->str().find("Exiting Aggie Shell by Solomon Blount...") != std::string::npos);
    assert(deps.cli_error->str().empty());
    std::cout << "CLIBatchMultilineTest passed!" << std::endl;
}

/// @brief Executes all CLI tests.
void CLITests::ExecuteTests() {
    CLITest();
    CLIHomeCursorTest();
    CLINonHomeCursorTest();
    CLIDoesntExitOnError();
    CLIBatchTest();
    CLIBatchMultilineTest();
}