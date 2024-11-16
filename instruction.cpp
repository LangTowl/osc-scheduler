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

// Desc: Update arrival time by passed amount
// Auth: Lang Towl
// Date: 11/14/2024
void Instruction::update_arrival_time(int amount) {
    this->arival_time += amount;
}

// Desc: Returns sorted array based on arival time
// Auth: Lang Towl
// Date: 11/7/2024
// Corrected function signature
std::vector<Instruction> sort_based_on_arival(const std::vector<Instruction>& instructions) {
    // Make a temporary copy of the vector to be sorted and returned
    std::vector<Instruction> temp_instructions = instructions;

    // Bubble sort algorithm with duplicate handling
    int n = temp_instructions.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            // Swap instructions if one is bigger then the other
            if (temp_instructions[j].get_arival_time() > temp_instructions[j + 1].get_arival_time()) {
                std::swap(temp_instructions[j], temp_instructions[j + 1]);
            }
        }
    }

    // Return the sorted and adjusted vector
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
    const int n = instructions.size();  // Number of instructions to execute
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

    // Loop to run until all bursts have been depleated 
    while (remaining_bursts != 0) {
        // Check to see if new instruction has arrived
        for (int i = next_instruction; i < n; i++) {
            if (instructions[i].get_arival_time() == step) {
                ready_queue.push_back(instructions[i]);
            } else {
                next_instruction = i;
                break;
            }
        }

        // Determine index of shortest remianing bursts
        int current_instruction_index = -1;
        for (int i = 0; i < ready_queue.size(); i++) {
            // Find shortest remaining instruction, skipping completed instructions
            if ((current_instruction_index == -1 || ready_queue[i].get_burst_duration() < ready_queue[current_instruction_index].get_burst_duration() || ready_queue[i].get_burst_duration() == ready_queue[current_instruction_index].get_burst_duration()) && ready_queue[i].get_burst_duration() != 0) {
                current_instruction_index = i;
            }
        }

        // Fill graph based on current instruction
        if (current_instruction_index != -1) {
            for (int i = 0; i < n; i++) {
                // Prints out either '_' or '#' for instructions in ready queue, otherwise ' ' for instructions that have not arrived yet
                if (i < ready_queue.size()) {
                    // Instruction is executing
                    if (i == current_instruction_index && ready_queue[current_instruction_index].get_burst_duration() != 0) {
                        graph[i] += "#";
                        ready_queue[current_instruction_index].reduce_burst_duration(1);
                        remaining_bursts--;
                    } else {
                        // Instruction is either waiting or done
                        if (ready_queue[i].get_burst_duration() == 0) {
                            continue;
                        } else {
                            graph[i] += "_";
                        }
                    }
                } else {
                    // Instruction has not arrived yet
                    graph[i] += " ";
                }
            }
        }

        // Go to next step in execution
        step++;
    }

    // Show graph
    for (int i = 0; i < graph.size(); i++) {
        std::cout << graph[i] << std::endl;
    }

    std::cout << std::endl;
}

// Desc: Print out shedule graph for RR
// Auth: Lang Towl
// Date: 11/7/2024
void print_rr(const std::vector<Instruction>& instructions) {
    // Scheduling parameters
    const int n = instructions.size();                  // Number of instructions to execute
    int next_instruction = 0;                           // Next instruction to arrive
    int step = 0;                                       // Tracks current step of execution
    int row = 0;                                        // Tracks which row should be executed
    int instructions_to_execute = instructions.size();  // Tracks remaining instructions that need to be executed

    // Compute total burst to be executed
    int remaining_bursts = 0;

    for (int i = 0; i < n; i++) {
        remaining_bursts += instructions[i].get_burst_duration();
    }

    // Vector to store instructions that are ready to be printed
    std::vector<Instruction> ready_queue;

    // Vector to store arrival buffers for instructions that arrive at the same time
    std::vector<std::string> buffer;

    // Make buffer empty
    for (int i = 0; i < n; i++) {
        buffer.push_back("");
    }

    // Add a wait in case of two instructions arruving at the same time
    for (int i = 0; i < n; i++) {
        if (i != n -1 && instructions[i].get_arival_time() == instructions[i + 1].get_arival_time()) {
            buffer[i + 1] += "_";
        }
    }

    // Create empty graph
    std::vector<std::string> graph;

    for (int i = 0; i < n; i++) {
        graph.push_back(std::to_string(i + 1) + " > ");
    }  

    // Loop to run until all bursts have been depleated 
    while (remaining_bursts != 0) {
        // Cap row at length of graph
        if (row == graph.size()) {
            row = 0;
        }

        // Check to see if new instruction has arrived (handles duplicates)
        for (int i = next_instruction; i < n; i++) {
            if (instructions[i].get_arival_time() == step) {
                ready_queue.push_back(instructions[i]);
                row = 0;
            } else {
                next_instruction = i;
                break;
            }
        }

        // Fill graph
        for (int i = 0; i < graph.size(); i++) {
            // For the instrctions that have arrived
            if (i < ready_queue.size()) {
                if (row == i && ready_queue[i].get_burst_duration() != 0) {
                    // Consume and clear buffer, if there is one
                    graph[i] += buffer[i];
                    buffer[i] = "";

                    // Execute and consume a burst 
                    graph[i] += "#";
                    ready_queue[i].reduce_burst_duration(1);
                    remaining_bursts -= 1;

                    // Wait however many instructions still remain
                    if (ready_queue[i].get_burst_duration() != 0) {
                        for (int j = 0; j < instructions_to_execute - 1; j++) {
                            graph[i] += "_";
                        }
                    }

                    // Remove instruction if all bursts have been consumed
                    if (ready_queue[i].get_burst_duration() == 0) {
                        instructions_to_execute--;
                    }
                }
            } else {
                // For the instructions that have yet to arrive
                graph[i] += " ";
            }
        }

        // Update parameters
        step++;
        row++;
    }

    // Show graph
    for (int i = 0; i < graph.size(); i++) {
        std::cout << graph[i] << std::endl;
    }
}

// Desc: Compute performance evaluators for FIFO
// Auth: Lang Towl
// Date: 11/15/2024
void calculate_fifo(const std::vector<Instruction>& instructions) {
    double total_waiting_time = 0.0;
    double total_response_time = 0.0;
    double time_to_complete = 0.0;
    double current_time = 0.0; 

    for (int i = 0; i < instructions.size(); i++) {
        // Adjust current time to reflect the arrival of the next instruction.
        if (current_time < instructions[i].get_arival_time()) {
            current_time = instructions[i].get_arival_time();
        }

        // Update waiting time, response time, & current time
        total_waiting_time += current_time - instructions[i].get_arival_time();
        total_response_time += current_time - instructions[i].get_arival_time();
        current_time += instructions[i].get_burst_duration();
    }

    time_to_complete = current_time;

    // COmpute throughput
    double throughput = instructions.size() / (time_to_complete / 10.0);

    // Print the results.
    std::cout << "Average Waiting Time: " << total_waiting_time / instructions.size() << std::endl;
    std::cout << "Average Response Time: " << total_response_time / instructions.size() << std::endl;
    std::cout << "Throughput over 10 cycles: " << throughput << std::endl;
}

// Desc: Compute performance evaluators for SJF
// Auth: Lang Towl
// Date: 11/15/2024
void calculate_sjf(const std::vector<Instruction>& instructions) {
    double total_waiting_time = 0.0;
    double total_response_time = 0.0;
    double total_time_to_complete = 0.0;
    int current_time = 0;
    int completed_count = 0;

    std::vector<bool> completed(instructions.size(), false); 

    while (completed_count < instructions.size()) {
        // Find the shortest job available at the current time
        int shortest_index = -1;
        for (int i = 0; i < instructions.size(); ++i) {
            if (!completed[i] && instructions[i].get_arival_time() <= current_time) {
                if (shortest_index == -1 || 
                    instructions[i].get_burst_duration() < instructions[shortest_index].get_burst_duration()) {
                    shortest_index = i;
                }
            }
        }

        if (shortest_index == -1) {
            // If no process is ready, advance time
            current_time++;
            continue;
        }

        // Process the selected instruction
        const Instruction& inst = instructions[shortest_index];
        int wait_time = current_time - inst.get_arival_time();
        int response_time = wait_time; // Since it starts immediately after waiting

        // Update totals
        total_waiting_time += wait_time;
        total_response_time += response_time;
        current_time += inst.get_burst_duration(); // Execute the instruction
        total_time_to_complete = current_time;
        completed[shortest_index] = true;
        completed_count++;
    }

    // Compute throughput
    double throughput = (double)completed_count / total_time_to_complete * 10.0;

    // Print the results
    std::cout << "Average Waiting Time: " << total_waiting_time / instructions.size() << std::endl;
    std::cout << "Average Response Time: " << total_response_time / instructions.size() << std::endl;
    std::cout << "Throughput over 10 cycles: " << throughput << std::endl;
}

// Desc: Compute performance evaluators for Round Robin
// Auth: Lang Towl
// Date: 11/15/2024
void calculate_rr(const std::vector<Instruction>& instructions) {
    int time_quantum = 1;
    double total_waiting_time = 0.0;
    double total_response_time = 0.0;
    double total_time_to_complete = 0.0;
    int current_time = 0;
    int completed_count = 0;

    std::vector<int> remaining_burst(instructions.size());
    std::vector<int> first_response_time(instructions.size(), -1);
    std::vector<int> arrival_time(instructions.size());
    std::vector<bool> completed(instructions.size(), false);

    // Update remaining bursts and arrival times
    for (int i = 0; i < instructions.size(); ++i) {
        remaining_burst[i] = instructions[i].get_burst_duration();
        arrival_time[i] = instructions[i].get_arival_time();
    }

    // Queue to track ready processes
    std::queue<int> ready_queue;
    int index = 0;

    // Add processes to the ready queue as they arrive
    while (completed_count < instructions.size()) {
        while (index < instructions.size() && instructions[index].get_arival_time() <= current_time) {
            ready_queue.push(index);
            index++;
        }

        // Proceed to next cycle if ready queue is empty
        if (ready_queue.empty()) {
            current_time++;
            continue;
        }

        // Process the next instruction in the queue
        int current_instruction = ready_queue.front();
        ready_queue.pop();

        // Update response time if this is the first execution of the process
        if (first_response_time[current_instruction] == -1) {
            first_response_time[current_instruction] = current_time - arrival_time[current_instruction];
        }

        // Compute bust time and update current time, then decrememnt remaining bursts to execute
        int burst_time = std::min(time_quantum, remaining_burst[current_instruction]);
        current_time += burst_time;
        remaining_burst[current_instruction] -= burst_time;

        // Add newly arrived processes during this time slice to the queue
        while (index < instructions.size() && instructions[index].get_arival_time() <= current_time) {
            ready_queue.push(index);
            index++;
        }

        if (remaining_burst[current_instruction] > 0) {
            // Process is not completed, re-add to the queue
            ready_queue.push(current_instruction);
        } else {
            // Process is completed
            completed[current_instruction] = true;
            completed_count++;

            int finish_time = current_time;
            int waiting_time = finish_time - arrival_time[current_instruction] - instructions[current_instruction].get_burst_duration();
            total_waiting_time += waiting_time;

            total_response_time += first_response_time[current_instruction];
        }
    }
    
    total_time_to_complete = current_time;

    // Compute throughput
    double throughput = (double)completed_count / total_time_to_complete * 10.0;

    // Print the results
    std::cout << "Average Waiting Time: " << total_waiting_time / instructions.size() << std::endl;
    std::cout << "Average Response Time: " << total_response_time / instructions.size() << std::endl;
    std::cout << "Throughput over 10 cycles: " << throughput << std::endl;
}
