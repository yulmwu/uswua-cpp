#ifndef ERROR_HPP
#define ERROR_HPP

#include <stdexcept>
#include <string>
#include "opcode.hpp"

class BytecodeError : public std::exception {
public:
    enum class BytecodeErrorKind {
        EmptyStack,
        InvalidOpcode,
        EmptyOperand,
        NotFound,
        EmptyCallStack,
        UnknownCallNo,
    };

    explicit BytecodeError(BytecodeErrorKind kind, Pointer ptr);
    virtual const char* what() const noexcept override;
    Pointer where() const noexcept;

private:
    BytecodeErrorKind kind_;
    Pointer ptr;
};

#endif /* ERROR_HPP */
