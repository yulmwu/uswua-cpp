#include "error.hpp"

BytecodeError::BytecodeError(BytecodeErrorKind kind)
    : std::runtime_error("Bytecode error"), kind_(kind) {}
