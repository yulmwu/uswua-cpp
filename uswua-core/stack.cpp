#include "stack.hpp"
#include "error.hpp"

void Stack::push(Value value) {
    this->data.push_back(value);
}

Value Stack::pop(Pointer ptr) {
    if (this->data.empty()) {
        throw BytecodeError(BytecodeError::BytecodeErrorKind::EmptyStack, ptr);
    }
    auto value = this->data.back();
    this->data.pop_back();
    return value;
}
