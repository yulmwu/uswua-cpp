#include <iostream>
#include <vector>

#include "uswua-core/opcode.hpp"
#include "uswua-core/error.hpp"
#include "uswua-core/vm.hpp"
#include "uswua-utils/b2i.hpp"

#include "uswua-utils/parser.hpp"

#include "tests/tests_all.cpp"

using namespace std;

int main() {
    auto code = R"(
    push 0x01
    store 0x00
)";
    
    Parser p = Parser(code);
    auto instructions = p.parse();
    
    for (auto i : instructions) {
//        cout << i << endl;
    }

    return 0;
}

