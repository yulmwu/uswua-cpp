#include "iostream"
#include "vm.hpp"

void Vm::execute() {
    Pointer pointer = 0;
    
    while (instructions.size() > pointer)
    {
        std::cout << instructions[pointer] << std::endl;
        pointer++;
    }
}

Value Vm::getOperand(Op op, Pointer ptr) {
    if (op.operand.has_value()) {
        return op.operand.value();
    } else {
        throw BytecodeError(BytecodeError::BytecodeErrorKind::EmptyOpcode);
    }
}
