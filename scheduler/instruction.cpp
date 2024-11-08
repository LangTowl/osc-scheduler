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

// Desc: Returns sorted array in case of FIFO and RR 
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

// Desc: Returns sorted array in case of SJF
// Auth: Lang Towl
// Date: 11/7/2024
std::vector<Instruction> sort_based_on_burst(const std::vector<Instruction>& instructions) {
    // Make temporary copy of array to be returned later
    std::vector<Instruction> temp_instructions = instructions;

    // Count the number of instructions in vector
    int n = temp_instructions.size();

    // Bubble sort algorithm
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (temp_instructions[j].get_burst_duration() > temp_instructions[j + 1].get_burst_duration()) {
                std::swap(temp_instructions[j], temp_instructions[j + 1]);
            }
        }
    }

    // Return sorted vector
    return temp_instructions;
}

// Desc: Print out shedule graph for FIFO and SJF
// Auth: Lang Towl
// Date: 11/7/2024
void print_fifo_and_sjf(const std::vector<Instruction>& instructions) {
    // Count number of instructions in vector
    int n = instructions.size();

    // Vector to store wait times for each instruction
    std::vector<int> wait_times;

    // Manually load first wait time
    wait_times.push_back(0);

    for (int i = 0; i < n; i++) {
        int temp = 0;
        for (int j = i; j >= 0; j--) {
            temp += instructions[j].get_burst_duration();
        }
        wait_times.push_back(temp);
    }

    std::cout << std::endl;

    // Print graph
    for (int i = 0; i < n; i++) {
        std::cout << i + 1 << " > ";

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

// Desc: Helper function for print_rr()
// Auth: Lang Towl
// Date: 11/7/2024
bool is_vector_empty(const std::vector<int>& vector) {
    int sum;

    // Aggregate vector values
    for (int i = 0; i < vector.size(); i++) {
        sum += vector[i];
    }

    // If sum == 0, vector is empty
    if (sum == 0) {
        return true;
    } 

    // Otherwise, not empty
    return false;
}

// Desc: Print out shedule graph for FIFO and SJF
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
    for (int i = 0; i < n; i++) {
        std::cout << i + 1 << " > ";

        // While loop prints # when its programs 'turn' and _ otherwise
        int counter = 0;
        while (true) {
            if (counter > 3) {
                counter = 0;
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

        std::cout << std::endl;
    } 
}