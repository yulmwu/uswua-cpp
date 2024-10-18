#include <iostream>
#include <vector>
#include "tests.cpp"

using namespace std;

TEST_CASE(case_2) {
    vector tests = {
        Op(to_opcode(0x01), 10)
    };
    
    auto *vm = new Vm(tests);
    vm->execute();
}
