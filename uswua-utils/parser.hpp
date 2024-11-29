#ifndef parser_hpp
#define parser_hpp

#include <iostream>
#include "../uswua-core/opcode.hpp"

class Parser {
public:
    std::string content;
    
    Parser(std::string content) : content(content) {}

    Instructions parse();
    Op parse_op(std::vector<std::string>);
};

#endif /* parser_hpp */
