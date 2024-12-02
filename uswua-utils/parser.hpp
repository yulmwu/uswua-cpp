#ifndef parser_hpp
#define parser_hpp

#include <iostream>
#include <map>
#include <string>

#include "../uswua-core/opcode.hpp"

class Parser {
public:
    std::string content;
    
    Parser(std::string content) : content(content), heap_label_index(0) {}

    Instructions parse();
    Op parse_op(std::vector<std::string>);

private:
    std::map<std::string, Pointer> heap_label_map;
    Pointer heap_label_index ;
};

#endif /* parser_hpp */
