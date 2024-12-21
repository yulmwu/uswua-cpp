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

struct VmOptions {
    Pointer startPtr = 0;
};

class Vm {
public:
    Instructions instructions;
    VmOptions options;

    Stack& stack;
    Heap& heap;

    Vm(Instructions instructions, Stack& stack, Heap& heap)
        : instructions(instructions), stack(stack), heap(heap) {}
    
    Vm(Instructions instructions, Stack& stack, Heap& heap, VmOptions options)
        : instructions(instructions), stack(stack), heap(heap), options(options) {}
    

    void execute();
    OpExecuted executeOp(Op& op);
    Value getOperand(Op& op);
    Value vmcall(Pointer);

    std::string stackDump();
    std::string heapDump();
    void dump();
    
private:
    Pointer ptr = 0;
    std::vector<Pointer> callStack;
};

#endif /* vm_hpp */
