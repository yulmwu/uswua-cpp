#include <iostream>
#include <vector>

#include "tests.cpp"
#include "../uswua-core/opcode.hpp"
#include "../uswua-core/vm.hpp"
#include "../uswua-core/memory/memory.hpp"

using namespace std;

TEST_CASE(case_2) {
    vector tests = {
        Op(to_opcode(0x01), 10),
        Op(to_opcode(0x01), 20),
        Op(to_opcode(0x04), std::nullopt),
        Op(to_opcode(0xFE), 0x05),
    };
    
    Stack stack;
    Heap heap;
    Data data;

    Vm vm = Vm(tests, stack, heap, data);
    vm.execute();
    vm.stackDump();

    ASSERT_EQ(stack.data[0], 20);
    ASSERT_EQ(stack.data[1], 10);
}
