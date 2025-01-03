#include "b2i.hpp"

using namespace std;

Instructions b2i_from(vector<unsigned char> bytes) {
    Instructions instructions;
    Pointer index = 0;
    
    while (index < bytes.size()) {
        auto opcode = to_opcode(bytes[index]);
        
        using enum Opcode;
        
        switch (opcode) {
            case PUSH:
            case STORE:
            case LOAD:
            case DEL:
            case DLOAD:
            case PROC:
            case CALL:
            case JMP:
            case JIF:
            case VMCALL:
            case DBG: {
                instructions.push_back(Op(opcode, (Value)bytes[index + 1]));
                index += 1;
                break;
            }
            default: {
                instructions.push_back(Op(opcode, nullopt));
                break;
            }
        }
        
        index += 1;
    }
    
    return instructions;
}
