#include <iostream>
#include <vector>
#include "opcode.hpp"
#include "error.hpp"
#include "vm.hpp"

using namespace std;

int main() {
    uint8_t bytecode = 0x01;
    
    try {
        auto opcode = to_opcode(bytecode);
        
        cout << "Opcode: " << static_cast<int>(opcode) << endl;
        
        auto op1 = Op(opcode, nullopt);
        cout << "Op1: " << op1 << endl;
        
        auto op2 = Op(opcode, 3);
        cout << "Op2: " << op2 << endl;
        
        cout << "----- vm test -----" << endl;
        
        vector tests = {
            Op(to_opcode(0x01), 10), // PUSH 10 -> stack[10] heap{}
            Op(to_opcode(0x01), 20), // PUSH 20 -> stack[10, 20] heap{}
            Op(to_opcode(0x01), 30), // PUSH 30 -> stack[10, 20, 30] heap{}
            Op(to_opcode(0x02), 0), // STORE (addr)0 -> stack[10, 20] heap{0:30}
            Op(to_opcode(0x02), 1), // STORE (addr)1 -> stack[10] heap{0:30,1:20}
            Op(to_opcode(0x03), 0), // LOAD (addr)0 -> stack[10, 30] heap{0:30,1:20}
            Op(to_opcode(0xFE), 20), // DBG
            
            Op(to_opcode(0x28), 2),
            Op(to_opcode(0x00), nullopt),
            Op(to_opcode(0x2A), nullopt),
            Op(to_opcode(0x29), 7),
            
            Op(to_opcode(0x00), nullopt),
        };
        
        Vm *vm = new Vm(tests);
        vm->execute();
        
        vm->stackDump();
        vm->heapDump();
    } catch (const BytecodeError& e) {
        cerr << "ByteCodeError: " << e.what() << " on (ptr)" << e.where() << endl;
    }
    
    return 0;
}

