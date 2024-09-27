#include "iostream"
#include "vector"
#include "ranges"
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
        case Opcode::ADD: {
            auto left = this->stack.pop(ptr);
            auto right = this->stack.pop(ptr);

            this->stack.push(left + right);
            break;
        }
        case Opcode::SUB: {
            auto left = this->stack.pop(ptr);
            auto right = this->stack.pop(ptr);

            this->stack.push(left - right);
            break;
        }
        case Opcode::MUL: {
            auto left = this->stack.pop(ptr);
            auto right = this->stack.pop(ptr);

            this->stack.push(left * right);
            break;
        }
        case Opcode::DIV: {
            auto left = this->stack.pop(ptr);
            auto right = this->stack.pop(ptr);

            this->stack.push(left / right);
            break;
        }
        case Opcode::MOD: {
            auto left = this->stack.pop(ptr);
            auto right = this->stack.pop(ptr);

            this->stack.push(left % right);
            break;
        }
        case Opcode::AND: {
            auto left = this->stack.pop(ptr);
            auto right = this->stack.pop(ptr);

            this->stack.push(left & right);
            break;
        }
        case Opcode::OR: {
            auto left = this->stack.pop(ptr);
            auto right = this->stack.pop(ptr);

            this->stack.push(left | right);
            break;
        }
        case Opcode::XOR: {
            auto left = this->stack.pop(ptr);
            auto right = this->stack.pop(ptr);

            this->stack.push(left ^ right);
            break;
        }
        case Opcode::NOT: {
            auto right = this->stack.pop(ptr);

            this->stack.push(!right);
            break;
        }
        case Opcode::LSF: {
            auto left = this->stack.pop(ptr);
            auto right = this->stack.pop(ptr);

            this->stack.push(left << right);
            break;
        }
        case Opcode::RSF: {
            auto left = this->stack.pop(ptr);
            auto right = this->stack.pop(ptr);

            this->stack.push(left >> right);
            break;
        }
        case Opcode::EQ: {
            auto left = this->stack.pop(ptr);
            auto right = this->stack.pop(ptr);

            this->stack.push(left == right);
            break;
        }
        case Opcode::GT: {
            auto left = this->stack.pop(ptr);
            auto right = this->stack.pop(ptr);

            this->stack.push(left > right);
            break;
        }
        case Opcode::LT: {
            auto left = this->stack.pop(ptr);
            auto right = this->stack.pop(ptr);

            this->stack.push(left < right);
            break;
        }
        case Opcode::GTE: {
            auto left = this->stack.pop(ptr);
            auto right = this->stack.pop(ptr);

            this->stack.push(left >= right);
            break;
        }
        case Opcode::LTE: {
            auto left = this->stack.pop(ptr);
            auto right = this->stack.pop(ptr);

            this->stack.push(left <= right);
            break;
        }
        default: {
            std::logic_error("not implemented");
            break;
        }
    }

    return OpExecuted::OK;
}

void Vm::stackDump() {
    std::cout << "----- dumping stack -----" << std::endl;
    for (auto i = 0; i < this->stack.values_.size(); i++) {
        std::cout << i << ": " << stack.values_[i] << std::endl;
    }
    std::cout << "-------------------------" << std::endl;
}

void Vm::heapDump() {
    std::cout << "----- dumping heap -----" << std::endl;
    for (const auto& pair : this->heap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    std::cout << "------------------------" << std::endl;
}
