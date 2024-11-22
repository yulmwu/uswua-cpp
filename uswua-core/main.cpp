#include <iostream>
#include <uswua-cpp/opcode>

int main(int argc, const char * argv[]) {
    Op op(Opcode::PUSH, std::nullopt);
    std::cout << op << std::endl;
    return 0;
}
