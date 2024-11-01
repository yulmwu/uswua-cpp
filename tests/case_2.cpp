#include <iostream>
#include <vector>
#include "tests.cpp"

using namespace std;

TEST_CASE(case_2) {
    vector tests = {
        Op(to_opcode(0x01), 10)
    };
    
    Stack stack;
    auto *vm = new Vm(tests, stack);
    vm->execute();

    ASSERT_EQ(stack.values_[0], 10);
}
