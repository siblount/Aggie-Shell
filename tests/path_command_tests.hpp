#include <memory>

#include "../cli.fwd.hpp"
#include "util/cliutil.hpp"

namespace PathCommandTests {
    std::shared_ptr<CLI> NewCLI(CLIDependencies* deps);
    void PathCommandTest();
    void PathCommandNoArgsTest();
    void PathCommandOneArgTest();
    void PathCommandMultipleArgTest();
    void ExecuteTests();
}