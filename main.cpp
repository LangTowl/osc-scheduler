#include "instruction.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// Desc: Main function
// Auth: Lang Towl
// Date: 11/6/2024
int main(){
    // Open file from current working directory
    std::ifstream file("source.txt");

    // Check if file is opened successfully
    if (!file) {
        std::cout << "File failed to open." << std::endl;
        return 1;
    }

    std::cout << "Contents of source file:" << std::endl << std::endl;

    //****************************** Parse Source File ******************************//

    // Create a vector to store all instructions in source file
    std::vector<Instruction> instructions;

    // Read each line from the file
    std::string line;

    while (std::getline(file, line)) {
        // Collect curent line from source file
        std::istringstream stream(line);

        // Temporary storage for line components
        std::string component1;
        int component2;
        int component3;

        // Store components from stream
        stream >> component1 >> component2 >> component3;

        // Show components to verify information
        std::cout << component1 << " " << component2  << " " << component3 << std::endl;

        // Append instruction to instructions vector
        instructions.push_back(Instruction(component1, component2, component3));
    }

    std::cout << std::endl;

    //****************************** First In First Out ******************************//

    std::cout << "Scheduled with First In First Out:" << std::endl << std::endl;

    // Sort array based on FIFO
    std::vector<Instruction> fifo_instructions = sort_based_on_arival(instructions);

    // Print out reference
    for (int i = 0; i < fifo_instructions.size(); i++) {
        std::cout << i + 1 << " > "<< fifo_instructions[i].get_name() << " " << fifo_instructions[i].get_burst_duration() << " " << fifo_instructions[i].get_arival_time() << std::endl;
    }

    std::cout << std::endl;

    // Graph FIFO instructions
    print_fifo(fifo_instructions);

    std::cout << std::endl;

    //****************************** Shortest Job First ******************************//

    std::cout << "Scheduled with Shortest Job First:" << std::endl << std::endl;

    // Sort array based on SJF
    std::vector<Instruction> sjf_instructions = sort_based_on_arival(instructions);

    // Print out reference
    for (int i = 0; i < sjf_instructions.size(); i++) {
        std::cout << i + 1 << " > "<< sjf_instructions[i].get_name() << " " << sjf_instructions[i].get_burst_duration() << " " << sjf_instructions[i].get_arival_time() << std::endl;
    }

    std::cout << std::endl;

    // Graph SJF instructions
    print_sjf(sjf_instructions);

    std::cout << std::endl;

    //****************************** Round Robin ******************************//

    // std::cout << "Scheduled with Round Robin:" << std::endl << std::endl;

    // // Sort array based on FIFO
    // std::vector<Instruction> rr_instructions = sort_based_on_arival(instructions);

    // // Print out reference
    // for (int i = 0; i < rr_instructions.size(); i++) {
    //     std::cout << i + 1 << " > "<< rr_instructions[i].get_name() << " " << rr_instructions[i].get_burst_duration() << " " << rr_instructions[i].get_arival_time() << std::endl;
    // }

    // std::cout << std::endl;

    // // Graph RR instructions
    // print_rr(rr_instructions);

    // Close the file
    file.close(); 
    return 0;
}