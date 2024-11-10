#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

class Octal {
    private:
    unsigned char* _digits;
    size_t _capacity;
    void reverse();
    public:
    size_t size;
    Octal();
    Octal(const size_t& n, unsigned char t = 0);
    Octal(const std::initializer_list<unsigned char>& list);
    Octal(const std::string& str);
    Octal(const Octal& other);
    Octal(Octal&& other) noexcept;
    virtual ~Octal() noexcept;
    void print() const;
    size_t get_size() const;
    Octal operator+(const Octal&) const;
    Octal operator-(const Octal&) const;
    //Octal sum(const Octal& other) const;
    //Octal subtraction(const Octal& other) const;
    void clear();
    void copy(const Octal&);
    bool operator>(const Octal&) const;
    bool operator<(const Octal&) const;
    bool operator>=(const Octal&) const;
    bool operator<=(const Octal&) const;
    //bool greater_than(const Octal& other);
    //bool less_than(const Octal& other);
    bool operator==(const Octal&) const;
    //bool equal(const Octal& other);
};