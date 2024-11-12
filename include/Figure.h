#pragma once
#include <iostream>
#include <memory>
#include "Point.h"

template <Number N>
class Figure {
    public:
    std::unique_ptr<Point<N>[]> vertices;
    size_t vertex_quantity;
    Figure();
    Figure(size_t);
    Figure(const Figure&);
    Figure(Figure&&) noexcept;
    Figure(const std::initializer_list<Point<N>>&);
    virtual ~Figure() noexcept;
    const std::unique_ptr<Point<N>[]>& get_points() const;
    void set_points(std::unique_ptr<Point<N>[]>);
    void set_point(Point<N>&, size_t);
    size_t size() const;
    void clear();
    void copy(const Figure&);
    void print() const;
    Figure& operator=(const Figure&);
    Figure& operator=(Figure&&) noexcept;
    bool operator==(const Figure&) const;
    double area() const;
    virtual void check();
    std::unique_ptr<Point<N>> center() const;
    operator double() const { return area(); };
};

template <Number N>
std::ostream& operator<<(std::ostream& out, const Figure<N>& fig) {
    out << "( ";
    auto& vertices = fig.get_points();
    size_t size = fig.size();
    for(size_t i = 0; i < size; i++) {
        out << "( " << vertices[i].x << ", " << vertices[i].y << ") ";
    }
    out << ") ";
    return out;
}

template <Number N>
std::istream& operator>>(std::istream& in, Figure<N>& fig) {
    N x, y;
    for(size_t i = 0; i < fig.size(); i++) {
        in >> x >> y;
        Point<N> point({x, y});
        fig.set_point(point, i);
    }
    fig.check();
    return in;
}