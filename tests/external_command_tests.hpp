#include <memory>

#include "../cli.fwd.hpp"
#include "util/cliutil.hpp"

namespace ExternalCommandTests {
    std::shared_ptr<CLI> NewCLI(CLIDependencies* deps);
    void ExternalCommandTest();
    void ExternalCommandEchoTest();
    void ExecuteTests();
}