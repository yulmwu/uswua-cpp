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
| `PUSH`  | `0x01` | Push stack  | value   | `stack <- operand` |
| `STORE` | `0x02` | Pop stack, store in heap | heap address | `heap[address] = stack:pop` |
| `LOAD`  | `0x03` | Load from heap, push to stack | heap address | `stack <- heap[operand]` |
| `ADD`   | `0x10` | Pop and add two values in the stack and push the values to the stack | | `stack <- stack:pop + stack:pop` |
| `SUB`   | `0x11` | Pop and subtract two values in the stack and push the values to the stack | | `stack <- stack:pop - stack:pop` |
| `MUL`   | `0x11` | Pop and multiple two values in the stack and push the values to the stack | | `stack <- stack:pop * stack:pop` |
| `DIV`   | `0x11` | Pop and divide two values in the stack and push the values to the stack | | `stack <- stack:pop / stack:pop` |
| `MOD`   | `0x11` | Pop and modulus two values in the stack and push the values to the stack | | `stack <- stack:pop % stack:pop` |
