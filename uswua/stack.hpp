#ifndef stack_hpp
#define stack_hpp

#include "vector"
#include "opcode.hpp"

class Stack {
public:
    Value pop();

    Stack() = default;

    void push(Value value);
private:
    std::vector<Value> values_;
};

#endif /* stack_hpp */
