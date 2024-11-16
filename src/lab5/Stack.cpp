#include "Stack.h"
#include "MemoryResource.h"
#include <memory_resource>
#include <iostream>
#include <iterator>

template <typename T>
Stack<T>::Stack(std::pmr::memory_resource* resource)
    : allocator(resource), data(nullptr), size(0), capacity(0) {}

template <typename T>
Stack<T>::~Stack() {
    clear();
    allocator.deallocate(data, capacity);
}

template <typename T>
void Stack<T>::push(const T& value) {
    if (size >= capacity) {
        reserve(capacity == 0 ? 1 : capacity * 2);
    }
    allocator.construct(data + size, value);
    ++size;
}

template <typename T>
void Stack<T>::pop() {
    if (size == 0) {
        throw std::runtime_error("Stack is empty");
    }
    --size;
    allocator.destroy(data + size);
}

template <typename T>
T& Stack<T>::top() {
    if (size == 0) {
        throw std::runtime_error("Stack is empty");
    }
    return data[size - 1];
}

template <typename T>
bool Stack<T>::empty() const {
    return size == 0;
}

template <typename T>
std::size_t Stack<T>::get_size() {
    return size;
}

template <typename T>
void Stack<T>::clear() {
    while (!empty()) {
        pop();
    }
}

template <typename T>
void Stack<T>::reserve(std::size_t new_capacity) {
    if (new_capacity <= capacity) return;
    T* new_data = allocator.allocate(new_capacity);
    for (std::size_t i = 0; i < size; ++i) {
        allocator.construct(new_data + i, std::move(data[i]));
        allocator.destroy(data + i);
    }
    allocator.deallocate(data, capacity);
    data = new_data;
    capacity = new_capacity;
}
