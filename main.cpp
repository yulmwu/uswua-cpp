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
/* 00 */    PUSH 0x00           ; r = 0
/* 01 */    STORE r             ;
/* 02 */    PUSH 0x01           ; i = 1
/* 03 */    STORE i             ;
/* 04 */    PROC 14             ; def f():
/* 05 */        LOAD r          ;
/* 06 */        LOAD i          ;
/* 07 */        ADD             ;
/* 08 */        STORE r         ;     r = r + i
/* 09 */        LOAD i          ;
/* 10 */        PUSH 0x01       ;
/* 11 */        ADD             ;
/* 12 */        STORE i         ;     i = i + 1
/* 13 */        LOAD i          ;
/* 14 */        PUSH 0x0A       ;
/* 15 */        GTE             ;
/* 16 */        JIF [+2]        ;    if 10 >= i:
/* 17 */        CALL 4          ;        f()
/* 18 */        RET             ;    else:
/* 19 */    CALL 4              ; f()
/* 20 */    LOAD r              ;
/* 21 */    PUSH 1              ;
/* 22 */    VMCALL 0x01         ; println(r)
/* 22 */    POP                 ;
/* 23 */    LOAD i              ;
/* 24 */    PUSH 1              ;
/* 25 */    VMCALL 0x01         ; println(i)
/* 26 */    POP                 ;

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

