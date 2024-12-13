#ifndef parser_hpp
#define parser_hpp

#include <iostream>
#include <map>
#include <string>

#include "../uswua-core/opcode.hpp"

class Parser {
public:
    std::string content;
    
    Parser(std::string content) : content(content), pointer(0), heap_label_index(0) {}

    Instructions parse();
    std::optional<Op> parse_op(std::vector<std::string>);
    bool preprocessing(std::vector<std::string>);
    
    Pointer heap_get_or_insert(std::string);

private:
    Pointer pointer;
    std::map<std::string, Pointer> heap_label_map;
    Pointer heap_label_index;
    std::map<std::string, Pointer> label_map;
};

#endif /* parser_hpp */
