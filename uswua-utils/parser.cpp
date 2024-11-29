#include "parser.hpp"

#include <iostream>
#include <sstream>
#include "../uswua-core/opcode.hpp"

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
    return Op(Opcode::NOOP, nullopt);
}
