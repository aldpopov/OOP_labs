#include "Array.h"

template <typename Type>
Array<Type>::Array() : s(0), capacity(1), array(std::make_unique<std::shared_ptr<Type>[]>(s)) { }

template <typename Type>
Array<Type>::Array(const Array &other) : s(other.s), capacity(other.capacity), array(std::make_unique<std::shared_ptr<Type>[]>(other.s)) {
    for(size_t i = 0; i < s; i++) {
        array[i] = std::make_shared<Type>(*other.array[i]);
    }
}

template <typename Type>
Array<Type>::Array(Array &&other) noexcept : s(other.s), capacity(other.capacity), array(std::move(other.array)) {
    other.s = 0;
    other.capacity = 0;
}

template <typename Type>
size_t Array<Type>::size() const {
    return s;
}

template <typename Type>
void Array<Type>::clear() {
    s = 0;
    capacity = 1;
    array.reset();
    array = nullptr;
}

template <typename Type>
void Array<Type>::copy(const Array &other) {
    s = other.s;
    capacity = other.capacity;
    array = std::make_unique<std::shared_ptr<Type>[]>(other.s);
    std::copy(other.get_points(), other.get_points() + s, array);
}

template <typename Type>
Array<Type> &Array<Type>::operator=(const Array &other) {
    if (this != &other) {
        copy(other);
    }
}

template <typename Type>
Array<Type> &Array<Type>::operator=(Array &&other) noexcept {
    if(this != &other) {
        //array.reset();
        s = other.s;
        array = other.array;
        other.s = 0;
        other.array.reset();
        other.array = nullptr;
    }
    return *this;
}

template <typename Type>
std::shared_ptr<Type> &Array<Type>::operator[](size_t index) {
    if(index >= s) {
        throw std::out_of_range("Index out of range!");
    }
    return array[index];
}

template <typename Type>
void Array<Type>::resize(size_t lim) {
    auto array_2 = std::make_unique<std::shared_ptr<Type>[]>(lim);
    for(size_t i = 0; i < s; i++) {
        array_2[i] = std::move(array[i]);
    }

    array = std::move(array_2);
    capacity = lim;
}

template <typename Type>
void Array<Type>::append(std::shared_ptr<Type> to_add) {
    if(s == capacity) {
        resize(capacity * 2);
    }
    array[s++] = to_add;
}

template <typename Type>
void Array<Type>::remove(size_t index) {
    //std::cout << s << " " << index << std::endl;
    if(index >= s) {
        throw std::out_of_range("Index out of range?");
    }
    for(size_t i = index; i < s - 1; i++) {
        array[i] = std::move(array[i + 1]);
    }
    s--;
}