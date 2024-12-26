#include "error.hpp"
#include <sstream>

using namespace std;

const char* BytecodeError::what() const noexcept {
    stringstream ss;

    switch (this->kind_) {
        case BytecodeErrorKind::EmptyStack:
            ss << "Empty Stack";
            break;
        case BytecodeErrorKind::InvalidOpcode:
            ss << "Invalid Opcode";
            break;
        case BytecodeErrorKind::EmptyOperand:
            ss << "Empty Operand";
            break;
        case BytecodeErrorKind::NotFound:
            ss << "Not Found";
            break;
        case BytecodeErrorKind::EmptyCallStack:
            ss << "Empty CallStack";
            break;
        case BytecodeErrorKind::UnknownCallNo:
            ss << "Unknown Call Number";
            break;
        case BytecodeErrorKind::IndexOutOfRange:
            ss << "Index Out Of Range";
            break;
        case BytecodeErrorKind::IdentifierNotFound:
            ss << "Identifier Not Found";
            break;
        case BytecodeErrorKind::UnknownPreprocessor:
            ss << "Unknown Preprocessor";
            break;
    }
    
    if (this->opcode_) ss << ": " << this->opcode_.value();
    if (this->pointer_) ss << ": " << this->pointer_.value();
    if (this->identifier_) ss << ": " << this->identifier_.value();
    
    this->message = ss.str();
    return this->message.c_str();
}

Pointer BytecodeError::where() const noexcept {
    return this->ptr;
}
