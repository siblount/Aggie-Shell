#include <thread>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <vector>
#include <sstream>

#include "external_command.hpp"
#include "../cli.hpp"

ExternalCommand::ExternalCommand(CLI* cli, std::vector<std::string> args, std::istream* __stdin, std::ostream* __stderr, std::ostream* __stdout) 
    : Command(cli, args, __stdin, __stderr, __stdout) {}

struct Pipe {
    int fd[2];
    Pipe() { 
        if (pipe(fd) == -1) throw std::runtime_error("Failed to create a pipe");
    }
    inline int GetReadPipe() { return fd[0]; }
    inline int GetWritePipe() { return fd[1]; }
    ~Pipe() {
        close(fd[0]);
        close(fd[1]);
    }
};

int ExternalCommand::Execute() {
    if (args.empty()) {
        throw std::runtime_error("Internal error: need atleast one argument to execute external command.");
    }
    // Create a pipe for the child process to write to.
    Pipe pipe;

    // Create a copy of the stdout since we will override it later.
    int stdout_copy = dup(STDOUT_FILENO);

    // Create a child process.
    pid_t pid = fork();

    // If we are in the child process.
    if (pid == 0) {
        // Close the read end of the pipe.
        close(pipe.GetReadPipe());

        // Redirect stdout to the write end of the pipe.
        dup2(pipe.GetWritePipe(), STDOUT_FILENO);

        // Prepare an array for execvp since it requires a null-terminated array.
        auto arr = std::make_unique<char*[]>(args.size() + 1);
        for (int i = 0; i < args.size(); i++) {
            arr[i] = (char*)args[i].c_str();
        }

        // End the array with a null pointer.
        arr[args.size()] = nullptr;

        // Execute the program and exit with the exit code of the program.
        exit(execvp(args[0].c_str(), arr.get()));

    }

    // If we are in the parent process.
    else {
        // Close the write end of the pipe.
        close(pipe.GetWritePipe());

        // Redirect stdout to the pipe.
        dup2(pipe.GetReadPipe(), STDOUT_FILENO);

        // Wait for the child process to finish.
        int status;
        waitpid(pid, &status, 0);

        // Restore stdout.
        dup2(stdout_copy, STDOUT_FILENO);
        
        // Relay the output from the child process to the standard output.
        char buffer[1024];
        ssize_t nread;
        while ((nread = read(pipe.GetReadPipe(), buffer, sizeof(buffer))) != 0) {
            *standardOutput << std::string(buffer, nread);
        }
        
        // Close the pipe.
        close(pipe.GetReadPipe());

        // Return the exit code of the child process.
        return status;
    }
}