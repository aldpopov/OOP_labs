#include <gtest/gtest.h>
#include "Rhombus.h"
#include "../src/lab4/Jarvis.cpp"
#include "../src/lab4/Point.cpp"
#include "../src/lab4/Figure.cpp"
#include "../src/lab4/Rhombus.cpp"
#include "../src/lab4/Pentagon.cpp"
#include "../src/lab4/Hexagon.cpp"
#include "../src/lab4/Array.cpp"

TEST(rhomb_test_1, list_initializer_test) {
    Rhombus<double> rhomb({Point<double>(3, 0), Point<double>(0, 2), Point<double>(-3, 0), Point<double>(0, -2)});

    auto& vertices = rhomb.get_points();

    ASSERT_EQ(vertices[0], Point<double>(-3.0, 0.0));
    ASSERT_EQ(vertices[1], Point<double>(0.0, -2.0));
    ASSERT_EQ(vertices[2], Point<double>(3.0, 0.0));
    ASSERT_EQ(vertices[3], Point<double>(0.0, 2.0));
}

TEST(rhomb_test_2, list_initializer_error_test) {
    ASSERT_THROW(Rhombus<double>({Point<double>(3, 0), Point<double>(0, 2)}), std::invalid_argument);
}

TEST(rhomb_test_3, sides_check_test) {
    ASSERT_THROW(Rhombus<double>({Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2)}), std::invalid_argument);
}

TEST(rhomb_test_4, area_center_test) {
    Rhombus<double> rhomb({Point<double>(3, 0), Point<double>(0, 2), Point<double>(-3, 0), Point<double>(0, -2)});

    Point<double> center = *rhomb.center();

    ASSERT_EQ(double(rhomb), 12);
    ASSERT_EQ(center, Point<double>(0.0, 0.0));
}