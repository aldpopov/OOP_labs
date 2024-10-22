#include "Point.h"
#include <math.h>

Point::Point() : x(0.0), y(0.0) {}

Point::Point(double x, double y) : x(x), y(y) {}

Point::Point(std::initializer_list<double>& list) {
    if (list.size() == 2) {
        auto iter = list.begin();
        x = *iter++;
        y = *iter;
    } else {
        x = 0;
        y = 0;
    }
}

bool Point::operator==(const Point& other) const {
    return this->x == other.x && this->y == other.y;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

Point Point::operator+(const Point& other) const {
    return Point(x + other.x, y + other.y);
}

Point Point::operator-(const Point& other) const {
    return Point(x - other.x, y - other.y);
}

double Point::operator*(const Point& other) const {
    return x * other.x + y * other.y;
}

double Point::abs() const {
    return sqrt(x * x + y * y);
}