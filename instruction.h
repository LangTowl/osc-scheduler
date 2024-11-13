#ifndef INSTRUCTION_H
#define INSTRUCTION_H

// Neccessary libraries
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Desc: Class to represent each instrctuion from source file
// Auth: Lang Towl
// Date: 11/7/2024
class Instruction {
private:
    // Privately available class attributes
    std::string name;
    int burst_duration;
    int arival_time;
public:
    // Desc: Class constructor, takes in name, duration of burst, and instruction arival time
    // Auth: Lang Towl
    // Date: 11/7/2024
    Instruction(std::string& name, int burst_duration, int arival_time);

    // Desc: Getter function for name
    // Auth: Lang Towl
    // Date: 11/7/2024
    std::string get_name() const;

    // Desc: Getter function for burst duration
    // Auth: Lang Towl
    // Date: 11/7/2024
    int get_burst_duration() const;

    // Desc: Getter function for arival time
    // Auth: Lang Towl
    // Date: 11/7/2024
    int get_arival_time() const;
};

// Desc: Returns sorted array in case of FIFO and RR 
// Auth: Lang Towl
// Date: 11/7/2024
std::vector<Instruction> sort_based_on_arival(const std::vector<Instruction>& instructions);

// Desc: Print out shedule graph for FIFO
// Auth: Lang Towl
// Date: 11/7/2024
void print_fifo(const std::vector<Instruction>& instructions);

// Desc: Print out shedule graph for SJF
// Auth: Lang Towl
// Date: 11/7/2024
void print_sjf(const std::vector<Instruction>& instructions);

// Desc: Print out shedule graph for RR
// Auth: Lang Towl
// Date: 11/7/2024
void print_rr(const std::vector<Instruction>& instructions);

#endif