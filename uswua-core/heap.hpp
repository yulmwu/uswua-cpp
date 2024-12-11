#ifndef heap_hpp
#define heap_hpp

#include <map>
#include "opcode.hpp"
#include "error.hpp"

class Heap {
public:
    std::map<Pointer, Value> data;

    void insert(Pointer, Value);
    void insert_or_assign(Pointer, Value);
    void erase(Pointer, Pointer);
    void assign(Pointer, Value, Pointer);
    Value get(Pointer, Pointer);

    Heap() = default;
};


#endif /* heap_hpp */
