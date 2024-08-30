#include "iostream"
#include "vm.hpp"

void Vm::execute() {
    Pointer ptr = 0;
    
    while (instructions.size() > ptr)
    {
        OpExecuted result = executeOp(instructions[ptr], ptr);
        if (result == OpExecuted::CONTINUE) {
            continue;
        } else if (result == OpExecuted::BREAK) {
            break;
        }
        ptr++;
    }
}

Value Vm::getOperand(Op& op, Pointer ptr) {
    if (op.operand.has_value()) {
        return op.operand.value();
    } else {
        throw BytecodeError(BytecodeError::BytecodeErrorKind::EmptyOpcode);
    }
}

OpExecuted Vm::executeOp(Op &op, Pointer ptr) {
    std::cout << op << std::endl;

    switch (op.opcode) {
        case Opcode::NOOP:
            break;
        case Opcode::PUSH:
            this->stack.push(getOperand(op, ptr));
            break;
        default:
            std::logic_error("not implemented");
            break;
    }

    return OpExecuted::OK;
}
