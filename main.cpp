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
#STARTPTR 0

PUSH 0x00           ; r = 0
STORE r             ;

PUSH 0x01           ; i = 1
STORE i             ;

#pstart F
PROC F              ; def f():
    LOAD r          ;
    LOAD i          ;
    ADD             ;
    STORE r         ;     r = r + i

    LOAD i          ;
    PUSH 0x01       ;
    ADD             ;
    STORE i         ;     i = i + 1

    LOAD i          ;
    DLOAD 0x00      ;
    GTE             ;
    JIF _CASE_FALSE ;    if 10 >= i:

_CASE_TRUE:
    CALL 4          ;       f()

_CASE_FALSE:
    RET             ;       else: return
#pend F

CALL F              ; f()

LOAD r
LOAD i
)";
    
    try {
        Parser p = Parser(code);
        Instructions instructions = p.parse();

        Stack stack;
        Heap heap;
        Data data({ 0x0A });

        Vm vm = Vm(instructions, stack, heap, data, p.vm_options);

        vm.execute();

        cout << vm.stackDump() << endl;
        cout << "-----" << endl;
        cout << vm.heapDump() << endl;
    } catch (BytecodeError error) {
        cout << error.what() << " at " << error.where() << endl;
    }
    
    return 0;
}

