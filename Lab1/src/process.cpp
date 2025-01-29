#include "process.hpp"
#include "ForkException.hpp"

#include <iostream>


namespace cse4733
{

    process::process(std::shared_ptr<ISystemCalls> systemCalls,
                     std::string path,
                     const std::vector<std::string> &args)
        : processId(-1),
          executablePath(std::move(path)),
          sysCalls(std::move(systemCalls)),
          errorMessage("(none)")
    {

        for (const auto &arg : args)
        {
            arguments.push_back(const_cast<char *>(arg.c_str()));
        }
        arguments.push_back(nullptr);
    }

    auto process::execute() -> bool
    {
        // TODO:
        // Call the system fork function to create a child process
        // IF the fork fails, display an error message and return false
        // IF the fork succeeds, check if this is the child process or the parent process
        //   IF the child:
        //     Execute the child process logic
        //     Return false to indicate that this is the child process
        //   ELSE the parent:
        //     Execute the parent process logic
        //     Return true to indicate that this is the parent process and the child process was created successfully

        // Calls fork function
        auto forkResult = sysCalls->Fork();

        // Check if the fork was successful by checking if it has a value
        if (!forkResult.has_value())
            return false;

        // Get the pid from the fork result
        pid_t result = forkResult.value();

        // Child
        if(result == 0) {
            executeChildProcess();
            return false;
        }
        // Parent
        else {
            executeParentProcess(result);
            return true;
        }

        return result;
    }

    void process::executeChildProcess()
    {
        // TODO:
        //   Print the child process ID
        //   Print the parent process ID
        //   Execute the given program with the provided arguments
        //   Should Execvp return (if it does?) then print an error message and exit

        // Print the child process ID
        std::cout << "Child: Child ID =  " << sysCalls->Getpid() << std::endl;

        // Print the parent process ID
        std::cout << "Child: Parent ID = " << sysCalls->Getppid() << std::endl;

        // Execute the given program
        auto execResult = sysCalls->Execvp(executablePath.c_str(), arguments);

        // Check if Execvp returned
        if (execResult.has_value()) {
            errorMessage = "Execvp failed";
            exit(1);
        }
    }

    void process::executeParentProcess(pid_t pid)
    {
        // TODO:
        //   Store the child process ID
        //   Print the parent process ID
        //   Print the child process ID

        // Store the child process ID
        processId = pid;

        // Print the parent process ID
        std::cout << "Parent: Parent ID = " << sysCalls->Getpid() << std::endl;

        // Print the child process ID
        std::cout << "Parent: Child ID = " << processId << std::endl;
    }

    void process::handleChildExitStatus(int status, pid_t pid)
    {
        // TODO:
        // Check if the child process terminated normally
        // IF the child process terminated normally
        //    Print a message with the child process ID with the exit status.
        // ELSE IF the child process did not terminate normally
        //    Print an error message with the child process ID

        // Check if the child process terminated normally
        if (WIFEXITED(status))
            // Print a message with the child process ID with the exit status.
            std::cout << "Child process " << pid << " terminated with exit status " << WEXITSTATUS(status) << std::endl;
        else
            // Print an error message with the child process ID
            std::cout << "Child process " << pid << " did not terminate normally" << std::endl;
    }

    auto process::wait() -> std::optional<int>
    {
        // Declare a variable to hold the status of the child process
        // Use the Waitpid system call to wait for the child process to change state (e.g., to terminate)
        // Check if the Waitpid system call succeeded
        // If the Waitpid system call failed, print an error message and return std::nullopt
        // Else if the Waitpid system call succeeded, handle the child's exit status
        // Return the exit status of the child process

        int status; // Status of the child process

        // Wait for the child process to change state
        auto waitResult = sysCalls->Waitpid(processId, &status, 0);

        // Check if the Waitpid system call succeeded
        if (!waitResult.has_value()) {
            errorMessage = "Waitpid failed";
            return std::nullopt;
        }

        // Handle the child's exit status
        handleChildExitStatus(status, waitResult.value());

        // Return the exit status of the child process
        return WEXITSTATUS(status);
    }

    auto process::get_id() const -> pid_t
    {
        return this->processId;
    }

    auto process::getErrorMessage() const -> std::string
    {
        return errorMessage;
    }

} // namespace cse4733
