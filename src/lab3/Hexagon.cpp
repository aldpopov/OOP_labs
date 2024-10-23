#include "Hexagon.h"
#include "Jarvis.h"

Hexagon::Hexagon() : Figure(6) {}

Hexagon::Hexagon(const Hexagon& other) : Figure(other) { check(); }

Hexagon::Hexagon(Hexagon&& other) noexcept : Figure(other) { check(); }

void Hexagon::check() {
    if(vertex_quantity != 6) {
        throw std::invalid_argument("It is not a hexagon.");
    }
    
    Point* hull = convex_hull(*this);
    int hull_size = hull[0].x;
    if(hull_size != vertex_quantity) {
        throw std::invalid_argument("It is not a convex pentagon.");
    } else {
        for(size_t i = 0; i < hull_size; i++) {
            set_point(hull[i + 1], i);
        }
    }
}

Hexagon::Hexagon(const std::initializer_list<Point>& list) {
    vertex_quantity = list.size();
    vertices = new Point[vertex_quantity];

    size_t i = 0;
    for (Point point : list) {
        vertices[i] = point;
        i++;
    }
    check();
}

Hexagon::~Hexagon() {}