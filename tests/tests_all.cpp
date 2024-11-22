#include "tests.cpp"

#include "case_1.cpp"
#include "case_2.cpp"
#include "case_b2i.cpp"

void TESTS_RUN_ALL() {
    RUN_TEST(case_1);
    RUN_TEST(case_2);
    RUN_TEST(case_b2i);
}
