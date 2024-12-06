#include "parser.hpp"

#include <iostream>
#include <sstream>
#include <regex>
#include <ranges>

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

Opcode to_opcode(string opcode, Pointer pointer) {
    transform(opcode.begin(), opcode.end(), opcode.begin(), ::tolower);
    
    CASE_OPCODE("noop", NOOP)
    CASE_OPCODE("push", PUSH)
    CASE_OPCODE("store", STORE)
    CASE_OPCODE("load", LOAD)
    CASE_OPCODE("swap", SWAP)
    CASE_OPCODE("pop", POP)
    CASE_OPCODE("del", DEL)
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
    CASE_OPCODE("vmcall", VMCALL)
    CASE_OPCODE("dbg", DBG)
    CASE_OPCODE("exit", EXIT)

    throw BytecodeError(BytecodeError::BytecodeErrorKind::InvalidOpcode, pointer);
}

Instructions Parser::parse() {;
    Instructions instructions;
    
    auto r = std::regex_replace(this->content, regex(";.*", ""), "");
    r = std::regex_replace(r, regex("/\\*.*?\\*/"), "");
    
    for (auto line : split(r, '\n')) {
        auto trimmed = trim(line);
        
        if (trimmed.empty()) continue;

        auto result = this->parse_op(split(trimmed, ' '));
        if (!result) continue;
        
        instructions.push_back(result.value());
        this->pointer++;
    }
    
    return instructions;
}

optional<Op> Parser::parse_op(vector<string> op) {
    auto _opcode = op[0];
    transform(_opcode.begin(), _opcode.end(), _opcode.begin(), ::tolower);
    
    if (_opcode.starts_with("#")) {
        _opcode.erase(0, 1);
        this->preprocessing(_opcode, vector(op.begin() + 1, op.end()));
        return nullopt;
    }
    
    auto opcode = to_opcode(_opcode, this->pointer);
    auto operand = op[1];
    
    if (opcode == Opcode::PUSH) {
        if (operand.starts_with("0x")) {
            return Op(opcode, (Value)stoi(operand, 0, 16));
        } else {
            return Op(opcode, (Value)stoi(operand));
        }
    } else if (opcode == Opcode::STORE
               || opcode == Opcode::LOAD
               || opcode == Opcode::DEL) {
        if (std::regex_match(operand, regex("^[a-zA-Z_][a-zA-Z0-9_]*$"))) {
            return Op(opcode, this->heap_get_or_insert(operand));
        }
        else if (operand.starts_with("0x")) {
            return Op(opcode, (Pointer)stoi(operand, 0, 16));
        } else {
            return Op(opcode, (Pointer)stoi(operand));
        }
    } else if (opcode == Opcode::JMP
               || opcode == Opcode::JIF
               || opcode == Opcode::DBG
               || opcode == Opcode::PROC
               || opcode == Opcode::CALL
               || opcode == Opcode::VMCALL) {
        if (operand.starts_with("0x")) {
            return Op(opcode, (Pointer)stoi(operand, 0, 16));
        } else if (operand.starts_with("[") && operand.ends_with("]")) {
            string r = operand.substr(1, operand.length() - 2);
            return Op(opcode, (Pointer)(this->pointer + stoi(r)));
        } else {
            return Op(opcode, (Pointer)stoi(operand));
        }
    } else {
        return Op(opcode, nullopt);
    }
}

void Parser::preprocessing(string name, vector<string> args) {
//    cout << name << ": " << args[0] << args[1] << endl;
    if (name == "startptr") {
        this->pointer = (Pointer)stoi(args[0]);
    }
}

Pointer Parser::heap_get_or_insert(string operand) {
    auto value = this->heap_label_map.find(operand);

    if (value != this->heap_label_map.end()) {
        return value->second;
    } else {
        this->heap_label_map.insert(std::make_pair(operand, this->heap_label_index));
        auto r = this->heap_label_index;
        this->heap_label_index++;
        return r;
    }
}
