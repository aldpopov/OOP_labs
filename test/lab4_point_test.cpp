#include "Point.h"
#include <gtest/gtest.h>
#include "../src/lab4/Jarvis.cpp"
#include "../src/lab4/Point.cpp"
#include "../src/lab4/Figure.cpp"
#include "../src/lab4/Rhombus.cpp"
#include "../src/lab4/Pentagon.cpp"
#include "../src/lab4/Hexagon.cpp"
#include "../src/lab4/Array.cpp"

TEST(point_test_1, constructor_test) {
    Point<double> point(1.4, 2);

    ASSERT_EQ(point.x, 1.4);
    ASSERT_EQ(point.y, 2);
}

TEST(point_test_2, abs_test) {
    Point<double> point(4.0, 3.0);
    double absolute;

    absolute = point.abs();

    ASSERT_EQ(absolute, 5.0); 
}

TEST(point_test_3, sum_test) {
    Point<double> point_1(0.1, 4.2);
    Point<double> point_2(-0.1, 0.2);

    Point<double> sum = point_1 + point_2;

    ASSERT_EQ(sum, Point(0.0, 4.4));
}

TEST(point_test_4, subtraction_test) {
    Point<double> point_1(0.1, 4.2);
    Point<double> point_2(-0.1, 0.2);

    Point<double> sum = point_1 - point_2;

    ASSERT_EQ(sum, Point(0.2, 4.0));
}

TEST(point_test_5, mult_test) {
    Point<double> point_1(1.0, -3.0);
    Point<double> point_2(2.0, 4.0);

    double mult = point_1 * point_2;

    ASSERT_EQ(mult, -10.0);
}