#pragma once
#include <iostream>
#include "Figure.h"

template <Number N>
class Hexagon : public Figure<N> {
    public:
    Hexagon();
    Hexagon(const Hexagon&);
    Hexagon(Hexagon&&) noexcept;
    Hexagon(const std::initializer_list<Point<N>>&);
    virtual void check();
    virtual ~Hexagon();
};

template <Number N>
std::ostream& operator<<(std::ostream& out, const Hexagon<N>& hex) {
    out << "Hexagon( ";
    auto& vertices = hex.get_points();
    size_t size = hex.size();
    for(size_t i = 0; i < size; i++) {
        out << "( " << vertices[i].x << ", " << vertices[i].y << " ), ";
    }
    out << ") ";
    return out;
}

template <Number N>
std::istream& operator>>(std::istream& in, Hexagon<N>& hex) {
    N x, y;
    for(size_t i = 0; i < hex.size(); i++) {
        in >> x >> y;
        Point<N> point({x, y});
        hex.set_point(point, i);
    }
    hex.check();
    return in;
}