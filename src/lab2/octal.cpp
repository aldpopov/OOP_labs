#include "Octal.h"
#include <cstring>
#include <algorithm>

Octal::Octal() : _digits(nullptr), _capacity(0), size(0) {}

Octal::Octal(const size_t& n, unsigned char t) : _capacity(n), size(n) {
    _digits = new unsigned char[_capacity];
    for(size_t i = 0; i < size; ++i) {
        _digits[i] = t;
    }
}

Octal::Octal(const std::initializer_list<unsigned char>& list) : _capacity(list.size()), size(list.size()) {
    _digits = new unsigned char[_capacity];
    size_t index = 0;
    for(auto iter = list.begin(); iter != list.end(); iter++) {
        if (*iter > 7) {
            throw std::invalid_argument("Not valid digit");
        }
        _digits[index++] = *iter;
    }
}

Octal::Octal(const std::string& str) {
    size = str.size();
    _capacity = size;
    _digits = new unsigned char[_capacity];
    for(size_t i = 0; i < size; i++) {
        _digits[i] = str[i] - '0';
    }
}

Octal::Octal(const Octal&other) : _capacity(other._capacity), size(other.size) {
    _digits = new unsigned char [_capacity];
    for(size_t i = 0; i < size; i++) {
        _digits[i] = other._digits[i];
    }
}

Octal::Octal(Octal&& other) noexcept : _digits(other._digits), _capacity(other._capacity), size(other.size) {
    other._digits = nullptr;
    other.size = 0;
    other._capacity = 0;
}

void Octal::clear() {
    delete[] _digits;
    size = 0;
    _capacity = 0;
}

Octal::~Octal() noexcept { clear(); }

size_t Octal::get_size() const {
    return size;
}

void Octal::print() const {
    for(size_t i = 0; i < size; i++) {
        std::cout << static_cast<int>(_digits[i]);
    }
    std::cout << std::endl;
}

Octal Octal::operator+(const Octal &other) const {
    size_t max_size = std::max(size, other.size);
    size_t new_size = max_size + 1;
    Octal res(new_size, 0);
    int transfer = 0;
    for(size_t i = 0; i< max_size; ++i) {
        int first_digit = static_cast<int>((i < size) ? _digits[size - 1 - i] : 0);
        int second_digit = static_cast<int>((i < other.size) ? other._digits[size - 1 - i] : 0);
        int sum = first_digit + second_digit + transfer;
        res._digits[i] = static_cast<unsigned char>(sum % 8);
        transfer = sum / 8;
    }
    if(transfer > 0) {
        res._digits[0] = transfer;
    } else {
        res.size = max_size;
    }
    res.reverse();
    return res;
}

Octal Octal::operator-(const Octal &other) const {
    if(size < other.size) {
        throw std::invalid_argument("It is impossible subtraction.");
    }
    size_t max_size = size;
    Octal res(max_size, 0);
    int lent = 0;
    for(size_t i =0; i < max_size; i++) {
        int first_digit = static_cast<int>((i < size) ? _digits[size - 1 - i] : 0);
        int second_digit = static_cast<int>((i < other.size) ? other._digits[size - 1 - i] : 0);
        int subt = first_digit - second_digit - lent;
        if(subt < 0) {
            subt += 8;
            lent = 1;
        } else {
            lent = 0;
        }
        res._digits[i] = static_cast<unsigned char>(subt);
    }
    int leading_zeroes = 0;
    while(leading_zeroes < res.size && res._digits[res.size - 1 - leading_zeroes] == 0) {
        leading_zeroes++;
    }
    res.size -= leading_zeroes;
    res.reverse();
    return res;
}

void Octal::copy(const Octal& other) {
    if(this != &other) {
        delete[] _digits;
        _capacity = other._capacity;
        size = other.size;
        _digits = new unsigned char[_capacity];
        for(size_t i = 0; i < size; i++) {
            _digits[i] = other._digits[i];
        }
    }
}

void Octal::reverse() {
    std::reverse(_digits, _digits + size);
}

bool Octal::operator>(const Octal& other) const {
    if (size > other.size) {
        return true;
    } else if (size < other.size) {
        return false;
    } else {
        for (size_t i = 0; i < size; i++) {
            if(_digits[i] > other._digits[i]) {
                return true;
            }else if (_digits[i] < other._digits[i]) {
                return false;
            }
        }
        return false;
    }
}

bool Octal::operator>=(const Octal& other) const {
    if (size > other.size) {
        return true;
    } else if (size < other.size) {
        return false;
    } else {
        for (size_t i = 0; i < size; i++) {
            if(_digits[i] > other._digits[i]) {
                return true;
            }else if (_digits[i] < other._digits[i]) {
                return false;
            }
        }
        return true;
    }
}

bool Octal::operator<(const Octal& other) const {
    if (size > other.size) {
        return false;
    } else if (size < other.size) {
        return true;
    } else {
        for (size_t i = 0; i < size; i++) {
            if(_digits[i] < other._digits[i]) {
                return true;
            }else if (_digits[i] > other._digits[i]) {
                return false;
            }
        }
        return false;
    }
}

bool Octal::operator<=(const Octal& other) const {
    if (size > other.size) {
        return false;
    } else if (size < other.size) {
        return true;
    } else {
        for (size_t i = 0; i < size; i++) {
            if(_digits[i] < other._digits[i]) {
                return true;
            }else if (_digits[i] > other._digits[i]) {
                return false;
            }
        }
        return true;
    }
}

bool Octal::operator==(const Octal& other) const {
    if((*this >= other) && (*this <= other)) {
        return true;
    } else {
        return false;
    }
}
