#include "opcode.hpp"
#include <iostream>

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
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}

