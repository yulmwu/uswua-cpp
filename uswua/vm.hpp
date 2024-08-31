#ifndef vm_hpp
#define vm_hpp

#include "map"
#include "opcode.hpp"
#include "stack.hpp"
#include "error.hpp"

enum class OpExecuted {
    OK,
    CONTINUE,
    BREAK
};

class Vm {
public:
    Instructions instructions;
    
    Vm(Instructions instructions) : instructions(instructions), stack(), heap()
    {}
    void execute();
    Value getOperand(Op& op, Pointer ptr);
    OpExecuted executeOp(Op& op, Pointer ptr);
    
private:
    Stack stack;
    std::map<Pointer, Value> heap;
};

#endif /* vm_hpp */
