#include "cli_options.hpp"

CLIOptions::CLIOptions() : env(nullptr), command_factory(nullptr), standard_input(nullptr), standard_error(nullptr), standard_output(nullptr) {}

CLIOptions::CLIOptions(Environment* env, CommandFactory* command_factory, std::istream* standard_input, std::ostream* standard_error, std::ostream* standard_output) : 
    env(env), command_factory(command_factory), standard_input(standard_input), standard_error(standard_error), standard_output(standard_output) {}