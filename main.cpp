#include <iostream>
#include <vector>

#include "uswua-core/opcode.hpp"
#include "uswua-core/error.hpp"
#include "uswua-core/vm.hpp"
#include "uswua-utils/b2i.hpp"

#include "uswua-utils/b2i.hpp"
#include "uswua-utils/parser.hpp"

#include "tests/tests_all.cpp"

using namespace std;

int main() {
    TESTS_RUN_ALL();
    
//    std::vector<unsigned char> tests = {
//        /* 00 */ 0x01, 0x00, // PUSH 0
//        /* 01 */ 0x02, 0x00, // STORE 0 (r)   r = 0
//        /* 02 */ 0x01, 0x01, // PUSH 1
//        /* 03 */ 0x02, 0x01, // STORE 1 (i)   i = 1
//        
//        /* 04 */ 0x28, 0x0C, // PROC 12       def f():
//        /* 05 */ 0x03, 0x00, // LOAD 0 (r)
//        /* 06 */ 0x03, 0x01, // LOAD 1 (i)
//        /* 07 */ 0x10, // ADD
//        /* 08 */ 0x02, 0x00, // STORE 0 (r)       r = r + i
//
//        /* 09 */ 0x03, 0x01, // LOAD 1 (i)
//        /* 10 */ 0x01, 0x01, // PUSH 1
//        /* 11 */ 0x10, // ADD
//        /* 12 */ 0x02, 0x01, // STORE 1           i = i + 1
//        /* 13 */ 0x03, 0x01, // LOAD 1
//        /* 14 */ 0x01, 0x0A, // PUSH 10
//        /* 15 */ 0x23, // GTE (>=)                if (10 >= i) { JMP 5 } else { JIF 18 }
//        /* 16 */ 0x2D, 0x12, // JIF 18,
//
//        /* 17 */ 0x2C, 0x05, // JMP 5
//
//        /* 18 */ 0x03, 0x00, // LOAD 0
//        /* 19 */ 0x03, 0x01, // LOAD 0
//        
//
//        0x01, 1, // PUSH 1
//        0x30, 0x01, // VMCALL 0x01(=print)
//        0x05,
//    
//        0x01, 1, // PUSH 1
//        0x30, 0x01, // VMCALL 0x01(=print)
//        
//        /* 18 */ 0x00 // NOOP
//    };
//    
//    auto instructions = b2i_from(tests);
//    
//    Stack stack;
//    Vm vm = Vm(instructions, stack);
//    vm.execute();
    
    return 0;
}

