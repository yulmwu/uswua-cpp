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
        IdentifierNotFound,
        UnknownPreprocessor
    };

    explicit BytecodeError(BytecodeErrorKind kind, Pointer ptr)
        : kind_(kind), ptr(ptr) {}
    explicit BytecodeError(BytecodeErrorKind kind, Pointer ptr, Opcode opcode)
        : kind_(kind), ptr(ptr), opcode_(opcode) {}
    explicit BytecodeError(BytecodeErrorKind kind, Pointer ptr, std::string identifier)
        : kind_(kind), ptr(ptr), identifier_(identifier) {}
    explicit BytecodeError(BytecodeErrorKind kind, Pointer ptr, Pointer pointer)
        : kind_(kind), ptr(ptr), pointer_(pointer) {}

    virtual const char* what() const noexcept override;
    Pointer where() const noexcept;

private:
    mutable std::string message;

    BytecodeErrorKind kind_;
    std::optional<Opcode> opcode_;
    std::optional<std::string> identifier_;
    std::optional<Pointer> pointer_;
    Pointer ptr;
};

#endif /* ERROR_HPP */
