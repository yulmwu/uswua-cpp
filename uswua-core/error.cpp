#include "error.hpp"

using namespace std;

BytecodeError::BytecodeError(BytecodeErrorKind kind, Pointer ptr)
    : kind_(kind), ptr(ptr) {}

const char* BytecodeError::what() const noexcept {
    switch (this->kind_) {
        case BytecodeErrorKind::EmptyStack:
            return "Empty Stack";
        case BytecodeErrorKind::InvalidOpcode:
            return "Invalid Opcode";
        case BytecodeErrorKind::EmptyOperand:
            return "Empty Operand";
        case BytecodeErrorKind::NotFound:
            return "Not Found";
        case BytecodeErrorKind::EmptyCallStack:
            return "Empty CallStack";
        case BytecodeErrorKind::UnknownCallNo:
            return "Unknown Call Number";
        case BytecodeErrorKind::IdentifierNotFound:
            return "Identifier Not Found";
    }
}

Pointer BytecodeError::where() const noexcept {
    return this->ptr;
}
