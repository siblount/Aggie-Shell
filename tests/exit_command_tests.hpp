#include <memory>

#include "../cli.fwd.hpp"
#include "util/cliutil.hpp"

namespace ExitCommandTests {
    std::shared_ptr<CLI> NewCLI(CLIDependencies* deps);
    void ExitCommandTest();
    void ExitCommandNoArgsTest();
    void ExitCommandTooManyArgsTest();
    void ExecuteTests();
}