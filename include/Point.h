#pragma once
#include <concepts>
#include <memory>
#include <type_traits>
#include <iostream>

template <typename Type>
concept Number = std::is_integral_v<Type> || std::is_floating_point_v<Type>; 

template <Number N>
class Point {
    public:
    N x,y;
    Point();
    Point(N, N);
    Point(std::initializer_list<N>& list);
    Point operator+(const Point&) const;
    Point operator-(const Point&) const;
    double operator*(const Point&) const;
    bool operator==(const Point&) const;
    bool operator!=(const Point&) const;
    double abs() const;
};

template <typename Type>
std::ostream& operator<<(std::ostream& out, const Point<Type>& p) {
    out << "Point( " << p.x << ", " << p.y << " )";
    return out;
}