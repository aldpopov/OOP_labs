#include "Pentagon.h"
#include <gtest/gtest.h>
#include "Point.h"

TEST(penta_test_1, list_initializer_test) {
    Pentagon penta{Point(-4, 1), Point(-2, 4), Point(2, 5), Point(5, 2), Point(0, -3)};

    Point* vertices = penta.get_points();

    ASSERT_EQ(vertices[0], Point(-4.0, 1.0));
    ASSERT_EQ(vertices[1], Point(0.0, -3.0));
    ASSERT_EQ(vertices[2], Point(5.0, 2.0));
    ASSERT_EQ(vertices[3], Point(2.0, 5.0));
    ASSERT_EQ(vertices[4], Point(-2.0, 4.0));
}

TEST(penta_test_2, list_initializer_error_test) {
    ASSERT_THROW(Pentagon({Point(3, 0), Point(0, 2)}), std::invalid_argument);
}

TEST(penta_test_3, area_center_test) {
    Pentagon penta{Point(-4, 1), Point(-2, 4), Point(2, 5), Point(5, 2), Point(0, -3)};

    double area = double(penta);
    Point center = *penta.center();

    ASSERT_EQ(area, 40.0);
    ASSERT_EQ(center, Point(0.2, 1.8));
}