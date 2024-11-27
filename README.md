### [ussua bytecode](https://github.com/yulmwu/ussua) project C++ porting.


| opcode  | hex    | description | operand | notation |
|---------|--------|-------------|---------|----------|
| `NOOP`  | `0x00` | Noop        |         |          |
| `PUSH`  | `0x01` | Push stack  | Value   | `stack <- operand` |
| `STORE` | `0x02` | Pop stack, store in heap | Heap address | `heap[address] = stack:pop` |
| `LOAD`  | `0x03` | Load from heap, push to stack | Heap address | `stack <- heap[operand]` |
| `ADD`   | `0x10` | Pop and add two values in the stack and push the values to the stack | | `stack <- stack:pop + stack:pop` |
| `SUB`   | `0x11` | Pop and subtract two values in the stack and push the values to the stack | | `stack <- stack:pop - stack:pop` |
| `MUL`   | `0x12` | Pop and multiple two values in the stack and push the values to the stack | | `stack <- stack:pop * stack:pop` |
| `DIV`   | `0x13` | Pop and divide two values in the stack and push the values to the stack | | `stack <- stack:pop / stack:pop` |
| `MOD`   | `0x14` | Pop and modulus two values in the stack and push the values to the stack | | `stack <- stack:pop % stack:pop` |
| `AND`   | `0x18` | Pop and `and` logical operation two values in the stack and push the values to the stack | | `stack <- stack:pop && stack:pop` |
| `OR`   | `0x19` | Pop and `or` logical operation two values in the stack and push the values to the stack | | `stack <- stack:pop` || stack:pop` |
| `XOR`   | `0x1A` | Pop and `xor` logical operation two values in the stack and push the values to the stack | | `stack <- stack:pop ^ stack:pop` |
| `NOT`   | `0x1B` | Pop and `not` logical operation value in the stack and push the values to the stack | | `stack <- !stack:pop` |
| `LSF`   | `0x1C` | Pop and left shift values in the stack and push the values to the stack | | `stack <- stack:pop << stack:pop` |
| `RSF`   | `0x1D` | Pop and right shift values in the stack and push the values to the stack | | `stack <- stack:pop << stack:pop` |
| `EQ`   | `0x20` | Pop and compare values equally in the stack and if true, push 1 to the stack | | `stack <- stack:pop == stack:pop` |
| `GT`   | `0x21` | Pop and compare if the first value is greater than the second, and if true, push 1 to the stack | | `stack <- stack:pop > stack:pop` |
| `LT`   | `0x22` | Pop and compare if the first value is less than the second, and if true, push 1 to the stack | | `stack <- stack:pop < stack:pop` |
| `GTE`  | `0x23` | Pop and compare if the first value is greater than or equal to the second, and if true, push 1 to the stack | | `stack <- stack:pop >= stack:pop` |
| `LTE`  | `0x24` | Pop and compare if the first value is less than or equal to the second, and if true, push 1 to the stack | | `stack <- stack:pop <= stack:pop` |
| `PROC` | `0x28` | Specify the length of the procedure, skip this length and execute. this instruction is used later when it is executed through CALL | Length of the procedure | `ptr = ptr + operand + 1(PROC)` |
| `CALL` | `0x29` | Backup the current pointer to the callstack and move it to the position of the procedure (PROC next pointer) | Pointer of the procedure's first instruction | `callstack <- ptr, ptr = operand` |
| `RET` | `0x2A` | Return to the pointer backed up to callstack | | `ptr = callstack:pop` |
| `JMP` | `0x2C` | Jump to the pointer | Pointer | `ptr = operand` |
| `JIF` | `0x2D` | Pop the stack, and if the value is 0 (false), jump to the pointer | Pointer | `if (stack:pop == 0) ptr = operand` |

