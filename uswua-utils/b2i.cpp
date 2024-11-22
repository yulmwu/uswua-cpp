#include "b2i.hpp"

Instructions b2i_from(std::vector<unsigned char> bytes) {
    Instructions instructions;
    Pointer index = 0;
    
    while (index < bytes.size()) {
        auto opcode = to_opcode(bytes[index]);
        
        using enum Opcode;
        
        switch (opcode) {
            case PUSH:
            case STORE:
            case LOAD:
            case PROC:
            case CALL:
            case JMP:
            case JIF:
            case DBG: {
                instructions.push_back(Op(opcode, (Value)bytes[index + 1]));
                index += 1;
                break;
            }
            default: {
                instructions.push_back(Op(opcode, std::nullopt));
                break;
            }
        }
        
        index += 1;
    }
    
    return instructions;
}
