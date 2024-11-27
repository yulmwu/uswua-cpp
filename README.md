### [ussua bytecode](https://github.com/yulmwu/ussua) project C++ porting.

        case 0x00: return Opcode::NOOP;
        case 0x01: return Opcode::PUSH;
        case 0x02: return Opcode::STORE;
        case 0x03: return Opcode::LOAD;
        case 0x10: return Opcode::ADD;
        case 0x11: return Opcode::SUB;
        case 0x12: return Opcode::MUL;
        case 0x13: return Opcode::DIV;
        case 0x14: return Opcode::MOD;
        case 0x18: return Opcode::AND;
        case 0x19: return Opcode::OR;
        case 0x1A: return Opcode::XOR;
        case 0x1B: return Opcode::NOT;
        case 0x1C: return Opcode::LSF;
        case 0x1D: return Opcode::RSF;
        case 0x20: return Opcode::EQ;
        case 0x21: return Opcode::GT;
        case 0x22: return Opcode::LT;
        case 0x23: return Opcode::GTE;
        case 0x24: return Opcode::LTE;
        case 0x28: return Opcode::PROC;
        case 0x29: return Opcode::CALL;
        case 0x2A: return Opcode::RET;
        case 0x2C: return Opcode::JMP;
        case 0x2D: return Opcode::JIF;
        case 0xFE: return Opcode::DBG;
        case 0xFF: return Opcode::EXIT;
        
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
| `OR`   | `0x19` | Pop and `or` logical operation two values in the stack and push the values to the stack | | `stack <- stack:pop || stack:pop` |
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

