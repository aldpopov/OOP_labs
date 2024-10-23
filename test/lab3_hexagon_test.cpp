#include "Hexagon.h"
#include <gtest/gtest.h>
#include "Point.h"

TEST(hex_test_1, list_initializer_test) {
    Hexagon hex{Point(2, 0), Point(1, 2), Point(-1, 2), Point(-2, 0), Point(-1, -2), Point(1, -2)};

    Point* vertices = hex.get_points();

    ASSERT_EQ(vertices[0], Point(-2.0, 0.0));
    ASSERT_EQ(vertices[1], Point(-1.0, -2.0));
    ASSERT_EQ(vertices[2], Point(1.0, -2.0));
    ASSERT_EQ(vertices[3], Point(2.0, 0.0));
    ASSERT_EQ(vertices[4], Point(1.0, 2.0));
    ASSERT_EQ(vertices[5], Point(-1.0, 2.0));
}

TEST(hex_test_2, list_initializer_error_test) {
    ASSERT_THROW(Hexagon({Point(3, 0), Point(0, 2)}), std::invalid_argument);
}

TEST(hex_test_3, area_center_test) {
    Hexagon hex{Point(2, 0), Point(1, 2), Point(-1, 2), Point(-2, 0), Point(-1, -2), Point(1, -2)};
    //double area = double(hex);
    Point center = *hex.center();

    //ASSERT_EQ(area, 12.0);
    ASSERT_EQ(center, Point(0.0, 0.0));
}