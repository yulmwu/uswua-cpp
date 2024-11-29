#include <iostream>
#include <vector>

#include "tests.cpp"
#include "../uswua-core/opcode.hpp"
#include "../uswua-core/vm.hpp"
#include "../uswua-core/stack.hpp"

using namespace std;

TEST_CASE(case_parser) {
    auto code = R"(
PUSH 0x00
STORE 0x00
PUSH 0x01
STORE 0x01
PROC 12
LOAD 0x00
LOAD 0x01
ADD
STORE 0x0
LOAD 0x01
PUSH 0x01
ADD
STORE 0x01
LOAD 0x01
PUSH 0x0A
GTE
JIF 18
JMP 5
LOAD 0x00
LOAD 0x01
NOOP
)";
    
    std::vector<unsigned char> tests = {
        /* 00 */ 0x01, 0x00, // PUSH 0
        /* 01 */ 0x02, 0x00, // STORE 0 (r)   r = 0
        /* 02 */ 0x01, 0x01, // PUSH 1
        /* 03 */ 0x02, 0x01, // STORE 1 (i)   i = 1
        
        /* 04 */ 0x28, 0x0C, // PROC 12       def f():
        /* 05 */ 0x03, 0x00, // LOAD 0 (r)
        /* 06 */ 0x03, 0x01, // LOAD 1 (i)
        /* 07 */ 0x10, // ADD
        /* 08 */ 0x02, 0x00, // STORE 0 (r)       r = r + i

        /* 09 */ 0x03, 0x01, // LOAD 1 (i)
        /* 10 */ 0x01, 0x01, // PUSH 1
        /* 11 */ 0x10, // ADD
        /* 12 */ 0x02, 0x01, // STORE 1           i = i + 1
        /* 13 */ 0x03, 0x01, // LOAD 1
        /* 14 */ 0x01, 0x0A, // PUSH 10
        /* 15 */ 0x23, // GTE (>=)                if (10 >= i) { JMP 5 } else { JIF 18 }
        /* 16 */ 0x2D, 0x12, // JIF 18,

        /* 17 */ 0x2C, 0x05, // JMP 5

        /* 18 */ 0x03, 0x00, // LOAD 0
        /* 19 */ 0x03, 0x01, // LOAD 1
        /* 18 */ 0x00 // NOOP
    };
    
    auto instructions_a = b2i_from(tests);
    Parser p = Parser(code);
    Instructions instructions_b = p.parse();
    
    for (auto i = 0; i < instructions_a.size(); i++) {
        ASSERT_EQ(instructions_a[i], instructions_b[i]);
//        cout << instructions_a[i] << " | " << instructions_b[i] << endl;
    }
}
