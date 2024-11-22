#include "opcode.hpp"
#include "error.hpp"

Op::Op(Opcode op, std::optional<Value> val) : opcode(op), operand(val) {}

void Op::display(std::ostream& os) const {
    os << opcode;

    if (this->operand.has_value()) {
        os << " " << this->operand.value();
    }
}

Opcode to_opcode(uint8_t value, Pointer ptr) {
    switch (value) {
        case 0x00: return Opcode::NOOP;
        case 0x01: return Opcode::PUSH;
        case 0x02: return Opcode::STORE;
        case 0x03: return Opcode::LOAD;
        case 0x10: return Opcode::ADD;
        case 0x11: return Opcode::SUB;
        case 0x12: return Opcode::MUL;
        case 0x13: return Opcode::DIV;
        case 0x14: return Opcode::MOD;
        case 0x18: return Opcode::AND;
        case 0x19: return Opcode::OR;
        case 0x1A: return Opcode::XOR;
        case 0x1B: return Opcode::NOT;
        case 0x1C: return Opcode::LSF;
        case 0x1D: return Opcode::RSF;
        case 0x20: return Opcode::EQ;
        case 0x21: return Opcode::GT;
        case 0x22: return Opcode::LT;
        case 0x23: return Opcode::GTE;
        case 0x24: return Opcode::LTE;
        case 0x28: return Opcode::PROC;
        case 0x29: return Opcode::CALL;
        case 0x2A: return Opcode::RET;
        case 0x2C: return Opcode::JMP;
        case 0x2D: return Opcode::JIF;
        case 0xFE: return Opcode::DBG;
        case 0xFF: return Opcode::EXIT;
        default: throw BytecodeError(BytecodeError::BytecodeErrorKind::InvalidOpcode, ptr);
    }
}

std::ostream& operator<<(std::ostream& os, const Op& op) {
    op.display(os);
    return os;
}

std::ostream& operator<<(std::ostream& os, const Opcode& opcode) {
    os << "0x" << std::hex << static_cast<int>(opcode);
    return os;
}
