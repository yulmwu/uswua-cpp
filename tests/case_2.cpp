#include <iostream>
#include <vector>

#include "tests.cpp"
#include "../uswua-core/opcode.hpp"
#include "../uswua-core/vm.hpp"
#include "../uswua-core/stack.hpp"

using namespace std;

TEST_CASE(case_2) {
    vector tests = {
        Op(to_opcode(0x01), 10),
        Op(to_opcode(0x01), 20),
        Op(to_opcode(0x04), std::nullopt),
        Op(to_opcode(0xFE), 0x05),
    };
    
    Stack stack;
    Vm vm = Vm(tests, stack);
    vm.execute();
    vm.stackDump();

    ASSERT_EQ(stack.values_[0], 20);
    ASSERT_EQ(stack.values_[1], 10);
}
