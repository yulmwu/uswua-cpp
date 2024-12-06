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
//    TESTS_RUN_ALL();
    
    auto code = R"(

)";
    
    try {
        Parser p = Parser(code);
        Instructions instructions = p.parse();
        
        Stack stack;
        Vm vm = Vm(instructions, stack);
    
        vm.execute();
        
        vm.stackDump();
    } catch (BytecodeError error) {
        cout << error.what() << endl;
        cout << error.where() << endl;
    }
    
    return 0;
}

