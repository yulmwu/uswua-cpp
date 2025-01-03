#ifndef stack_hpp
#define stack_hpp

#include <vector>
#include "opcode.hpp"

struct Stack {
    std::vector<Value> data;

    Stack() = default;

    void push(Value);
    Value pop(Pointer);
    Value back(Pointer);
};

#endif /* stack_hpp */
