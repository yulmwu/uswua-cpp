#ifndef vm_hpp
#define vm_hpp

#include <map>
#include <vector>

#include "opcode.hpp"
#include "stack.hpp"
#include "heap.hpp"
#include "error.hpp"

enum class OpExecuted {
    OK,
    CONTINUE,
    BREAK
};

class Vm {
public:
    Instructions instructions;

    Stack& stack;
    Heap& heap;

    Vm(Instructions instructions, Stack& stack, Heap& heap)
        : instructions(instructions), stack(stack), heap(heap), ptr(0) {}

    void execute();
    OpExecuted executeOp(Op& op);
    Value getOperand(Op& op);
    Value vmcall(Pointer);

    std::string stackDump();
    void heapDump();
    void dump();
    
private:
    Pointer ptr;
    std::vector<Pointer> callStack;
};

#endif /* vm_hpp */
