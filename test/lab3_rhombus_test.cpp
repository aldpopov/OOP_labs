#include "Rhombus.h"
#include <gtest/gtest.h>
#include "Point.h"

TEST(rhomb_test_1, list_initializer_test) {
    Rhombus rhomb({Point(3, 0), Point(0, 2), Point(-3, 0), Point(0, -2)});

    Point* vertices = rhomb.get_points();

    ASSERT_EQ(vertices[0], Point(-3.0, 0.0));
    ASSERT_EQ(vertices[1], Point(0.0, -2.0));
    ASSERT_EQ(vertices[2], Point(3.0, 0.0));
    ASSERT_EQ(vertices[3], Point(0.0, 2.0));
}

TEST(rhomb_test_2, list_initializer_error_test) {
    ASSERT_THROW(Rhombus({Point(3, 0), Point(0, 2)}), std::invalid_argument);
}

TEST(rhomb_test_3, sides_check_test) {
    ASSERT_THROW(Rhombus({Point(0, 0), Point(4, 0), Point(3, 2), Point(1, 2)}), std::invalid_argument);
}

TEST(rhomb_test_4, area_center_test) {
    Rhombus rhomb({Point(3, 0), Point(0, 2), Point(-3, 0), Point(0, -2)});

    Point center = *rhomb.center();

    ASSERT_EQ(double(rhomb), 12);
    ASSERT_EQ(center, Point(0.0, 0.0));
}