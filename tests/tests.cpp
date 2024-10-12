#include <iostream>

#define TEST_CASE(name)                       \
    void test_##name()

#define RUN_TEST(name)                        \
    do {                                      \
        std::cout << "Running test: " #name  \
                  << std::endl;              \
        test_##name();                        \
        std::cout << "Test " #name " passed." \
                  << std::endl;              \
    } while (0)

#define ASSERT_EQ(x, y)                         \
    do {                                        \
        if ((x) != (y)) {                      \
            std::cerr << "Assertion failed: " \
                      << #x << " == " << #y   \
                      << ", at " << __FILE__   \
                      << ":" << __LINE__      \
                      << std::endl;            \
            std::exit(EXIT_FAILURE);           \
        }                                       \
    } while (0)

TEST_CASE(case_example) {
    ASSERT_EQ(1, 1);
}

void TESTS_RUN_ALL() {
    RUN_TEST(case_example);
}
