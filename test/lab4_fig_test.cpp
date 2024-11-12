#include "Figure.h"
#include <gtest/gtest.h>
#include "Point.h"
#include "../src/lab4/Jarvis.cpp"
#include "../src/lab4/Point.cpp"
#include "../src/lab4/Figure.cpp"
#include "../src/lab4/Rhombus.cpp"
#include "../src/lab4/Pentagon.cpp"
#include "../src/lab4/Hexagon.cpp"
#include "../src/lab4/Array.cpp"


TEST(fig_test_1, default_constructor) {
    Figure<double> fig;

    ASSERT_EQ(fig.size(), 0);
}

TEST(fig_test_2, size_initialization) {
    Figure<double> fig(5);

    ASSERT_EQ(fig.size(), 5);
}

TEST(fig_test_3, list_initializer) {
    Figure<double> fig({Point<double>(1, 4), Point<double>(-4, 3.1), Point<double>(5, 0)});

    auto& vertices = fig.get_points();
    size_t size = fig.size();

    ASSERT_EQ(vertices[0], Point<double>(-4, 3.1));
    ASSERT_EQ(vertices[1], Point<double>(5, 0));
    ASSERT_EQ(vertices[2], Point<double>(1, 4));
}

TEST(fig_test_4, area_center_test) {
    Figure<double> fig({Point<double>(0, 0), Point<double>(4, 2), Point<double>(3, 2), Point<double>(1, 2)});

    Point<double> center = *fig.center();
    
    ASSERT_EQ(double(fig), 3.0);
    ASSERT_EQ(center, Point<double>(2, 1.5));
}

TEST(fig_test_5, convex_hull_test) {
    Figure<double> fig({Point<double>(-2, 1), Point<double>(3, -1), Point<double>(1, 3), Point<double>(0, -3)});

    auto& vertices = fig.get_points();

    ASSERT_EQ(vertices[0], Point<double>(-2, 1));
    ASSERT_EQ(vertices[1], Point<double>(0, -3));
    ASSERT_EQ(vertices[2], Point<double>(3, -1));
    ASSERT_EQ(vertices[3], Point<double>(1, 3));
}

TEST(fig_test_6, convex_hull_error_test) {

    ASSERT_THROW(Figure<double>({Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(3, 1)}), std::invalid_argument);
}

TEST(fig_test_7, copy) {
    Figure<double> fig({Point<double>(-2, 1), Point<double>(3, -1), Point<double>(1, 3), Point<double>(0, -3)});
    Figure<double> fig_2;

    fig_2 = fig;
    auto& vertices = fig_2.get_points();

    ASSERT_EQ(vertices[0], Point<double>(-2, 1));
    ASSERT_EQ(vertices[1], Point<double>(0, -3));
    ASSERT_EQ(vertices[2], Point<double>(3, -1));
    ASSERT_EQ(vertices[3], Point<double>(1, 3));
}