#include "Rhombus.h"
#include "Jarvis.h"

Rhombus::Rhombus() : Figure(4) {}

Rhombus::Rhombus(const Rhombus& other) : Figure(other) { check(); }

Rhombus::Rhombus(Rhombus&& other) noexcept : Figure(other) { check(); }

void Rhombus::check() {
    if (vertex_quantity != 4) {
        throw std::invalid_argument("It is not a rhombus.");
    }
    
    Point* hull = convex_hull(*this);
    int hull_size = hull[0].x;
    if(hull_size != vertex_quantity) {
        throw std::invalid_argument("It is not a convex rhomb.");
    } else {
        for(size_t i = 0; i < hull_size; i++) {
            set_point(hull[i + 1], i);
        }
    }

    double ab_length = (vertices[1] - vertices[0]).abs();
    double bc_length = (vertices[2] - vertices[1]).abs();
    double cd_length = (vertices[3] - vertices[2]).abs();
    double da_length = (vertices[0] - vertices[3]).abs();

    if (ab_length != bc_length || ab_length != cd_length || ab_length != da_length || bc_length != cd_length || bc_length != da_length || cd_length != da_length) {
        throw std::invalid_argument("It is not a rhombus without equal sides.");
    }
}

Rhombus::Rhombus(const std::initializer_list<Point>& list) {
    vertex_quantity = list.size();
    vertices = new Point[vertex_quantity];

    size_t i = 0;
    for ( Point point : list) {
        vertices[i] = point;
        i++;
    }
    check();
}

Rhombus::~Rhombus() {}