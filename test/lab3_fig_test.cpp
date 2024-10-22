#include "Figure.h"
#include <gtest/gtest.h>
#include "Point.h"


TEST(fig_test_1, default_constructor) {
    Figure fig;

    ASSERT_EQ(fig.size(), 0);
}

TEST(fig_test_2, size_initialization) {
    Figure fig(5);

    ASSERT_EQ(fig.size(), 5);
}

TEST(fig_test_3, list_initializer) {
    Figure fig({Point(1, 4), Point(-4, 3.1), Point(5, 0)});

    Point* vertices = fig.get_points();
    size_t size = fig.size();

    ASSERT_EQ(vertices[0], Point(-4, 3.1));
    ASSERT_EQ(vertices[1], Point(5, 0));
    ASSERT_EQ(vertices[2], Point(1, 4));
}

TEST(fig_test_4, area_center_test) {
    Figure fig({Point(0, 0), Point(4, 0), Point(3, 2), Point(1, 2)});

    double area = double(fig);
    Point center = *fig.center();
    
    ASSERT_EQ(area, 7.0);
    ASSERT_EQ(center, Point(2, 1));
}

TEST(fig_test_5, convex_hull_test) {
    Figure fig({Point(-2, 1), Point(3, -1), Point(1, 3), Point(0, -3)});

    Point* vertices = fig.get_points();

    ASSERT_EQ(vertices[0], Point(-2, 1));
    ASSERT_EQ(vertices[1], Point(0, -3));
    ASSERT_EQ(vertices[2], Point(3, -1));
    ASSERT_EQ(vertices[3], Point(1, 3));
}

TEST(fig_test_6, convex_hull_error_test) {

    ASSERT_THROW(Figure({Point(0, 0), Point(4, 0), Point(3, 2), Point(3, 1)}), std::invalid_argument);
}

TEST(fig_test_7, copy) {
    Figure fig({Point(-2, 1), Point(3, -1), Point(1, 3), Point(0, -3)});
    Figure fig_2;

    fig_2 = fig;
    Point* vertices = fig_2.get_points();

    ASSERT_EQ(vertices[0], Point(-2, 1));
    ASSERT_EQ(vertices[1], Point(0, -3));
    ASSERT_EQ(vertices[2], Point(3, -1));
    ASSERT_EQ(vertices[3], Point(1, 3));
}

TEST(fig_test_8, move) {
    Figure fig({Point(-2, 1), Point(3, -1), Point(1, 3), Point(0, -3)});
    Figure fig_2;
    Point* vertices_1 = fig.get_points();

    fig_2 = std::move(fig);
    Point* vertices_2 = fig_2.get_points();

    ASSERT_EQ(vertices_1, vertices_2);
}