#include "Pentagon.h"
#include <gtest/gtest.h>
#include "../src/lab4/Jarvis.cpp"
#include "../src/lab4/Point.cpp"
#include "../src/lab4/Figure.cpp"
#include "../src/lab4/Rhombus.cpp"
#include "../src/lab4/Pentagon.cpp"
#include "../src/lab4/Hexagon.cpp"
#include "../src/lab4/Array.cpp"

TEST(penta_test_1, list_initializer_test) {
    Pentagon<double> penta{Point<double>(-4, 1), Point<double>(-2, 4), Point<double>(2, 5), Point<double>(5, 2), Point<double>(0, -3)};

    auto& vertices = penta.get_points();

    ASSERT_EQ(vertices[0], Point<double>(-4.0, 1.0));
    ASSERT_EQ(vertices[1], Point<double>(0.0, -3.0));
    ASSERT_EQ(vertices[2], Point<double>(5.0, 2.0));
    ASSERT_EQ(vertices[3], Point<double>(2.0, 5.0));
    ASSERT_EQ(vertices[4], Point<double>(-2.0, 4.0));
}

TEST(penta_test_2, list_initializer_error_test) {
    ASSERT_THROW(Pentagon<double>({Point<double>(3, 0), Point<double>(0, 2)}), std::invalid_argument);
}

TEST(penta_test_3, area_center_test) {
    Pentagon<double> penta{Point<double>(-4, 1), Point<double>(-2, 4), Point<double>(2, 5), Point<double>(5, 2), Point<double>(0, -3)};

    //double area = double(penta);
    Point center = *penta.center();

    //ASSERT_EQ(double(penta), 40.0);
    ASSERT_EQ(center, Point<double>(0.2, 1.8));
}