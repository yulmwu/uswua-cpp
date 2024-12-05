#include <iostream>
#include <vector>
#include <ranges>

#include "vm.hpp"
#include "../uswua-utils/time.hpp"

void Vm::execute() {
    while (instructions.size() > ptr)
    {
        auto result = executeOp(instructions[ptr]);
        if (result == OpExecuted::CONTINUE) {
            continue;
        } else if (result == OpExecuted::BREAK) {
            break;
        }
        this->ptr++;
    }
}

OpExecuted Vm::executeOp(Op &op) {
    switch (op.opcode) {
        case Opcode::NOOP: break;
        case Opcode::PUSH: {
            this->stack.push(getOperand(op));
            break;
        }
        case Opcode::STORE: {
            auto value = this->stack.pop(this->ptr);
            auto addr = (Pointer)this->getOperand(op);
            this->heap.insert_or_assign(addr, value);
            break;
        }
        case Opcode::LOAD: {
            auto addr = (Pointer)this->getOperand(op);
            auto value = this->heap.find(addr);
            if (value == this->heap.end()) {
                throw BytecodeError(BytecodeError::BytecodeErrorKind::NotFound, this->ptr);
            }
            this->stack.push(value->second);
            break;
        }
        case Opcode::SWAP: {
            auto x = this->stack.pop(this->ptr);
            auto y = this->stack.pop(this->ptr);
            
            this->stack.push(x);
            this->stack.push(y);
            break;
        }
        case Opcode::POP: {
            this->stack.pop(this->ptr);
            break;
        }
        case Opcode::DEL: {
            this->heap.erase((Pointer)this->getOperand(op));
            break;
        }
        case Opcode::ADD: {
            auto left = this->stack.pop(this->ptr);
            auto right = this->stack.pop(this->ptr);

            this->stack.push(left + right);
            break;
        }
        case Opcode::SUB: {
            auto left = this->stack.pop(this->ptr);
            auto right = this->stack.pop(this->ptr);

            this->stack.push(left - right);
            break;
        }
        case Opcode::MUL: {
            auto left = this->stack.pop(this->ptr);
            auto right = this->stack.pop(this->ptr);

            this->stack.push(left * right);
            break;
        }
        case Opcode::DIV: {
            auto left = this->stack.pop(this->ptr);
            auto right = this->stack.pop(this->ptr);

            this->stack.push(left / right);
            break;
        }
        case Opcode::MOD: {
            auto left = this->stack.pop(this->ptr);
            auto right = this->stack.pop(this->ptr);

            this->stack.push(left % right);
            break;
        }
        case Opcode::AND: {
            auto left = this->stack.pop(this->ptr);
            auto right = this->stack.pop(this->ptr);

            this->stack.push(left & right);
            break;
        }
        case Opcode::OR: {
            auto left = this->stack.pop(this->ptr);
            auto right = this->stack.pop(this->ptr);

            this->stack.push(left | right);
            break;
        }
        case Opcode::XOR: {
            auto left = this->stack.pop(this->ptr);
            auto right = this->stack.pop(this->ptr);

            this->stack.push(left ^ right);
            break;
        }
        case Opcode::NOT: {
            auto right = this->stack.pop(this->ptr);

            this->stack.push(!right);
            break;
        }
        case Opcode::LSF: {
            auto left = this->stack.pop(this->ptr);
            auto right = this->stack.pop(this->ptr);

            this->stack.push(left << right);
            break;
        }
        case Opcode::RSF: {
            auto left = this->stack.pop(this->ptr);
            auto right = this->stack.pop(this->ptr);

            this->stack.push(left >> right);
            break;
        }
        case Opcode::EQ: {
            auto left = this->stack.pop(this->ptr);
            auto right = this->stack.pop(this->ptr);

            this->stack.push(left == right);
            break;
        }
        case Opcode::GT: {
            auto left = this->stack.pop(this->ptr);
            auto right = this->stack.pop(this->ptr);

            this->stack.push(left > right);
            break;
        }
        case Opcode::LT: {
            auto left = this->stack.pop(this->ptr);
            auto right = this->stack.pop(this->ptr);

            this->stack.push(left < right);
            break;
        }
        case Opcode::GTE: {
            auto left = this->stack.pop(this->ptr);
            auto right = this->stack.pop(this->ptr);

            this->stack.push(left >= right);
            break;
        }
        case Opcode::LTE: {
            auto left = this->stack.pop(this->ptr);
            auto right = this->stack.pop(this->ptr);

            this->stack.push(left <= right);
            break;
        }
        case Opcode::PROC: {
            this->ptr = this->ptr + ((Pointer)this->getOperand(op)) + 1;
            return OpExecuted::CONTINUE;
        }
        case Opcode::CALL: {
            this->callStack.push_back(this->ptr + 1);
            this->ptr = (Pointer)this->getOperand(op) + 1;
            return OpExecuted::CONTINUE;
        }
        case Opcode::RET: {
            if (this->callStack.empty()) {
                throw BytecodeError(BytecodeError::BytecodeErrorKind::EmptyCallStack, ptr);
            }

            auto ptr = this->callStack.back();
            this->callStack.pop_back();
            
            this->ptr = ptr;
            return OpExecuted::CONTINUE;
        }
        case Opcode::JMP: {
            this->ptr = (Pointer)this->getOperand(op);
            return OpExecuted::CONTINUE;
        }
        case Opcode::JIF: {
            if (this->stack.pop(this->ptr) == 0) {
                this->ptr = (Pointer)this->getOperand(op);
                return OpExecuted::CONTINUE;
            }
            
            break;
        }
        case Opcode::VMCALL: {
            this->stack.push(this->vmcall(this->getOperand(op)));
            break;
        }
        case Opcode::DBG: {
            std::cout << std::endl;
            std::cout << "[" << current_time() << "] ";
            std::cout << "operand: " << op.operand.value();
            std::cout << std::endl << std::endl;
            break;
        }
        case Opcode::EXIT: {
            return OpExecuted::BREAK;
        }
    }

    return OpExecuted::OK;
}

Value Vm::vmcall(Pointer callno) {
    auto args_len = this->stack.pop(this->ptr);

    switch (callno) {
        // print(args_len, ...args)
        case 0x00: {
            for (int i = 0; i < args_len; i++) std::cout << stack.pop(this->ptr) << " ";
            break;
        }
        // println(args_len, ...args)
        case 0x01: {
            for (int i = 0; i < args_len; i++) std::cout << stack.pop(this->ptr) << " ";
            std::cout << std::endl;
            break;
        }
        default: {
            throw BytecodeError(BytecodeError::BytecodeErrorKind::UnknownCallNo, this->ptr);
        }
    }
    
    return 0;
}

Value Vm::getOperand(Op& op) {
    if (op.operand.has_value()) {
        return op.operand.value();
    } else {
        throw BytecodeError(BytecodeError::BytecodeErrorKind::EmptyOperand, this->ptr);
    }
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

void Vm::dump() {
    std::cout << "----- dumping stack ptr=" << this->ptr << " -----" << std::endl;
    for (auto i = 0; i < this->stack.values_.size(); i++) {
        std::cout << i << ": " << stack.values_[i] << std::endl;
    }
    std::cout << "----- dumping heap -----" << std::endl;
    for (const auto& pair : this->heap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    std::cout << "------------------------" << std::endl;
}
