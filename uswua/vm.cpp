#include "iostream"
#include "vm.hpp"

void Vm::execute() {
    auto ptr = 0;
    
    while (instructions.size() > ptr)
    {
        auto result = executeOp(instructions[ptr], ptr);
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
        throw BytecodeError(BytecodeError::BytecodeErrorKind::EmptyOperand, ptr);
    }
}

OpExecuted Vm::executeOp(Op &op, Pointer ptr) {
    std::cout << ptr << ": " << op << std::endl;

    switch (op.opcode) {
        case Opcode::NOOP: break;
        case Opcode::PUSH: {
            this->stack.push(getOperand(op, ptr));
            break;
        }
        case Opcode::STORE: {
            auto value = this->stack.pop(ptr);
            auto addr = this->getOperand(op, ptr);
            this->heap.insert(std::make_pair(addr, value));
            break;
        }
        case Opcode::LOAD: {
            auto addr = this->getOperand(op, ptr);
            auto value = this->heap.find(addr);
            if (value == this->heap.end()) {
                throw BytecodeError(BytecodeError::BytecodeErrorKind::NotFound, ptr);
            }
            this->stack.push(value->second);
            break;
        }
        default: {
            std::logic_error("not implemented");
            break;
        }
    }

    return OpExecuted::OK;
}
