#ifndef vm_hpp
#define vm_hpp

#include "map"
#include "vector"
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

    void stackDump();
    void heapDump();
    
private:
    Stack stack;
    std::map<Pointer, Value> heap;
    std::vector<Pointer> callStack;
};

#endif /* vm_hpp */
