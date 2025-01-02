#ifndef html_logger_hpp
#define html_logger_hpp

#include <iostream>
#include <vector>

#include "../uswua-core/opcode.hpp"
#include "../uswua-core/memory/memory.hpp"

enum class LogKind {
    OK,
    ERROR,
    HALT
};

struct LogMessage {
    Op op;
    LogKind kind;
    Pointer pointer;
    Pointer steps;
    std::string stack_dump;
    std::string heap_dump;
    
    LogMessage(Op op, LogKind kind, Pointer pointer, Pointer steps, std::string stack_dump, std::string heap_dump)
    : op(op), kind(kind), pointer(pointer), steps(steps), stack_dump(stack_dump), heap_dump(heap_dump) {}
};

class HTMLLogger {
public:
    std::vector<std::string> logs;
    
    HTMLLogger() = default;
    HTMLLogger(std::vector<LogMessage> logs) {
        for (auto i : logs) this->write(i);
    }
    
    void write(LogMessage log);
    std::string html();
};

#endif /* html_logger_hpp */
