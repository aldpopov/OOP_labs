#pragma once
#include <iostream>
#include "Figure.h"

class Pentagon : public Figure {
    public:
    Pentagon();
    Pentagon(const Pentagon&);
    Pentagon(Pentagon&&) noexcept;
    Pentagon(const std::initializer_list<Point>&);
    virtual void check();
    virtual ~Pentagon();
};

inline std::ostream& operator<<(std::ostream& out, const Pentagon& penta) {
    out << "Pentagon( ";
    Point* vertices = penta.get_points();
    size_t size = penta.size();
    for(size_t i = 0; i < penta.size(); i++) {
        out << "( " << vertices[i].x << ", " << vertices[i].y << " ), ";
    }
    out << ") ";
    return out;
}

inline std::istream& operator>>(std::istream& in, Pentagon& penta) {
    double x, y;
    for(size_t i = 0; i < penta.size(); i++) {
        in >> x >> y;
        Point point({x, y});
        penta.set_point(point, i);
    }
    penta.check();
    return in;
}