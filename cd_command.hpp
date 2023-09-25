#include "command.hpp"

class CDCommand : public Command {
    public:
        CDCommand(std::vector<std::string> args, std::istream* __stdin, std::ostream* __stdout);
        int Execute() override;
};