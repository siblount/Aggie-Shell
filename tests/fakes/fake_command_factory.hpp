#include "../../command_factory.hpp"
#include "unordered_map"
class FakeCommandFactory : public CommandFactory {
    public:
        std::unordered_map<std::string, Command*> commands;
        FakeCommandFactory(CLI& cli);
        /// @brief Simply returns the command from the commands map.
        Command& GetCommand(std::string input, std::vector<std::string> args) override;
        /// @brief Simply returns the command from the commands map.
        Command& GetCommand(std::string input, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stderr, std::ostream* __stdout) override;
};