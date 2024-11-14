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

// Desc: Default Class constructor
// Auth: Lang Towl
// Date: 11/7/2024
Instruction::Instruction() {
    this->name = "null";
    this->burst_duration = 0;
    this->arival_time = 0;
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

// Desc: Decrease burst duration by 1
// Auth: Lang Towl
// Date: 11/13/2024
void Instruction::reduce_burst_duration(int amount) {
    this->burst_duration -= amount;
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
    // Scheduling parameters
    int n = instructions.size();        // Number of instructions to execute
    int next_instruction = 0;           // Next instruction to arrive
    int step = 0;                       // Tracks current step of execution  

    // Compute total burst to be executed
    int remaining_bursts = 0;

    for (int i = 0; i < n; i++) {
        remaining_bursts += instructions[i].get_burst_duration();
    }

    // Vector to store instructions that are ready to be printed
    std::vector<Instruction> ready_queue;

    // Create empty graph
    std::vector<std::string> graph;

    for (int i = 0; i < n; i++) {
        graph.push_back(std::to_string(i + 1) + " > ");
    }

    // Loop to run continuosly 
    while (remaining_bursts != 0) {
        // Check to see if new instruction has arrived
        if (instructions[next_instruction].get_arival_time() == step) {
            ready_queue.push_back(instructions[next_instruction]);
            next_instruction++;
        }

        // Determine index of shortest remianing bursts
        int current_instruction_index = -1;
        for (int i = 0; i < ready_queue.size(); i++) {
            if (current_instruction_index == -1 || ready_queue[i].get_burst_duration() < ready_queue[current_instruction_index].get_burst_duration()) {
                current_instruction_index = i;
            }
        }

        // Fill graph based on current instruction
        if (current_instruction_index != -1) {
            for (int i = 0; i < n; i++) {
                if (i <= ready_queue.size()) {
                    if (i == current_instruction_index) {
                        graph[i] += "#";
                        ready_queue[current_instruction_index].reduce_burst_duration(1);
                        remaining_bursts--;

                        if (ready_queue[current_instruction_index].get_burst_duration() <= 0) {
                            ready_queue.erase(ready_queue.begin() + current_instruction_index);
                        }
                    } else {
                        graph[i] += "_";
                    }
                } else {
                    graph[i] += " ";
                }
            }
        }

        step++;

        for (int i = 0; i < graph.size(); i++) {
            std::cout << graph[i] << std::endl;
        }

        std::cout << std::endl;
    }
}

/*
// Count number of instructions in vector
    int n = instructions.size();

    // Count total iteration, current instruction, and next instruction
    int step = 0;
    int row = 0;
    int next_instruction = 1;

    // Instruction to store currently executing instruction
    Instruction current_instruction = instructions[0];

    // Ready queue to store instructions that are ready to be executed
    std::vector<Instruction> ready_queue;

    ready_queue.push_back(instructions[0]);
    

    // Generate empty graph based on number of instructions
    std::vector<std::string> graph(n, "");

    // Code to run while ready queue is not empty and there are bursts still needing execution
    while (!ready_queue.empty() && next_instruction < n) {
        // Check to see if a new instruction has arrived
        if (instructions[next_instruction].get_arival_time() == step) {
            // Add new instruction to ready queue
            ready_queue.push_back(instructions[next_instruction]);
            next_instruction++;
        }

        // Pick shortest instruction from ready queue
        for (int i = 0; i < ready_queue.size(); i++) {
            // Replace current instruction with instruction from ready queue
            if (current_instruction.get_burst_duration() > ready_queue[i].get_burst_duration()) {
                current_instruction = ready_queue[i];
                row = i;
            }
        } 
        
        // Fill next line of graph
        for (int i = 0; i < n; i++) {
            if (i <= ready_queue.size()) {
                if (i == row) {
                    graph[row] += "#";
                    ready_queue[row].reduce_burst_duration(1);

                    // Remove instruction if its burst has been depleted
                    if (ready_queue[row].get_burst_duration() <= 0) {
                        ready_queue.erase(ready_queue.begin() + i);
                    }
                } else {
                    graph[row] += "_";
                }
            } else {
                graph[row] += " ";
            }
        }

        step++;
    }

    // Print graph
    for (int i = 0; i < graph.size(); i++) {
        std::cout << i + 1 << " > " <<  graph[i] << std::endl;
    }
*/

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