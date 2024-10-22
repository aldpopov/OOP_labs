#include "Point.h"
#include <gtest/gtest.h>

TEST(point_test_1, constructor_test) {
    Point point(1.4, 2);

    ASSERT_EQ(point.x, 1.4);
    ASSERT_EQ(point.y, 2);
}

TEST(point_test_2, abs_test) {
    Point point(4.0, 3.0);
    double absolute;

    absolute = point.abs();

    ASSERT_EQ(absolute, 5.0); 
}

TEST(point_test_3, sum_test) {
    Point point_1(0.1, 4.2);
    Point point_2(-0.1, 0.2);

    Point sum = point_1 + point_2;

    ASSERT_EQ(sum, Point(0.0, 4.4));
}

TEST(point_test_4, subtraction_test) {
    Point point_1(0.1, 4.2);
    Point point_2(-0.1, 0.2);

    Point sum = point_1 - point_2;

    ASSERT_EQ(sum, Point(0.2, 4.0));
}

TEST(point_test_5, mult_test) {
    Point point_1(1.0, -3.0);
    Point point_2(2.0, 4.0);

    double mult = point_1 * point_2;

    ASSERT_EQ(mult, -10.0);
}