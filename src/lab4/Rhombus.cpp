#include "Rhombus.h"
#include "Figure.h"
#include "Jarvis.h"

template <Number N>
Rhombus<N>::Rhombus() : Figure<N>(4) {}

template <Number N>
Rhombus<N>::Rhombus(const Rhombus& other) : Figure<N>(other) { check(); }

template <Number N>
Rhombus<N>::Rhombus(Rhombus&& other) noexcept : Figure<N>(other) { check(); }

template <Number N>
void Rhombus<N>::check() {
    if (this->vertex_quantity != 4) {
        throw std::invalid_argument("It is not a rhombus.");
    }
    
    std::unique_ptr<Point<N>[]> hull = convex_hull(*this);
    int hull_size = hull[0].x;
    if(hull_size != this->vertex_quantity) {
        throw std::invalid_argument("It is not a convex rhomb.");
    } else {
        for(size_t i = 0; i < hull_size; i++) {
            this->set_point(hull[i + 1], i);
        }
    }

    double ab_length = (this->vertices[1] - this->vertices[0]).abs();
    double bc_length = (this->vertices[2] - this->vertices[1]).abs();
    double cd_length = (this->vertices[3] - this->vertices[2]).abs();
    double da_length = (this->vertices[0] - this->vertices[3]).abs();

    if (ab_length != bc_length || ab_length != cd_length || ab_length != da_length || bc_length != cd_length || bc_length != da_length || cd_length != da_length) {
        throw std::invalid_argument("It is not a rhombus without equal sides.");
    }
}

template <Number N>
Rhombus<N>::Rhombus(const std::initializer_list<Point<N>>& list) {
    this->vertex_quantity = list.size();
    this->vertices = std::make_unique<Point<N>[]>(this->vertex_quantity);

    size_t i = 0;
    for (Point<N> point : list) {
        this->vertices[i] = point;
        i++;
    }
    this->check();
}

template <Number N>
Rhombus<N>::~Rhombus() {}

template <typename Type>
std::ostream& operator<<(std::ostream& out, const Rhombus<Type>& rhomb) {
    out << "Rhombus( ";
    auto& vertices = rhomb.get_points();
    size_t size = rhomb.size();
    for(size_t i = 0; i < size; i++) {
        out << "( " << vertices[i].x << ", " << vertices[i].y << " ), ";
    }
    out << ") ";
    return out;
}

template <typename Type>
std::istream& operator>>(std::istream& in, Rhombus<Type>& rhomb) {
    Type x, y;
    for(size_t i = 0; i < rhomb.size(); i++) {
        in >> x >> y;
        Point<Type> point({x, y});
        rhomb.set_point(point, i);
    }
    rhomb.check();
    return in;
}