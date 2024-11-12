#include "Point.h"
#include <math.h>

template <Number N>
Point<N>::Point() : x(0.0), y(0.0) {}

template <Number N>
Point<N>::Point(N x, N y) : x(x), y(y) {}

template <Number N>
Point<N>::Point(std::initializer_list<N>& list) {
    if (list.size() == 2) {
        auto iter = list.begin();
        x = *iter++;
        y = *iter;
    } else {
        x = 0;
        y = 0;
    }
}

template <Number N>
bool Point<N>::operator==(const Point& other) const {
    return this->x == other.x && this->y == other.y;
}

template <Number N>
bool Point<N>::operator!=(const Point& other) const {
    return !(*this == other);
}

template <Number N>
Point<N> Point<N>::operator+(const Point& other) const {
    return Point(x + other.x, y + other.y);
}

template <Number N>
Point<N> Point<N>::operator-(const Point& other) const {
    return Point(x - other.x, y - other.y);
}

template <Number N>
double Point<N>::operator*(const Point& other) const {
    return x * other.x + y * other.y;
}

template <Number N>
double Point<N>::abs() const {
    return sqrt(x * x + y * y);
}