#include "data.hpp"
#include "error.hpp"

void Data::push(Value value) {
    this->data.push_back(value);
}

Value Data::get(Pointer addr, Pointer ptr) {
    if (addr >= this->data.size()) {
        throw BytecodeError(BytecodeError::BytecodeErrorKind::IndexOutOfRange, ptr, addr);
    }
    return this->data[addr];
}

