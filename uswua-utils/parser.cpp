#include "parser.hpp"

#include <iostream>
#include <sstream>

#include "../uswua-core/opcode.hpp"
#include "../uswua-core/error.hpp"

#define CASE_OPCODE(opcode_str, enum_value) \
    if (opcode == opcode_str) { return Opcode::enum_value; }


using namespace std;

vector<string> split(string str, char delimiter) {
    istringstream stream(str);
    string buffer;
 
    vector<string> result;
 
    while (getline(stream, buffer, delimiter)) result.push_back(buffer);
 
    return result;
}

string trim(string str) {
    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ') + 1);

    return str;
}

Opcode to_opcode(string opcode, Pointer pointer = 0) {
    transform(opcode.begin(), opcode.end(), opcode.begin(), ::tolower);
    
    CASE_OPCODE("noop", NOOP)
    CASE_OPCODE("push", PUSH)
    CASE_OPCODE("store", STORE)
    CASE_OPCODE("load", LOAD)
    CASE_OPCODE("swap", SWAP)
    CASE_OPCODE("add", ADD)
    CASE_OPCODE("sub", SUB)
    CASE_OPCODE("mul", MUL)
    CASE_OPCODE("div", DIV)
    CASE_OPCODE("mod", MOD)
    CASE_OPCODE("and", AND)
    CASE_OPCODE("or", OR)
    CASE_OPCODE("xor", XOR)
    CASE_OPCODE("not", NOT)
    CASE_OPCODE("lsf", LSF)
    CASE_OPCODE("rsf", RSF)
    CASE_OPCODE("eq", EQ)
    CASE_OPCODE("gt", GT)
    CASE_OPCODE("lt", LT)
    CASE_OPCODE("gte", GTE)
    CASE_OPCODE("lte", LTE)
    CASE_OPCODE("proc", PROC)
    CASE_OPCODE("call", CALL)
    CASE_OPCODE("ret", RET)
    CASE_OPCODE("jmp", JMP)
    CASE_OPCODE("jif", JIF)
    CASE_OPCODE("dbg", DBG)
    CASE_OPCODE("exit", EXIT)

    throw BytecodeError(BytecodeError::BytecodeErrorKind::InvalidOpcode, pointer);
}

Instructions Parser::parse() {
    Instructions instructions;
    
    for (auto line : split(this->content, '\n')) {
        auto trimmed = trim(line);
        
        if (trimmed.empty()) continue;

        instructions.push_back(this->parse_op(split(trimmed, ' ')));
    }
    
    return instructions;
}

Op Parser::parse_op(vector<string> op) {
    auto _opcode = op[0];
    transform(_opcode.begin(), _opcode.end(), _opcode.begin(), ::tolower);
    
    auto opcode = to_opcode(_opcode);
    auto operand = op[1];
    
    if (opcode == Opcode::PUSH) {
        if (operand.starts_with("0x")) {
            return Op(opcode, (Value)stoi(operand, 0, 16));
        } else {
            return Op(opcode, (Value)stoi(operand));
        }
    } else if (opcode == Opcode::STORE
               || opcode == Opcode::LOAD 
               || opcode == Opcode::JMP
               || opcode == Opcode::JIF
               || opcode == Opcode::DBG
               || opcode == Opcode::PROC
               || opcode == Opcode::CALL) {
        if (operand.starts_with("0x")) {
            return Op(opcode, (Pointer)stoi(operand, 0, 16));
        } else {
            return Op(opcode, (Pointer)stoi(operand));
        }
    } else {
        return Op(opcode, nullopt);
    }
}
