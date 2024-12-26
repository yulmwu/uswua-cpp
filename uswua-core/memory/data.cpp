#include "data.hpp"
#include "error.hpp"

Value Data::get(Pointer ptr) {
    if (ptr >= this->data.size()) {
        throw BytecodeError(BytecodeError::BytecodeErrorKind::IndexOutOfRange, ptr);
    }
    return this->data.back();
}

