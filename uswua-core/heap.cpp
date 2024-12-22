#include "heap.hpp"

void Heap::insert(Pointer pointer, Value value) {
    this->data.insert({ pointer, value });
}

void Heap::insert_or_assign(Pointer pointer, Value value) {
    this->data.insert_or_assign(pointer, value);
}

void Heap::erase(Pointer pointer, Pointer ptr) {
    if (this->data.find(pointer) != data.end()) {
        this->data.erase(pointer);
    } else {
        throw BytecodeError(BytecodeError::BytecodeErrorKind::NotFound, ptr, pointer);
    }
}

void Heap::assign(Pointer pointer, Value value, Pointer ptr) {
    if (this->data.find(pointer) != data.end()) {
        this->data[pointer] = value;
    } else {
        throw BytecodeError(BytecodeError::BytecodeErrorKind::NotFound, ptr, pointer);
    }
}

Value Heap::get(Pointer pointer, Pointer ptr) {
    if (this->data.find(pointer) != data.end()) {
        return this->data[pointer];
    } else {
        throw BytecodeError(BytecodeError::BytecodeErrorKind::NotFound, ptr, pointer);
    }
}
