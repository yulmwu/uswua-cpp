#include "stack.hpp"
#include "error.hpp"

void Stack::push(Value value) {
    values_.push_back(value);
}

Value Stack::pop() {
    if (values_.empty()) {
        throw BytecodeError(BytecodeError::BytecodeErrorKind::EmptyStack);
    }
    Value value = values_.back();
    values_.pop_back();
    return value;
}
