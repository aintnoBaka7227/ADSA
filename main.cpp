#include <iostream>
#include <vector> 
#include <string> 
#include <sstream> 

int main() {
    std::string instruction;
    getline(std::cin, instruction);
    std::stringstream ss(instruction);
    std::string move;
    std::vector<std::string> moves;
    while(ss >> move) {
        moves.push_back(move);
    }

    
    return 0;
}