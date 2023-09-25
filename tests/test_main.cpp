#include "cli_tests.hpp"
#include "cd_command_tests.hpp"
#include "exit_command_tests.hpp"
#include "path_command_tests.hpp"
#include "command_parser_tests.hpp"

int main() {
    CLITests::ExecuteTests();
    CDCommandTests::ExecuteTests();
    ExitCommandTests::ExecuteTests();
    PathCommandTests::ExecuteTests();
    CommandParserTests::ExecuteTests();
    return 0;
}