#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <cassert>

#include "../cli.hpp"
#include "../environment.hpp"
#include "util/cliutil.hpp"
#include "../command_factory.hpp"
#include "fakes/fake_command_factory.hpp"
#include "../commands/command.hpp"
#include "../commands/exit_command.hpp"
#include "../commands/path_command.hpp"
#include "../commands/cd_command.hpp"
#include "../commands/nothing_command.hpp"
#include "command_parser_tests.hpp"

std::shared_ptr<CLI> CommandParserTests::NewCLI(CLIDependencies* deps) {
    auto cli = ::NewCLI(deps);
    FakeCommandFactory factory{*cli};
    cli->commandFactory = &factory;
    return cli;
}

void CommandParserTests::CommandParserTest() {
    auto deps = new CLIDependencies{};
    auto cli = CommandParserTests::NewCLI(deps);

    try {
        CommandParser{cli->commandFactory};
    } catch (...) {
        std::cout << "CommandParserTest failed!" << std::endl;
        return;
    }
    
    std::cout << "CommandParserTest passed!" << std::endl;
}

void CommandParserTests::CommandParserBuiltinTests() {
    auto deps = new CLIDependencies{};
    auto cli = CommandParserTests::NewCLI(deps);
    cli->commandFactory = new CommandFactory{*cli};

    try {
        CommandParser parser{cli->commandFactory};
        assert(typeid(parser.Parse("exit")) == typeid(ExitCommand));
        assert(typeid(parser.Parse("cd")) == typeid(CDCommand));
        assert(typeid(parser.Parse("path")) == typeid(PathCommand));
    } catch (...) {
        std::cout << "CommandParserBuiltinTests failed!" << std::endl;
        return;
    }

    std::cout << "CommandParserBuiltinTests passed!" << std::endl;
}

void CommandParserTests::CommandParserCmdWithArgsTest() {
    auto deps = new CLIDependencies{};
    auto cli = CommandParserTests::NewCLI(deps);
    cli->commandFactory = new CommandFactory{*cli};

    try {
        CommandParser parser{cli->commandFactory};
        auto& cmd = parser.Parse("cd /home hi hello good_bye");
        assert(typeid(cmd) == typeid(CDCommand));
        assert(cmd.args.size() == 4);
        assert(cmd.args[0] == "/home");
        assert(cmd.args[1] == "hi");
        assert(cmd.args[2] == "hello");
        assert(cmd.args[3] == "good_bye");
    } catch (...) {
        std::cout << "CommandParserCmdWithArgsTest failed!" << std::endl;
        return;
    }

    std::cout << "CommandParserCmdWithArgsTest passed!" << std::endl;
}

void CommandParserTests::CommandParserTrailingWhitespaceTest() {
    auto deps = new CLIDependencies{};
    auto cli = CommandParserTests::NewCLI(deps);
    cli->commandFactory = new CommandFactory{*cli};

    try {
        CommandParser parser{cli->commandFactory};
        auto& cmd = parser.Parse("cd /home ");
        assert(typeid(cmd) == typeid(CDCommand));
        assert(cmd.args.size() == 1);
        assert(cmd.args[0] == "/home");
    } catch (...) {
        std::cout << "CommandParserTrailingWhitespaceTest failed!" << std::endl;
        return;
    }

    std::cout << "CommandParserTrailingWhitespaceTest passed!" << std::endl;
}

void CommandParserTests::CommandParserLeadingWhitespaceTest() {
    auto deps = new CLIDependencies{};
    auto cli = CommandParserTests::NewCLI(deps);
    cli->commandFactory = new CommandFactory{*cli};

    try {
        CommandParser parser{cli->commandFactory};
        auto& cmd = parser.Parse(" cd /home");
        assert(typeid(cmd) == typeid(CDCommand));
        assert(cmd.args.size() == 1);
        assert(cmd.args[0] == "/home");
    } catch (...) {
        std::cout << "CommandParserLeadingWhitespaceTest failed!" << std::endl;
        return;
    }

    std::cout << "CommandParserLeadingWhitespaceTest passed!" << std::endl;
}

void CommandParserTests::CommandParserEmptyStringTest() {
    auto deps = new CLIDependencies{};
    auto cli = CommandParserTests::NewCLI(deps);
    cli->commandFactory = new CommandFactory{*cli};

    try {
        CommandParser parser{cli->commandFactory};
        auto& cmd = parser.Parse("                  ");
        assert(typeid(cmd) == typeid(NothingCommand));
        cmd = parser.Parse("");
        assert(typeid(cmd) == typeid(NothingCommand));
    } catch (...) {
        std::cout << "CommandParserEmptyStringTest failed!" << std::endl;
        return;
    }

    std::cout << "CommandParserEmptyStringTest passed!" << std::endl;
}

void CommandParserTests::CommandParserWithQuotesTest() {
    auto deps = new CLIDependencies{};
    auto cli = CommandParserTests::NewCLI(deps);
    cli->commandFactory = new CommandFactory{*cli};

    try {
        CommandParser parser{cli->commandFactory};
        auto& cmd = parser.Parse("cd \"hello world\"");
        assert(typeid(cmd) == typeid(CDCommand));
        assert(cmd.args.size() == 1);
        assert(cmd.args[0] == "hello world");
    } catch (...) {
        std::cout << "CommandParserWithQuotesTest failed!" << std::endl;
        return;
    }

    std::cout << "CommandParserWithQuotesTest passed!" << std::endl;
}

void CommandParserTests::CommandParserWithNestedQuotesTest() {
    auto deps = new CLIDependencies{};
    auto cli = CommandParserTests::NewCLI(deps);
    cli->commandFactory = new CommandFactory{*cli};

    try {
        CommandParser parser{cli->commandFactory};
        auto& cmd = parser.Parse("cd \"hello \"world\"\"");
        assert(typeid(cmd) == typeid(CDCommand));
        assert(cmd.args.size() == 1);
        assert(cmd.args[0] == "hello \"world\"");
    } catch (...) {
        std::cout << "CommandParserWithNestedQuotesTest failed!" << std::endl;
        return;
    }

    std::cout << "CommandParserWithNestedQuotesTest passed!" << std::endl;
}

void CommandParserTests::CommandParserWithUnfinishedQuotesTest() {
    auto deps = new CLIDependencies{};
    auto cli = CommandParserTests::NewCLI(deps);
    cli->commandFactory = new CommandFactory{*cli};

    try {
        CommandParser parser{cli->commandFactory};
        auto& cmd = parser.Parse("cd \"hello world");
        assert(typeid(cmd) == typeid(CDCommand));
        assert(cmd.args.size() == 2);
        assert(cmd.args[0] == "\"hello");
        assert(cmd.args[1] == "world");

    } catch (...) {
        std::cout << "CommandParserWithUnfinishedQuotesTest failed!" << std::endl;
        return;
    }

    std::cout << "CommandParserWithUnfinishedQuotesTest passed!" << std::endl;
}

void CommandParserTests::ExecuteTests() {
    CommandParserTest();
    CommandParserBuiltinTests();
    CommandParserCmdWithArgsTest();
    CommandParserTrailingWhitespaceTest();
    CommandParserLeadingWhitespaceTest();
    CommandParserEmptyStringTest();
    CommandParserWithQuotesTest();
    CommandParserWithNestedQuotesTest();
    CommandParserWithUnfinishedQuotesTest();
}