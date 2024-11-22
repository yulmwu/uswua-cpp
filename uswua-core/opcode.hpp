#ifndef OPCODE_HPP
#define OPCODE_HPP

#include <iostream>
#include <optional>
#include <cstdint>
#include <stdexcept>
#include <vector>

enum class Opcode : uint8_t {
    NOOP = 0x00,
    PUSH = 0x01,
    STORE = 0x02,
    LOAD = 0x03,

    ADD = 0x10,
    SUB = 0x11,
    MUL = 0x12,
    DIV = 0x13,
    MOD = 0x14,

    AND = 0x18,
    OR = 0x19,
    XOR = 0x1A,
    NOT = 0x1B,
    LSF = 0x1C,
    RSF = 0x1D,

    EQ = 0x20,
    GT = 0x21,
    LT = 0x22,
    GTE = 0x23,
    LTE = 0x24,

    PROC = 0x28,
    CALL = 0x29,
    RET = 0x2A,

    JMP = 0x2C,
    JIF = 0x2D,

    DBG = 0xFE,
    EXIT = 0xFF
};

typedef ssize_t Value;
typedef size_t Pointer;

struct Op {
    Opcode opcode;
    std::optional<Value> operand;

    Op(Opcode op, std::optional<Value> val);
    void display(std::ostream& os) const;
};

Opcode to_opcode(uint8_t value, Pointer ptr = 0);

std::ostream& operator<<(std::ostream& os, const Opcode& opcode);
std::ostream& operator<<(std::ostream& os, const Op& op);
bool operator==(const Op& op1, const Op& op2);
bool operator!=(const Op& op1, const Op& op2);

typedef std::vector<Op> Instructions;

#endif // OPCODE_HPP
