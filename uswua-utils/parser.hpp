#ifndef parser_hpp
#define parser_hpp

#include <iostream>
#include <map>
#include <string>

#include "../uswua-core/opcode.hpp"
#include "../uswua-core/vm.hpp"

class Parser {
public:
    std::string content;
    VmOptions vm_options;
    
    Parser(std::string content) : content(content), pointer(0), heap_label_index(0) {}

    Instructions parse();
    
    std::optional<Op> parse_op(std::vector<std::string>);
    Op parse_op_push(Opcode, std::string);
    Op parse_op_heap_op(Opcode, std::string);
    Op parse_op_jmp(Opcode, std::string);
    Op parse_op_proc(Opcode, std::string);
    Op parse_op_call(Opcode, std::string);
    Op parse_op_dbg(Opcode, std::string);
    
    bool preprocessing(std::vector<std::string>);
    
    Pointer heap_get_or_insert(std::string);

private:
    Pointer pointer;

    std::map<std::string, Pointer> heap_label_map;
    Pointer heap_label_index;
    std::map<std::string, Pointer> label_map;
    std::map<std::string, Pointer> proc_map;
};

#endif /* parser_hpp */
