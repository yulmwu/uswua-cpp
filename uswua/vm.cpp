#include "iostream"
#include "vm.hpp"

void Vm::execute() {
    size_t pointer = 0;
    
    while (instructions.size() > pointer)
    {
        std::cout << instructions[pointer] << std::endl;
        pointer++;
    }
}
