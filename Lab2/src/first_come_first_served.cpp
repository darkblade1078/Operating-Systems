#include "first_come_first_served.hpp"

#include <iostream>

namespace cse4733 {

void first_come_first_served::run(std::vector<std::shared_ptr<cse4733::IProcess>>& processes)
{
            int completion_time = 0;// TODO:
        //
        // Set 'current_time' to zero. It will keep track of the elapsed process execution times.
        // For all processes
        //   Get the burst time
        //   Set the completion time to the current time plus the burst time
        //   Set the turnaround time to the completion time minus the arrival time
        //   Set the waiting time to the turnaround time minus the burst time
        //   Add burst time to current time

    //our current_time variable set to 0
    int current_time = 0;

    //for loop to iterate through the processes
    for (const auto& process : processes) {

        //get the burst time of the process
        const int burst_time = process.get()->get_burst_time();

        //add the current_time and burst_time on top of our completion_time
        process.get()->set_completion_time(current_time + burst_time);

        //set the turnaround time to the completion time minus the arrival time
        process.get()->set_turnaround_time(process.get()->get_completion_time() - process.get()->get_arrival_time());

        //set the waiting time to the turnaround time minus the burst time
        process.get()->set_waiting_time(process.get()->get_turnaround_time() - burst_time);

        //add the burst time to the current time
        current_time += burst_time;
    }
}

void first_come_first_served::print_results(std::vector<std::shared_ptr<cse4733::IProcess>>& processes) {
    std::cout << "FCFS Scheduling:" << std::endl
              << "  Process ID\tCompletion Time\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time" << std::endl;

    int total_waiting = 0;
    int total_turnaround = 0;
    for (const auto& item : processes) {
        std::cout << "  " << item->to_string() << std::endl;
        total_waiting += item->get_waiting_time();
        total_turnaround += item->get_turnaround_time();
    }
    std::cout << "  Average waiting time (tics): " << total_waiting / processes.size() << std::endl;
    std::cout << "  Average turnaround time (tics): " << total_turnaround / processes.size() << std::endl << std::endl;
}


}

