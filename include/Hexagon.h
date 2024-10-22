#pragma once
#include <iostream>
#include "Figure.h"

class Hexagon : public Figure {
    public:
    Hexagon();
    Hexagon(const Hexagon&);
    Hexagon(Hexagon&&) noexcept;
    Hexagon(const std::initializer_list<Point>&);
    virtual void check();
    virtual ~Hexagon();
};

inline std::ostream& operator<<(std::ostream& out, const Hexagon& hex) {
    out << "Hexagon( ";
    Point* vertices = hex.get_points();
    size_t size = hex.size();
    for(size_t i = 0; i < hex.size(); i++) {
        out << "( " << vertices[i].x << ", " << vertices[i].y << " ), ";
    }
    out << ") ";
    return out;
}

inline std::istream& operator>>(std::istream& in, Hexagon& hex) {
    double x, y;
    for(size_t i = 0; i < hex.size(); i++) {
        in >> x >> y;
        Point point({x, y});
        hex.set_point(point, i);
    }
    hex.check();
    return in;
}