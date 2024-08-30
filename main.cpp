#include <iostream>
#include <vector>
#include "opcode.hpp"
#include "error.hpp"
#include "vm.hpp"

using namespace std;

int main() {
    uint8_t bytecode = 0x01;
    
    try {
        Opcode opcode = to_opcode(bytecode);
        
        cout << "Opcode: " << static_cast<int>(opcode) << endl;
        
        Op op1 = Op(opcode, nullopt);
        cout << "Op1: " << op1 << endl;
        
        Op op2 = Op(opcode, 3);
        cout << "Op2: " << op2 << endl;
        
        vector tests = {
            Op(to_opcode(0x01), 10),
            Op(to_opcode(0xFE), 20),
            Op(to_opcode(0x00), nullopt),
        };
        
        cout << "vm test ---" << endl;
        
        Vm *vm = new Vm(tests);
        vm->execute();
    } catch (const BytecodeError& e) {
        cerr << "ByteCodeError: " << e.what() << endl;
    }
    
    return 0;
}

