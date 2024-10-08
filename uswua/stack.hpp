#ifndef stack_hpp
#define stack_hpp

#include "vector"
#include "opcode.hpp"

class Stack {
public:
    std::vector<Value> values_;

    Value pop(Pointer ptr);

    Stack() = default;

    void push(Value value);
};

#endif /* stack_hpp */
