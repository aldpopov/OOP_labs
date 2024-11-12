#include "Figure.h"
#include <math.h>
#include <iostream>
#include "Jarvis.h"
#include <memory>

template <Number N>
void Figure<N>::print() const {
    std::cout << "( ";
    for(size_t i = 0; i < vertex_quantity; i++) {
        std::cout << "( " << vertices[i].x << ", " << vertices[i].y << "), ";
    }
    std::cout<< ")" << std::endl;
}

template <Number N>
Figure<N>::Figure() : vertices(nullptr), vertex_quantity(0) {}

template <Number N>
Figure<N>::Figure(size_t s) : vertices(std::make_unique<Point<N>[]>(s)), vertex_quantity(s) { check(); }

template <Number N>
Figure<N>::Figure(const Figure& other) { copy(other); }

template <Number N>
Figure<N>::Figure(Figure&& other) noexcept : vertex_quantity(other.vertex_quantity), vertices(std::move(other.vertices)) {
    other.vertex_quantity = 0;
    other.vertices = nullptr;
}

template <Number N>
Figure<N>::~Figure() noexcept{ clear(); }

template <Number N>
Figure<N>::Figure(const std::initializer_list<Point<N>>& list) : vertices(std::make_unique<Point<N>[]>(list.size())), vertex_quantity(list.size()) {
    size_t i = 0;
    for(Point<N> p : list) {
        vertices[i] = p;
        i++;
    }
    check();
}

template <Number N>
void Figure<N>::check() {
    std::unique_ptr<Point<N>[]> hull = convex_hull(*this);
    int hull_size = hull[0].x;
    if(hull_size != vertex_quantity) {
        throw std::invalid_argument("It is not a convex figure.");
    } else {
        for(size_t i = 0; i < hull_size; i++) {
            set_point(hull[i + 1], i);
        }
    }
}

template <Number N>
const std::unique_ptr<Point<N>[]>& Figure<N>::get_points() const { return vertices; }

template <Number N>
void Figure<N>::set_points(std::unique_ptr<Point<N>[]> p) { vertices = std::move(p); }

template <Number N>
void Figure<N>::set_point(Point<N> &p, size_t s) { 
    if(s < vertex_quantity) {
        vertices[s] = p;
    } 
}

template <Number N>
size_t Figure<N>::size() const { return vertex_quantity; }

template <Number N>
void Figure<N>::clear() {
    vertices.reset();
    vertex_quantity = 0;
    vertices = nullptr;
}

template <Number N>
void Figure<N>::copy(const Figure& other) {
    if(this != &other) {
        clear();
        vertex_quantity = other.vertex_quantity;
        vertices = std::make_unique<Point<N>[]>(vertex_quantity);
        for(size_t i = 0; i < vertex_quantity; i++) {
            vertices[i] = other.vertices[i];
        }
    }
}

template <Number N>
Figure<N>& Figure<N>::operator=(const Figure& other) {
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

template <Number N>
Figure<N>& Figure<N>::operator=(Figure&& other) noexcept {
    if (this != &other) {
        vertices = std::move(other.vertices);
    }
    return *this;
}

template <Number N>
bool Figure<N>::operator==(const Figure& other) const {
    if (vertex_quantity != other.size()) {
        return false;
    }
    std::unique_ptr<Point<N>[]> other_vertices = other.get_points();
    for(size_t i = 0; i < vertex_quantity; i++) {
        if(vertices[i].x != other_vertices[i].x || vertices[i].y != other_vertices[i].y) {
            return false;
        }
    }
    return true;
}

template <Number N>
double Figure<N>::area() const {
    double fig_area;
    for (size_t i = 0; i < vertex_quantity - 1; i++) {
        fig_area += vertices[i].x * vertices[i + 1].y;
    }
    fig_area += vertices[vertex_quantity - 1].x * vertices[0].y;
    for (size_t i = 0; i < vertex_quantity - 1; i++) {
        fig_area -= vertices[i].y * vertices[i + 1].x;
    }
    fig_area -= vertices[0].x * vertices[vertex_quantity - 1].y;
    return abs(fig_area) * 0.5;
}

template <Number N>
std::unique_ptr<Point<N>> Figure<N>::center() const {
    std::unique_ptr<Point<N>> center = std::make_unique<Point<N>>();
    for (size_t i = 0; i < vertex_quantity; i++) {
        center->x += vertices[i].x;
        center->y += vertices[i].y;
    }
    center->x /= vertex_quantity;
    center->y /= vertex_quantity;
    return center;
}