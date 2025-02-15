#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

#include "cse4733/ForkException.hpp"
#include "cse4733/ProcessManager.hpp"
#include "cse4733/SignalHandlers.hpp"
#include "cse4733/SleepException.hpp"
#include "cse4733/SystemCalls.hpp"
#include "cse4733/WaitPidException.hpp"

namespace cse4733
{

    ProcessManager::ProcessManager()
        : m_counter(0),
          m_shouldTerminate(false),
          m_sleepValue(1)
    {
    }

    void ProcessManager::incrementCounter()
    {
        m_counter++;
    }

    void ProcessManager::incrementSleepValue()
    {
        m_sleepValue++;
    }

    void ProcessManager::decrementSleepValue()
    {
        m_sleepValue--;
    }

    int ProcessManager::getSleepValue() const
    {
        return m_sleepValue;
    }

    bool ProcessManager::ShouldContinueRunning() const
    {
        return !m_shouldTerminate &&
               m_counter >= 0 &&
               m_counter < 60;
    }

    void ProcessManager::Run()
    {
        /*
        TODO: Implement the Run method.
        1. Create a child process using the fork system call.
        2. If the fork failed, throw a ForkException with the message "Error occurred during fork."
        3. If the fork returned a negative value, throw a ForkException with the message "Failed to fork a child process."
        4. If the fork returned 0, this is the child process:
        4.1. Register signal handlers for SIGINT, SIGUSR1, and SIGALRM.
        4.2. Output the child process ID and a message indicating that the program is running.
        4.3. While the process should continue running:
        4.3.1. Sleep for the specified duration.
        4.3.2. Output the child process ID and sleep duration.
        4.3.3. Increment the counter.
        5. If the fork returned a positive value, this is the parent process:
        5.1. Wait for the child process to terminate.
        5.2. If the wait failed, throw a WaitPidException with the message "Error occurred during waitpid."
        5.3. If the child process terminated normally, output the exit status.
        5.4. If the child process was terminated by a signal, output the signal number.
        */

        //Fork a child process
        std::optional<pid_t> pid = SystemCalls::Fork();

        if(!pid.has_value())
            throw ForkException("Error occurred during fork.");

        //Checks if fork failed and throws exception if it did
        if(pid.value() < 0)
            throw ForkException("Failed to fork a child process.");

        if(pid.value() == 0) {
            //Child process

            //Register signal handlers for SIGINT, SIGUSR1, and SIGALRM
            signal(SIGINT, handleSIGINT);
            signal(SIGUSR1, handleSIGUSR1);
            signal(SIGALRM, handleSIGALRM);
            

            //Output the child process ID and a message indicating that the program is running
            std::cout << "Child process ID: " << SystemCalls::GetPid() << std::endl;

            //While the process should continue running
            while(ShouldContinueRunning()) {
                
                //Sleep for the specified duration
                try {
                    SystemCalls::Sleep(m_sleepValue);
                }
                catch(const SleepException &e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                    exit(EXIT_FAILURE);
                }

                //Output the child process ID and sleep duration
                std::cout << "Child process ID: " << SystemCalls::GetPid() << " slept for " << m_sleepValue << " seconds." << std::endl;

                //Increment the counter
                incrementCounter();
            }
        }
        else {
            //Parent process
            //Wait for child process to terminate
            std::optional<int> status = SystemCalls::WaitPid(pid.value(), nullptr, 0);

            //Check if wait failed
            if(!status.has_value())
                throw WaitPidException("Error occurred during waitpid.");

            //Check if child process terminated normally
            if(WIFEXITED(status.value()))
                std::cout << "Child process exited with status " << WEXITSTATUS(status.value()) << std::endl;

            //Check if child process was terminated by a signal
            if(WIFSIGNALED(status.value()))
                std::cout << "Child process was terminated by signal " << WTERMSIG(status.value()) << std::endl;
        }
    }

} // namespace cse4733