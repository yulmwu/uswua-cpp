#ifndef vm_hpp
#define vm_hpp

#include "opcode.hpp"
#include "stack.hpp"
#include "error.hpp"

class Vm {
public:
    Instructions instructions;
    
    Vm(Instructions instructions) : instructions(instructions)
    {}
    void execute();
    
private:
    Stack stack;
};

#endif /* vm_hpp */
