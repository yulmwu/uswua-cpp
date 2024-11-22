#include <iostream>

#include "tests.cpp"
#include "../uswua-core/opcode.hpp"

using namespace std;

TEST_CASE(case_1) {
    uint8_t raw_1 = 0x01;

    auto opcode_1 = to_opcode(raw_1);
    ASSERT_EQ(opcode_1, Opcode::PUSH);
    ASSERT_EQ(static_cast<int>(opcode_1), 0x01);
    
    uint8_t raw_2 = 0x10;

    auto opcode_2 = to_opcode(raw_2);
    ASSERT_EQ(opcode_2, Opcode::ADD);
    ASSERT_EQ(static_cast<int>(opcode_2), 0x10);
}
