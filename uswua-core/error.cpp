#include "error.hpp"

BytecodeError::BytecodeError(BytecodeErrorKind kind, Pointer ptr)
    : kind_(kind), ptr(ptr) {}

const char* BytecodeError::what() const noexcept {
    switch (this->kind_) {
        case BytecodeErrorKind::EmptyStack:
            return "EmptyStack";
        case BytecodeErrorKind::InvalidOpcode:
            return "InvalidOpcode";
        case BytecodeErrorKind::EmptyOperand:
            return "EmptyOperand";
        case BytecodeErrorKind::NotFound:
            return "NotFound";
        case BytecodeErrorKind::EmptyCallStack:
            return "EmptyCallStack";
        case BytecodeErrorKind::UnknownCallNo:
            return "UnknownCallNo";
    }
}

Pointer BytecodeError::where() const noexcept {
    return this->ptr;
}
