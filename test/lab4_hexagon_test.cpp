#include "Hexagon.h"
#include <gtest/gtest.h>
#include "../src/lab4/Jarvis.cpp"
#include "../src/lab4/Point.cpp"
#include "../src/lab4/Figure.cpp"
#include "../src/lab4/Rhombus.cpp"
#include "../src/lab4/Pentagon.cpp"
#include "../src/lab4/Hexagon.cpp"
#include "../src/lab4/Array.cpp"

TEST(hex_test_1, list_initializer_test) {
    Hexagon<double> hex{Point<double>(2, 0), Point<double>(1, 2), Point<double>(-1, 2), Point<double>(-2, 0), Point<double>(-1, -2), Point<double>(1, -2)};

    auto& vertices = hex.get_points();

    ASSERT_EQ(vertices[0], Point<double>(-2.0, 0.0));
    ASSERT_EQ(vertices[1], Point<double>(-1.0, -2.0));
    ASSERT_EQ(vertices[2], Point<double>(1.0, -2.0));
    ASSERT_EQ(vertices[3], Point<double>(2.0, 0.0));
    ASSERT_EQ(vertices[4], Point<double>(1.0, 2.0));
    ASSERT_EQ(vertices[5], Point<double>(-1.0, 2.0));
}

TEST(hex_test_2, list_initializer_error_test) {
    ASSERT_THROW(Hexagon<double>({Point<double>(3, 0), Point<double>(0, 2)}), std::invalid_argument);
}

TEST(hex_test_3, area_center_test) {
    Hexagon<double> hex{Point<double>(2, 0), Point<double>(1, 2), Point<double>(-1, 2), Point<double>(-2, 0), Point<double>(-1, -2), Point<double>(1, -2)};
    //double area = double(hex);
    Point<double> center = *hex.center();

    //ASSERT_EQ(area, 12.0);
    ASSERT_EQ(center, Point<double>(0.0, 0.0));
}