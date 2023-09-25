#include <memory>

#include "util/cliutil.hpp"

namespace CDCommandTests {
    std::shared_ptr<CLI> NewCLI(CLIDependencies* deps);
    void CDCommandTest();
    void CDCommandValidPathTest();
    void CDCommandNoArgsTest();
    void CDCommandTooManyArgsTest();
    void CDCommandBadPathTest(); 
    void ExecuteTests();
}