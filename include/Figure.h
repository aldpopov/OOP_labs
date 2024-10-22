#pragma once
#include <iostream>
#include "Point.h"

class Figure {
    public:
    Point* vertices;
    size_t vertex_quantity;
    Figure();
    Figure(size_t);
    Figure(const Figure&);
    Figure(Figure&&) noexcept;
    Figure(const std::initializer_list<Point>&);
    virtual ~Figure() noexcept;
    Point* get_points() const;
    void set_points(Point*);
    void set_point(Point&, size_t);
    size_t size() const;
    void clear();
    void copy(const Figure&);
    void print() const;
    Figure& operator=(const Figure&);
    Figure& operator=(Figure&&) noexcept;
    bool operator==(const Figure&) const;
    double area() const;
    virtual void check();
    Point* center() const;
    operator double() const { return area(); };
};

inline std::ostream& operator<<(std::ostream& out, const Figure& fig) {
    out << "( ";
    Point* vertices = fig.get_points();
    size_t size = fig.size();
    for(size_t i = 0; i < fig.size(); i++) {
        out << "( " << vertices[i].x << ", " << vertices[i].y << ") ";
    }
    out << ") ";
    return out;
}

inline std::istream& operator>>(std::istream& in, Figure& fig) {
    double x, y;
    for(size_t i = 0; i < fig.size(); i++) {
        in >> x >> y;
        Point point({x, y});
        fig.set_point(point, i);
    }
    fig.check();
    return in;
}