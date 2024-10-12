#include <iostream>

#define TEST_CASE(name)                       \
    void test_##name()

#define RUN_TEST(name)                        \
    do {                                      \
        try { \
            std::cout << "🔁 ----- Running test: " #name  \
                      << std::endl;              \
            test_##name();                        \
            std::cout << "✅ ----- Test " #name " passed." \
                      << std::endl;              \
        } catch (const BytecodeError& e) { \
            cerr << "❌ ByteCode error: " << e.what() << " on (ptr)" << e.where() << endl; \
        } \
    } while (0)

#define ASSERT_EQ(x, y)                         \
    do {                                        \
        if ((x) != (y)) {                      \
            std::cerr << "❌ Assertion failed at " \
                      << __FILE__ << ":" << __LINE__      \
                      << std::endl;            \
            std::cerr << " => " << #x << " == " << #y \
                      << std::endl;   \
            std::cerr << " => " << (x) << " == " << (y) \
                      << std::endl;   \
            std::exit(EXIT_FAILURE);           \
        }                                       \
    } while (0)
