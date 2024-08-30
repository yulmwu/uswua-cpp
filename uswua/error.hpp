#ifndef ERROR_HPP
#define ERROR_HPP

#include "stdexcept"

class BytecodeError : public std::runtime_error {
public:
    enum class BytecodeErrorKind {
        EmptyStack,
        InvalidOpcode,
        EmptyOpcode
    };

    explicit BytecodeError(BytecodeErrorKind kind);

private:
    BytecodeErrorKind kind_;
};

#endif /* ERROR_HPP */
