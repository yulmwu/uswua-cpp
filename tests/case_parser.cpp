#include <iostream>
#include <vector>

#include "tests.cpp"
#include "../uswua-core/opcode.hpp"
#include "../uswua-core/vm.hpp"
#include "../uswua-core/memory/memory.hpp"

using namespace std;

TEST_CASE(case_parser) {
    auto code = R"(
#DEFINE A 0x00

PUSH 0x00           ; r = 0
STORE r
PUSH 0x01           ; i = 0
STORE i

PROC 12             ; def f():
    LOAD r
    LOAD i
    ADD
    STORE r         ; r = r + i
    LOAD i
    PUSH 0x01
    ADD
    STORE i         ; i = i + 1
    LOAD i
    PUSH 0x0A
    GTE             ; cond = 10 >= i
    JIF 18          ; if !cond { JIF 18 }

JMP 5

LOAD r
LOAD i
NOOP
)";
    
    Parser p = Parser(code);
    Instructions instructions_a = p.parse();
    
    auto label_r = p.heap_get_or_insert("r");
    auto label_i = p.heap_get_or_insert("i");
    
    ASSERT_EQ(label_r, 0x00);
    ASSERT_EQ(label_i, 0x01);
    
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
    
    auto instructions_b = b2i_from(tests);
    
    for (auto i = 0; i < instructions_b.size(); i++) {
        ASSERT_EQ(instructions_a[i], instructions_b[i]);
//        cout << instructions_a[i] << " | " << instructions_b[i] << endl;
    }
}
