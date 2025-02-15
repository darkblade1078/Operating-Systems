#include "round_robin.hpp"

#include<algorithm>
#include<queue>

namespace cse4733 {

void round_robin::run(std::vector<std::shared_ptr<cse4733::IProcess>> &processes, int quantum)
    {
        // TODO:
        //  Get number of processes
        //  Fill the ready queue
        //  Loop until all processes are removed from the ready queue
        //     Get the next process from the ready queue
        //     Get the remaining time for the process
        //     Execute the process for the quantum or remaining time, whichever is smaller
        //   Update the completion time and remaining time
        //   Add back to the queue if the process still has remaining time
        //     Else set the completion time, turnaround time, and waiting time

        //our current_time variable set to 0
        int current_time = 0;

        //fill the ready queue
        std::queue<std::shared_ptr<cse4733::IProcess>> ready_queue;

        //for loop to fill the ready queue with the processes
        for (const auto& process : processes) {
            ready_queue.push(process);
        }

        //while loop that keeps running until the ready queue is empty
        while (!ready_queue.empty()) {

            //get the next process from the ready queue
            std::shared_ptr<cse4733::IProcess> process = ready_queue.front();

            //remove the process from the queue
            ready_queue.pop();

            //get the remaining time for the process
            const int remaining_time = process.get()->get_remaining_time();

            //get either quantum time or remaining time by using the min function
            const int time = std::min(quantum, remaining_time);

            //update the current time
            current_time += time;

            //update the remaining time
            process->set_remaining_time(remaining_time - time);

            //if the process still has remaining time, add it to the back of the queue (so we can go to the next process)
            if (process->get_remaining_time() > 0) {
                ready_queue.push(process);
            }
            //else set the completion time, turnaround time, and waiting time
            else {
                process->set_completion_time(current_time);
                process->set_turnaround_time(current_time - process->get_arrival_time());
                process->set_waiting_time(process->get_turnaround_time() - process->get_burst_time());
            }
        }
    }

    void round_robin::print_results(std::vector<std::shared_ptr<cse4733::IProcess>> &processes)
    {
        int total_waiting = 0;
        int total_turnaround = 0;
        int n = processes.size();

        std::cout << "Round Robin Scheduling:\n";
        std::cout << "Process ID\tCompletion Time\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n";
        for (const auto& item : processes)
        {
            std::cout << "  " << item->to_string() << std::endl;

            // Set the total turnaround time
            total_turnaround += item->get_turnaround_time();

            // Set the total waiting time
            total_waiting += item->get_waiting_time();
        }
        std::cout << "  Average Waiting Time: " << (double)total_waiting / n << std::endl;
        std::cout << "  Average Turnaround Time: " << (double)total_turnaround / n << std::endl;
    }

}

