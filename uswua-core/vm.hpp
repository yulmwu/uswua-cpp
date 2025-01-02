#ifndef vm_hpp
#define vm_hpp

#include <map>
#include <vector>

#include "opcode.hpp"
#include "error.hpp"
#include "memory/memory.hpp"
#include "../uswua-utils/html_logger.hpp"

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

    std::vector<LogMessage> logs;

    // Memory Section
    Stack& stack;
    Heap& heap;
    Data& data;

    Vm(Instructions instructions, Stack& stack, Heap& heap, Data& data)
        : instructions(instructions), stack(stack), heap(heap), data(data) {}
    
    Vm(Instructions instructions, Stack& stack, Heap& heap, Data& data, VmOptions options)
        : instructions(instructions), stack(stack), heap(heap), data(data), options(options) {}
    

    void execute();
    OpExecuted executeOp(Op& op);
    Value getOperand(Op& op);
    Value vmcall(Pointer);

    std::string stackDump();
    std::string heapDump();
    void dump();
    
private:
    Pointer ptr = 0;
    Pointer steps = 0;
    std::vector<Pointer> callStack;
};

#endif /* vm_hpp */
