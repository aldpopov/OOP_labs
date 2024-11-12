#include "Hexagon.h"
#include "Jarvis.h"

template <Number N>
Hexagon<N>::Hexagon() : Figure<N>(6) {}

template <Number N>
Hexagon<N>::Hexagon(const Hexagon& other) : Figure<N>(other) { check(); }

template <Number N>
Hexagon<N>::Hexagon(Hexagon&& other) noexcept : Figure<N>(other) { check(); }

template <Number N>
void Hexagon<N>::check() {
    if(this->vertex_quantity != 6) {
        throw std::invalid_argument("It is not a hexagon.");
    }
    
    std::unique_ptr<Point<N>[]> hull = convex_hull(*this);
    int hull_size = hull[0].x;
    if(hull_size != this->vertex_quantity) {
        throw std::invalid_argument("It is not a convex pentagon.");
    } else {
        for(size_t i = 0; i < hull_size; i++) {
            this->set_point(hull[i + 1], i);
        }
    }
}

template <Number N>
Hexagon<N>::Hexagon(const std::initializer_list<Point<N>>& list) {
    this->vertex_quantity = list.size();
    this->vertices = std::make_unique<Point<N>[]>(this->vertex_quantity);

    size_t i = 0;
    for (Point<N> point : list) {
        this->vertices[i] = point;
        i++;
    }
    this->check();
}

template <Number N>
Hexagon<N>::~Hexagon() {}