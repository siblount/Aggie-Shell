#include "cli_tests.hpp"
#include "cd_command_tests.hpp"
#include "exit_command_tests.hpp"
#include "path_command_tests.hpp"
#include "command_parser_tests.hpp"
#include "external_command_tests.hpp"
#include "command_factory_tests.hpp"
#include "command_tests.hpp"

int main() {
    CLITests::ExecuteTests();
    CDCommandTests::ExecuteTests();
    ExitCommandTests::ExecuteTests();
    PathCommandTests::ExecuteTests();
    CommandParserTests::ExecuteTests();
    ExternalCommandTests::ExecuteTests();
    CommandFactoryTests::ExecuteTests();
    CommandTests::ExecuteTests();
    return 0;
}