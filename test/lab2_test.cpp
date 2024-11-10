#include <gtest/gtest.h>
#include <Octal.h>

TEST(test_1, Default_constructor) {
    Octal octal;
    ASSERT_EQ(octal.get_size(), 0);
}

TEST(test_02, Size_constructor) {
    Octal octal(5, 3);
    ASSERT_EQ(octal.get_size(), 5);
}

TEST(test_03, Initializer_list_constructor) {
    Octal octal({1, 2, 3, 4});
    ASSERT_EQ(octal.get_size(), 4);
}

TEST(test_04, String_constructor) {
    Octal octal("1234");
    ASSERT_EQ(octal.get_size(), 4);
}

TEST(test_05, Copy_constructor) {
    Octal octal_1({1, 2, 3, 4});
    Octal octal_2(octal_1);
    ASSERT_EQ(octal_2.get_size(), 4);
}

TEST(test_06, Move_constructor) {
    Octal octal_1({1, 2, 3, 4});
    Octal octal_2(std::move(octal_1));
    ASSERT_EQ(octal_2.get_size(), 4);
}

TEST(test_07, Addition) {
    Octal octal_1("123");
    Octal octal_2("456");
    Octal result = octal_1 + octal_2;
    Octal right_result("601");
    ASSERT_TRUE(result == right_result);
}

TEST(test_08, Subtraction) {
    Octal octal_1("456");
    Octal octal_2("123");
    Octal result = octal_1 - octal_2;
    Octal right_result("333");
    ASSERT_TRUE(result == right_result);
}

TEST(test_09, Greater_than) {
    Octal octal_1("456");
    Octal octal_2("123");
    ASSERT_TRUE(octal_1 > octal_2);
}

TEST(test_10, Less_than) {
    Octal octal_1("123");
    Octal octal_2("456");
    ASSERT_TRUE(octal_1 < octal_2);
}

TEST(test_11, Equality) {
    Octal octal_1("123");
    Octal octal_2("123");
    ASSERT_TRUE(octal_1 == octal_2);
}