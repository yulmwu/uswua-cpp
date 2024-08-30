#include "stack.hpp"
#include "error.hpp"

void Stack::push(Value value) {
    this->values_.push_back(value);
}

Value Stack::pop() {
    if (this->values_.empty()) {
        throw BytecodeError(BytecodeError::BytecodeErrorKind::EmptyStack);
    }
    Value value = this -> values_.back();
    this->values_.pop_back();
    return value;
}
