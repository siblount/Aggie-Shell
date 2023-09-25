#pragma once

#include "../command_parser.hpp"
#include "../cli.fwd.hpp"
#include "util/cliutil.hpp"

namespace CommandParserTests {
    std::shared_ptr<CLI> NewCLI(CLIDependencies* deps);
    void CommandParserTest();
    void CommandParserBuiltinTests();
    void CommandParserCmdWithArgsTest();
    void CommandParserTrailingWhitespaceTest();
    void CommandParserLeadingWhitespaceTest();
    void CommandParserEmptyStringTest();
    void ExecuteTests();
}