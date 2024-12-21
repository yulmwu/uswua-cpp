#include <iostream>
#include <vector>
#include <ranges>
#include <iomanip>
#include <sstream>

#include "vm.hpp"
#include "../uswua-utils/time.hpp"

using namespace std;

void Vm::execute() {
    this->ptr = this->options.startPtr;
    
    while (this->instructions.size() > this->ptr) {
        auto result = this->executeOp(this->instructions[this->ptr]);
        
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
            auto value = this->heap.get(addr, this->ptr);
            this->stack.push(value);
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
            auto addr = (Pointer)this->getOperand(op);
            this->heap.erase(addr, this->ptr);
            break;
        }
        case Opcode::DUP: {
            auto value = stack.back(this->ptr);
            this->stack.push(value);
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
            cout << endl;
            cout << "[" << current_time() << "] ";
            cout << "operand: " << op.operand.value();
            cout << endl << endl;
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
            for (int i = 0; i < args_len; i++) cout << stack.pop(this->ptr) << " ";
            break;
        }
        // println(args_len, ...args)
        case 0x01: {
            for (int i = 0; i < args_len; i++) cout << stack.pop(this->ptr) << " ";
            cout << endl;
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

string Vm::stackDump() {
    stringstream ss;
    
    vector<Value> arr = this->stack.data;
    arr.resize(((arr.size() + 15) / 16) * 16, 0);
    
    const size_t bytes_per_line = 16;

    for (size_t i = 0; i < arr.size(); i += bytes_per_line) {
        ss << setw(4) << setfill('0') << hex << i << ": ";

        for (size_t j = 0; j < bytes_per_line; ++j) {
            ss << setw(2) << setfill('0') << hex << static_cast<int>(arr[i + j]) << " ";

            if (j == 7) {
                ss << "  ";
            }
        }

        ss << " -- ";

        for (size_t j = 0; j < bytes_per_line; ++j) {
            if (i + j < arr.size()) {
                unsigned char c = arr[i + j];
                if (c >= 32 && c <= 126) {
                    ss << c;
                } else {
                    ss << '.';
                }
            } else {
                break;
            }
        }

        ss << endl;
    }
    
    return ss.str();
}

string Vm::heapDump() {
    stringstream ss;

    if (this->heap.data.empty()) {
        return "Heap is empty";
    }

    Pointer min_address = this->heap.data.begin()->first;
    Pointer max_address = this->heap.data.rbegin()->first;

    min_address = (min_address / 16) * 16;
    max_address = ((max_address + 15) / 16) * 16;

    const size_t bytes_per_line = 16;

    for (Pointer i = min_address; i < max_address; i += bytes_per_line) {
        ss << setw(4) << setfill('0') << hex << i << ": ";

        for (size_t j = 0; j < bytes_per_line; ++j) {
            Pointer current_address = i + j;

            if (this->heap.data.count(current_address)) {
                ss << setw(2) << setfill('0') << hex << static_cast<int>(this->heap.data.at(current_address)) << " ";
            } else {
                ss << "00 ";
            }

            if (j == 7) {
                ss << "  ";
            }
        }

        ss << " -- ";

        for (size_t j = 0; j < bytes_per_line; ++j) {
            Pointer current_address = i + j;

            if (this->heap.data.count(current_address)) {
                unsigned char c = static_cast<unsigned char>(this->heap.data.at(current_address));
                if (c >= 32 && c <= 126) {
                    ss << c;
                } else {
                    ss << '.';
                }
            } else {
                ss << '.';
            }
        }

        ss << endl;
    }

    return ss.str();
}

void Vm::dump() {
    cout << "----- dumping stack ptr=" << this->ptr << " -----" << endl;
    for (auto i = 0; i < this->stack.data.size(); i++) {
        cout << i << ": " << stack.data[i] << endl;
    }
    cout << "----- dumping heap -----" << endl;
    for (const auto& pair : this->heap.data) {
        cout << pair.first << ": " << pair.second << endl;
    }
    cout << "------------------------" << endl;
}
