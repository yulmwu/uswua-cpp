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
    CASE_OPCODE("dup", DUP)
    CASE_OPCODE("dload", DLOAD)
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

    throw BytecodeError(BytecodeError::BytecodeErrorKind::InvalidOpcode, pointer, opcode);
}

Instructions Parser::parse() {
    Instructions instructions;
    
    auto r = regex_replace(this->content, regex(";.*", ""), "");
    r = regex_replace(r, regex("/\\*.*?\\*/"), "");
    
    vector<string> preprocessed;
    
    // preprocessing
    for (auto line : split(r, '\n')) {
        auto trimmed = trim(line);
        if (trimmed.empty() || trimmed.starts_with(';')) continue;

        auto is_preprocess = this->preprocessing(split(trimmed, ' '));
        
        if (!is_preprocess) {
            preprocessed.push_back(trimmed);
            this->pointer++;
        }
    }
    
    this->pointer = 0;
    
    for (auto line : preprocessed) {
        auto result = this->parse_op(split(line, ' '));
        if (!result) continue;
        
        this->pointer++;
        instructions.push_back(result.value());
    }
    
    return instructions;
}

optional<Op> Parser::parse_op(vector<string> op) {
    auto _opcode = op[0];
    transform(_opcode.begin(), _opcode.end(), _opcode.begin(), ::tolower);
    
    auto opcode = to_opcode(_opcode, this->pointer);
    auto operand = op[1];
    
    if (opcode == Opcode::PUSH || opcode == Opcode::DLOAD) {
        return this->parse_op_push(opcode, operand);
    } else if (opcode == Opcode::STORE || opcode == Opcode::LOAD || opcode == Opcode::DEL) {
        return this->parse_op_heap_op(opcode, operand);
    } else if (opcode == Opcode::JMP || opcode == Opcode::JIF) {
        return this->parse_op_jmp(opcode, operand);
    } else if (opcode == Opcode::PROC) {
        return this->parse_op_proc(opcode, operand);
    } else if (opcode == Opcode::CALL) {
        return this->parse_op_call(opcode, operand);
    } else if (opcode == Opcode::DBG || opcode == Opcode::VMCALL) {
        return this->parse_op_dbg(opcode, operand);
    } else {
        return Op(opcode, nullopt);
    }
}

Op Parser::parse_op_push(Opcode opcode, string operand) {
    if (operand.starts_with("0x")) {
        return Op(opcode, (Value)stoi(operand, 0, 16));
    } else {
        return Op(opcode, (Value)stoi(operand));
    }
}

Op Parser::parse_op_heap_op(Opcode opcode, string operand) {
    if (regex_match(operand, regex("^[a-zA-Z_][a-zA-Z0-9_]*$"))) {
        return Op(opcode, this->heap_get_or_insert(operand));
    }
    else if (operand.starts_with("0x")) {
        return Op(opcode, (Pointer)stoi(operand, 0, 16));
    } else {
        return Op(opcode, (Pointer)stoi(operand));
    }
}

Op Parser::parse_op_jmp(Opcode opcode, string operand) {
    if (operand.starts_with("0x")) {
        return Op(opcode, (Pointer)stoi(operand, 0, 16));
    } else if (operand.starts_with("[") && operand.ends_with("]")) {
        string r = operand.substr(1, operand.length() - 2);
        return Op(opcode, (Pointer)(this->pointer + stoi(r)));
    } else if (regex_match(operand, regex("^[a-zA-Z_][a-zA-Z0-9_]*$"))) {
        auto value = this->label_map.find(operand);

        if (value != this->label_map.end()) {
            return Op(opcode, value->second);
        } else {
            throw BytecodeError(BytecodeError::BytecodeErrorKind::IdentifierNotFound, pointer, operand);
        }
    } else {
        return Op(opcode, (Pointer)stoi(operand));
    }
}

Op Parser::parse_op_proc(Opcode opcode, string operand) {
    if (operand.starts_with("0x")) {
        return Op(opcode, (Pointer)stoi(operand, 0, 16));
    } else if (operand.starts_with("[") && operand.ends_with("]")) {
        string r = operand.substr(1, operand.length() - 2);
        return Op(opcode, (Pointer)(this->pointer + stoi(r)));
    } else if (regex_match(operand, regex("^[a-zA-Z_][a-zA-Z0-9_]*$")))  {
        this->proc_map.insert_or_assign(operand, this->pointer);

        auto value = this->preprocess_proc_map.find(operand);

        if (value != this->preprocess_proc_map.end()) {
            return Op(opcode, value->second);
        } else {
            throw BytecodeError(BytecodeError::BytecodeErrorKind::IdentifierNotFound, pointer, operand);
        }
    } else {
        return Op(opcode, (Value)stoi(operand));
    }
}

Op Parser::parse_op_call(Opcode opcode, string operand) {
    if (operand.starts_with("0x")) {
        return Op(opcode, (Pointer)stoi(operand, 0, 16));
    } else if (operand.starts_with("[") && operand.ends_with("]")) {
        string r = operand.substr(1, operand.length() - 2);
        return Op(opcode, (Pointer)(this->pointer + stoi(r)));
    } else if (regex_match(operand, regex("^[a-zA-Z_][a-zA-Z0-9_]*$")))  {
        auto value = this->proc_map.find(operand);

        if (value != this->proc_map.end()) {
            return Op(opcode, value->second);
        } else {
            throw BytecodeError(BytecodeError::BytecodeErrorKind::IdentifierNotFound, pointer, operand);
        }
    } else {
        return Op(opcode, (Value)stoi(operand));
    }
}

Op Parser::parse_op_dbg(Opcode opcode, string operand) {
    if (operand.starts_with("0x")) {
        return Op(opcode, (Pointer)stoi(operand, 0, 16));
    } else if (operand.starts_with("[") && operand.ends_with("]")) {
        string r = operand.substr(1, operand.length() - 2);
        return Op(opcode, (Pointer)(this->pointer + stoi(r)));
    } else {
        return Op(opcode, (Pointer)stoi(operand));
    }
}

bool Parser::preprocessing(vector<string> args) {
    if (args[0].starts_with("#")) {
        args[0].erase(0, 1);
        auto name = args[0];
        transform(name.begin(), name.end(), name.begin(), ::tolower);

        auto arguments = vector(args.begin() + 1, args.end());

        if (name == "startptr") {
            this->vm_options.startPtr = (Pointer)stoi(arguments[0]);
        } else if (name == "pstart") {
            this->preprocess_proc_map.insert_or_assign(arguments[0], this->pointer + 1);
        } else if (name == "pend") {
            auto value = this->preprocess_proc_map.find(arguments[0]);

            if (value != this->preprocess_proc_map.end()) {
                this->preprocess_proc_map[arguments[0]] = this->pointer - value->second;
            } else {
                throw BytecodeError(BytecodeError::BytecodeErrorKind::IdentifierNotFound, pointer, arguments[0]);
            }
        } else {
            throw BytecodeError(BytecodeError::BytecodeErrorKind::UnknownPreprocessor, pointer, name);
        }
    } else if (args[0].ends_with(":")) {
        args[0].pop_back();
        this->label_map.insert_or_assign(args[0], this->pointer);
    } else {
        return false;
    }

    return true;
}

Pointer Parser::heap_get_or_insert(string operand) {
    auto value = this->heap_label_map.find(operand);

    if (value != this->heap_label_map.end()) {
        return value->second;
    } else {
        this->heap_label_map.insert(make_pair(operand, this->heap_label_index));
        auto r = this->heap_label_index;
        this->heap_label_index++;
        return r;
    }
}
