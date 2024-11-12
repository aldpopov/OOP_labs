#pragma once
#include <iostream>
#include "Figure.h"

template <Number T>
class Rhombus : public Figure<T> {
    public:
    Rhombus();
    Rhombus(const Rhombus&);
    Rhombus(Rhombus&&) noexcept;
    Rhombus(const std::initializer_list<Point<T>>&);
    virtual void check();
    virtual ~Rhombus();
    
    template <Number N>
    friend std::ostream& operator<<(std::ostream& out, const Rhombus<T>& rhomb);

    template <Number N>
    friend std::istream& operator>>(std::istream& in, Rhombus<T>& rhomb);
};