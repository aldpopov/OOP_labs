#include "Pentagon.h"
#include "Jarvis.h"

Pentagon::Pentagon() : Figure(5) {}

Pentagon::Pentagon(const Pentagon& other) : Figure(other) {}

Pentagon::Pentagon(Pentagon&& other) noexcept : Figure(other) {}

void Pentagon::check() {
    if(vertex_quantity != 5) {
        throw std::invalid_argument("It is not a pentagon.");
    }
    Point* hull = convex_hull(*this);
    int hull_size = hull[0].x;
    if(hull_size != vertex_quantity) {
        throw std::invalid_argument("It is not a convex hexagon.");
    } else {
        for(size_t i = 0; i < hull_size; i++) {
            set_point(hull[i + 1], i);
        }
    }
}

Pentagon::Pentagon(const std::initializer_list<Point>& list) {
    vertex_quantity = list.size();
    vertices = new Point[vertex_quantity];

    size_t i = 0;
    for (Point point : list) {
        vertices[i] = point;
        i++;
    }
    check();
}

Pentagon::~Pentagon() {}