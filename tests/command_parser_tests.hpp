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
    void CommandParserWithQuotesTest();
    void CommandParserWithNestedQuotesTest();
    void CommandParserWithUnfinishedQuotesTest();
    void CommandParserRedirectTest();
    void CommandParserRedirectWithQuotesTest();
    void CommandParserRedirectWithNestedQuotesTest();
    void CommandParserRedirectWithSingleQuotesTest();
    void CommandParserDoubleRedirectTest();
    void ExecuteTests();
}