//
//  data.hpp
//  uswua-cpp
//
//  Created by Kim Jun Young on 12/26/24.
//

#ifndef data_hpp
#define data_hpp

#include <vector>
#include "opcode.hpp"
#include "error.hpp"

struct Data {
    std::vector<Value> data;

    Data() = default;
    Data(std::vector<Value> data): data(data) {}

    Value get(Pointer);
};

#endif /* data_hpp */
