#include <iostream>
#include <memory_resource>
#include <stdexcept>
#include <iterator>

template <typename T>
class Stack {
public:
    using allocator_type = std::pmr::polymorphic_allocator<T>;

    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(T* ptr) : current(ptr) {}

        reference operator*() const { return *current; }
        pointer operator->() const { return current; }

        iterator& operator++() {
            ++current;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs) {
            return lhs.current == rhs.current;
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs) {
            return !(lhs == rhs);
        }

    private:
        T* current;
    };

    explicit Stack(std::pmr::memory_resource* resource = std::pmr::get_default_resource());

    ~Stack();

    void push(const T& value);

    void pop();

    T& top();

    bool empty() const;

    std::size_t get_size();

    void clear();

    iterator begin() {
        return iterator(data);
    }

    iterator end() {
        return iterator(data + size);
    }

private:
    void reserve(std::size_t new_capacity);
    allocator_type allocator;
    T* data;
    std::size_t size;
    std::size_t capacity;
};