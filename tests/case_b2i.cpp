#include <iostream>
#include <vector>

#include "tests.cpp"

#include "../uswua-core/opcode.hpp"
#include "../uswua-utils/b2i.hpp"

using namespace std;

TEST_CASE(case_b2i) {
    vector<unsigned char> bytes = {
        0x28, 0x02, 0x00, 0x2a, 0x29, 0x00, 0x00
    };
    
    using enum Opcode;

    Instructions test = {
        Op(PROC, 0x02),
        Op(NOOP, nullopt),
        Op(RET, nullopt),
        Op(CALL, 0x00),
        Op(NOOP, nullopt),
    };
    
    auto instructions = b2i_from(bytes);

    for (auto i = 0; i < instructions.size(); i++) {
        ASSERT_EQ(instructions[i], test[i]);
    }
}
