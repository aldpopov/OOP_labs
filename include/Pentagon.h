#pragma once
#include <iostream>
#include "Figure.h"

template <Number N>
class Pentagon : public Figure<N> {
    public:
    Pentagon();
    Pentagon(const Pentagon&);
    Pentagon(Pentagon&&) noexcept;
    Pentagon(const std::initializer_list<Point<N>>&);
    virtual void check();
    virtual ~Pentagon();
};

template <Number N>
std::ostream& operator<<(std::ostream& out, const Pentagon<N>& penta) {
    out << "Pentagon( ";
    auto& vertices = penta.get_points();
    size_t size = penta.size();
    for(size_t i = 0; i < size; i++) {
        out << "( " << vertices[i].x << ", " << vertices[i].y << " ), ";
    }
    out << ") ";
    return out;
}

template <Number N>
std::istream& operator>>(std::istream& in, Pentagon<N>& penta) {
    N x, y;
    for(size_t i = 0; i < penta.size(); i++) {
        in >> x >> y;
        Point<N> point({x, y});
        penta.set_point(point, i);
    }
    penta.check();
    return in;
}