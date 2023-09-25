#include <iostream>
#include <string>
#include <vector>

/// @brief An abstract class representing a command to be executed.
class Command {
    public:
        /// @brief The arguments to send to the command; do not include the command name itself or dashes.
        std::vector<std::string> args;
        /// @brief The standard input stream to use for the command.
        std::ostream* standard_output;
        /// @brief The standard output stream to use for the command.
        std::istream* standard_input;
        /// @brief Creates a new command with the given arguments, standard input, and standard output.
        /// @param args The arguments to send to the command; do not include the command name itself or dashes.
        /// @param __stdin The standard input stream to use for the command. If NULL, will use default standard input.
        /// @param __stdout The standard output stream to use for the command. If NULL, will use default standard output.
        Command(std::vector<std::string> args, std::istream* __stdin, std::ostream* __stdout);
        virtual int Execute() = 0;
};