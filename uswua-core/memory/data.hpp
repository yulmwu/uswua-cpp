#ifndef data_hpp
#define data_hpp

#include <vector>
#include "opcode.hpp"
#include "error.hpp"

struct Data {
    std::vector<Value> data;

    Data() = default;
    Data(std::vector<Value> data): data(data) {}

    void push(Value);
    Value get(Pointer, Pointer);
};

#endif /* data_hpp */
