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
    
    Vm(Instructions instructions)
        : instructions(instructions), stack(*(new Stack())), heap(), ptr(0) {}
    Vm(Instructions instructions, Stack& stack) : instructions(instructions), stack(stack), heap(), ptr(0)
    {}
    void execute();
    Value getOperand(Op& op);
    OpExecuted executeOp(Op& op);

    void stackDump();
    void heapDump();
    
private:
    Pointer ptr;
    Stack& stack;
    std::map<Pointer, Value> heap;
    std::vector<Pointer> callStack;
};

#endif /* vm_hpp */
