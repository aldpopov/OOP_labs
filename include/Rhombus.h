#pragma once
#include <iostream>
#include "Figure.h"

class Rhombus : public Figure {
    public:
    Rhombus();
    Rhombus(const Rhombus&);
    Rhombus(Rhombus&&) noexcept;
    Rhombus(const std::initializer_list<Point>&);
    virtual void check();
    virtual ~Rhombus();
};

inline std::ostream& operator<<(std::ostream& out, const Rhombus& rhomb) {
    out << "Rhombus( ";
    Point* vertices = rhomb.get_points();
    size_t size = rhomb.size();
    for(size_t i = 0; i < rhomb.size(); i++) {
        out << "( " << vertices[i].x << ", " << vertices[i].y << " ), ";
    }
    out << ") ";
    return out;
}

inline std::istream& operator>>(std::istream& in, Rhombus& rhomb) {
    double x, y;
    for(size_t i = 0; i < rhomb.size(); i++) {
        in >> x >> y;
        Point point({x, y});
        rhomb.set_point(point, i);
    }
    rhomb.check();
    return in;
}