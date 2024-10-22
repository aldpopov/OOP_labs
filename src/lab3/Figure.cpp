#include "Figure.h"
#include <math.h>
#include <iostream>
#include "Jarvis.h"

void Figure::print() const {
    std::cout << "( ";
    for(size_t i = 0; i < vertex_quantity; i++) {
        std::cout << "( " << vertices[i].x << ", " << vertices[i].y << "), ";
    }
    std::cout<< ")" << std::endl;
}

Figure::Figure() : vertices(nullptr), vertex_quantity(0) {}

Figure::Figure(size_t s) : vertices(new Point[s]), vertex_quantity(s) {}

Figure::Figure(const Figure& other) { copy(other); }

Figure::Figure(Figure&& other) noexcept : vertex_quantity(other.vertex_quantity), vertices(other.vertices) {
    other.vertex_quantity = 0;
    other.vertices = nullptr;
}

Figure::~Figure() { clear(); }

Figure::Figure(const std::initializer_list<Point>& list) : vertices(new Point[list.size()]), vertex_quantity(list.size()) {
    size_t i = 0;
    for(Point p : list) {
        vertices[i] = p;
        i++;
    }
    check();
}

void Figure::check() {
    Point* hull = convex_hull(*this);
    int hull_size = hull[0].x;
    if(hull_size != vertex_quantity) {
        throw std::invalid_argument("It is not a convex figure.");
    } else {
        for(size_t i = 0; i < hull_size; i++) {
            set_point(hull[i + 1], i);
        }
    }
}

Point* Figure::get_points() const { return vertices; }

void Figure::set_points(Point* p) { vertices = p; }

void Figure::set_point(Point &p, size_t i) { vertices[i] = p; }

size_t Figure::size() const { return vertex_quantity; }

void Figure::clear() {
    delete[] vertices;
    vertex_quantity = 0;
    vertices = nullptr;
}

void Figure::copy(const Figure& other) {
    vertex_quantity = other.size();
    vertices = new Point[vertex_quantity];
    std::copy(other.get_points(), other.get_points() + vertex_quantity, vertices);
}

Figure& Figure::operator=(const Figure& other) {
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

Figure& Figure::operator=(Figure&& other) noexcept {
    if (this != &other) {
        vertex_quantity = other.size();
        delete[] vertices;
        vertices = other.get_points();
        other.vertex_quantity = 0;
        other.vertices = nullptr;
    }
    return *this;
}

bool Figure::operator==(const Figure& other) const {
    if (vertex_quantity != other.size()) {
        return false;
    }
    Point* other_vertices = other.get_points();
    for(size_t i = 0; i < vertex_quantity; i++) {
        if(vertices[i].x != other_vertices[i].x || vertices[i].y != other_vertices[i].y) {
            return false;
        }
    }
    return true;
}

double Figure::area() const {
    double fig_area;
    for (size_t i = 0; i < vertex_quantity - 1; i++) {
        fig_area += vertices[i].x * vertices[i + 1].y;
    }
    fig_area += vertices[vertex_quantity - 1].x * vertices[0].y;
    for (size_t i = 0; i < vertex_quantity - 1; i++) {
        fig_area -= vertices[i].y * vertices[i + 1].x;
    }
    fig_area -= vertices[vertex_quantity - 1].y * vertices[0].x;
    return abs(fig_area) / 2;
}

Point* Figure::center() const {
    Point* center = new Point();
    for (size_t i = 0; i < vertex_quantity; i++) {
        center->x += vertices[i].x;
        center->y += vertices[i].y;
    }
    center->x /= vertex_quantity;
    center->y /= vertex_quantity;
    return center;
}