#include "instruction.h"
#include <string>

// Desc: Class constructor, takes in name, duration of burst, and instruction arival time
// Auth: Lang Towl
// Date: 11/7/2024
Instruction::Instruction(std::string& name, int burst_duration, int arival_time) {
    this->name = name;
    this->burst_duration = burst_duration;
    this->arival_time = arival_time;
}

// Desc: Getter function for name
// Auth: Lang Towl
// Date: 11/7/2024
std::string Instruction::get_name() const {
    return this->name;
}

// Desc: Getter function for burst duration
// Auth: Lang Towl
// Date: 11/7/2024
int Instruction::get_burst_duration() const {
    return this->burst_duration;
}

// Desc: Getter function for arival time
// Auth: Lang Towl
// Date: 11/7/2024
int Instruction::get_arival_time() const {
    return this->arival_time;
}

// Desc: Returns sorted array based on arival time
// Auth: Lang Towl
// Date: 11/7/2024
std::vector<Instruction> sort_based_on_arival(const std::vector<Instruction>& instructions) {
    // Make temporary copy of array to be returned later
    std::vector<Instruction> temp_instructions = instructions;

    // Count the number of instructions in vector
    int n = temp_instructions.size();

    // Bubble sort algorithm
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (temp_instructions[j].get_arival_time() > temp_instructions[j + 1].get_arival_time()) {
                std::swap(temp_instructions[j], temp_instructions[j + 1]);
            }
        }
    }

    // Return sorted vector
    return temp_instructions;
}

// Desc: Print out shedule graph for FIFO
// Auth: Lang Towl
// Date: 11/7/2024
void print_fifo(const std::vector<Instruction>& instructions) {
    // Count number of instructions in vector
    int n = instructions.size();

    // Vector to store arrival time offset
    std::vector<int> arrival_time_offset;

    for (int i = 1; i < n; i++) {
        arrival_time_offset.push_back(instructions[i].get_arival_time());
    }

    arrival_time_offset.push_back(0);

    // Vector to store wait times for each instruction
    std::vector<int> wait_times;
    wait_times.push_back(0);

    // Backfill wait times
    for (int i = 0; i < n - 1; i++) {
        int temp = 0;
        for (int j = i; j >= 0; j--) {
            temp += (instructions[j].get_burst_duration());
        }
        wait_times.push_back(temp - arrival_time_offset[i]);
    }

    // Print graph
    for (int i = 0; i < n; i++) {
        std::cout << i + 1 << " > ";

        // Print blank spaces to simulate arival time
        for (int j = 0; j < instructions[i].get_arival_time(); j++) {
            std::cout << " ";
        }
            
        // Print wait time
        for (int j = 0; j < wait_times[i]; j++) {
            std::cout << "_";
        }

        // Print burst time
        for (int j = 0; j < instructions[i].get_burst_duration(); j++) {
            std::cout << "#";
        }

        std::cout<< std::endl;
    }
}

// Desc: Print out shedule graph for FIFO
// Auth: Lang Towl
// Date: 11/7/2024
void print_sjf(const std::vector<Instruction>& instructions) {
    // Count number of instructions in vector
    int n = instructions.size();

    // ready queue to store instructions that are ready to be executed
    std::vector<Instruction> ready_queue;

    // Scheduler graph
    std::vector<std::string> graph;

    // Manually add first instruction to ready queue and open graph
    ready_queue.push_back(instructions[0]);
    graph.push_back("");

    // Counter to track number of executions
    int counter = 0;

    // Counter to track instructions that have been added to the ready queue and the current instruction
    int current_instruction = 0;
    int next_instruction = 1;

    while (ready_queue.empty() != true) {
        // Check to see if new instruction is ready
        if (instructions[next_instruction].get_arival_time() == counter) {
            ready_queue.push_back(instructions[next_instruction]);
            next_instruction++;
            graph.push_back("");
        }

        graph[current_instruction] += "#";
        ready_queue.erase(ready_queue.begin() + 0);

        counter++;
    }


    // Print out graph
    for (int i = 0 ; i < graph.size(); i++) {
        std::cout << graph[i] << std::endl;
    }
    /*
    - Make vector to store initial instruction
    - Start executing that instruction
    - after each execution, check to see if the next instruction has arrive
    - if it has, add it to vector
    - check to see if new instruction has a shorter job then current instruction
    - if it does, start executing it
    - check to see if next instruciton is in, and if current instruction is longer then
    */
}

// Desc: Print out shedule graph for RR
// Auth: Lang Towl
// Date: 11/7/2024
void print_rr(const std::vector<Instruction>& instructions) {
    // Count number of instructions in vector
    int n = instructions.size();

    // Vector to store remaining burst times
    std::vector<int> remaining_bursts;

    for (int i = 0; i < n; i++) {
        remaining_bursts.push_back(instructions[i].get_burst_duration());
    }

    // Print graph
    int iterations = 0;
    for (int i = 0; i < n; i++) {
        std::cout << i + 1 << " > ";

        // While loop prints # when its programs 'turn' and _ otherwise
        int counter = 0;
        while (true) {
            if (counter > (n - 1)) {
                counter = 0;
            }

            if (iterations >= instructions[i].get_arival_time()) {
                // Do nothing
            } else {
                iterations++;
                std::cout << " ";
                continue;
            }

            if (counter == i) {
                std::cout << "#";

                counter++;

                if (remaining_bursts[i] != 1) {
                    remaining_bursts[i]--;
                } else {
                    break;
                }
            } else {
                std::cout << "_";
                counter++;
            }
        }

        iterations++;
        std::cout << std::endl;
    } 
}