#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include "command_tests.hpp"
#include "../commands/command.hpp"
#include "../commands/nothing_command.hpp"
#include "../ofstream_extended.hpp"

// Just trying out macros.
#define TRY_CATCH_FAIL(statement, message) try { statement; } catch (...) { throw std::runtime_error(message); }

void CommandTests::CommandStdDeconstructorTest() {
    std::vector<std::string> args;
    std::istream* standardInput = &std::cin;
    std::ostream* standardError = &std::cerr;
    std::ostream* standardOutput = &std::cout;
    Command* command = new NothingCommand(nullptr, args, standardInput, standardError, standardOutput);
    delete command;

    TRY_CATCH_FAIL(dynamic_cast<ofstream_extended*>(standardError), "CommandStdDeconstructorTest failed!");
    TRY_CATCH_FAIL(dynamic_cast<ofstream_extended*>(standardOutput), "CommandStdDeconstructorTest failed!");
    std::cout << "CommandStdDeconstructorTest passed!" << std::endl;
}

void CommandTests::CommandFileDeconstructorTest() {
    std::vector<std::string> args;
    ofstream_extended* fileStream = new ofstream_extended("tests/test.txt"); 
    std::unique_ptr<Command> command(new NothingCommand(nullptr, args, &std::cin, fileStream, fileStream));
    command.reset();

    if (ofstream_extended::instances.size() != 0) {
        throw std::runtime_error("CommandFileDeconstructorTest failed!");
    }
}

void CommandTests::ExecuteTests() {
    CommandStdDeconstructorTest();
    CommandFileDeconstructorTest();
}
