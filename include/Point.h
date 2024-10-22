#pragma once
#include <iostream>

class Point {
    public:
    double x,y;
    Point();
    Point(double, double);
    Point(std::initializer_list<double>& list);
    Point operator+(const Point&) const;
    Point operator-(const Point&) const;
    double operator*(const Point&) const;
    bool operator==(const Point&) const;
    bool operator!=(const Point&) const;
    double abs() const;
};

inline std::ostream& operator<<(std::ostream& out, const Point& p) {
    out << "Point( " << p.x << ", " << p.y << " )";
    return out;
}