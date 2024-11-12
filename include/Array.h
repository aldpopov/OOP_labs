#pragma once
#include <memory>
#include <stdexcept>
#include "Point.h"

template <typename Type>
class Array {
    private:
    size_t s;
    size_t capacity;
    std::unique_ptr<std::shared_ptr<Type>[]> array;
    void resize(size_t);
    void copy(const Array&);
    
    public:
    Array();
    Array(const Array&);
    Array(Array&&) noexcept;

    size_t size() const;
    Array &operator=(const Array &);
    Array &operator=(Array&&) noexcept;
    std::shared_ptr<Type> &operator[](size_t);

    void append(std::shared_ptr<Type>);
    void remove(size_t);
    void clear();
};