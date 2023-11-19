#pragma once
#include <memory>
#include "../cli.fwd.hpp"

namespace CLITests {
    void ExecuteTests();
    void CLINonHomeCursorTest();
    void CLIHomeCursorTest();
    void CLIDoesntExitOnError();
    void CLITest();
    void CLIBatchTest();
    void CLIBatchMultilineTest();
}