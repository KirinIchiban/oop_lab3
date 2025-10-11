#include "../include/headers.hpp"

//реализация

//КОНСТРУКТОРЫ
Twelve::Twelve() : data(nullptr), size(0) {}

Twelve::Twelve(const size_t &baseNo12, unsigned char ch) {
    if (baseNo12 == 0) {
        throw std::invalid_argument("Size cannot be zero");
    }
    size = baseNo12;
    unsigned char vl;

    if (ch >= '0' && ch <= '9') {
        vl = ch - '0';
    } else if (ch == 'A' || ch == 'a') {
        vl = 10;
    } else if (ch == 'B' || ch == 'b') {
        vl = 11;
    } else {
        throw std::invalid_argument("Character in base-12");
    }

    data = new unsigned char[baseNo12];
    for (size_t i = 0; i < baseNo12; ++i) {
        data[i] = vl;
    }   
    check_nulls();
}

Twelve::Twelve(const std::initializer_list<unsigned char> &list) {
    size = list.size();
    if (size == 0) {
        throw std::invalid_argument("List is empty");
    }
    data = new unsigned char[size];

    size_t i = 0;
    for (unsigned char num : list) {
        if (num == 'A' || num == 'a') {
        num = 10;
        } 
        else if (num == 'B' || num == 'b') {
        num = 11;}
        else if (num > 9) {
            delete[] data;
            throw std::invalid_argument("Digit in initializer_list >= 10");
        }
        data[size - i - 1] = num; 
        ++i;
    }

    check_nulls();
}

Twelve::Twelve(const std::string &t) {
    if (t.empty()) {
        throw std::invalid_argument("Empty string");
    }

    size = t.size();
    data = new unsigned char[size];

    for (size_t i = 0; i < size; ++i) {
        char c = t[size - i - 1];
        unsigned char value = 0;
        if (c >= '0' && c <= '9') {
            value = c - '0';
        }
        else if (c == 'A' || c == 'a') {
            value = 10;
        } else if (c == 'B' || c == 'b') {
            value = 11;
        } else {
            throw std::invalid_argument("Invalid character number");
        }
        data[i] = value;
    }
    check_nulls();
}

Twelve::Twelve(const Twelve& other) {
    size = other.size;
    data = new unsigned char[size];
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

Twelve::Twelve(Twelve&& other) noexcept {
    size = other.size;
    data = other.data;
    other.size = 0;
    other.data = nullptr;
}

//ОПЕРАТОРЫ
Twelve& Twelve::operator=(const Twelve& other) {
    if (this != &other) {
        delete[] data;  
        size = other.size;
        data = new unsigned char[size]; 
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}
Twelve& Twelve::operator=(Twelve&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
    }
    return *this;
}

//АРИФМЕТИЧЕСКИЕ МЕТОДЫ
Twelve Twelve::add(const Twelve& other) const {
        size_t mx = (this->size > other.size) ? this->size : other.size;

        Twelve res;
        delete[] res.data; 
        res.data = new unsigned char[mx];
        res.size = mx;
        for (size_t i = 0; i < mx; ++i) {
            res.data[i] = 0;
        }

        unsigned char perenos = 0;
        for (size_t i = 0; i < mx; i++) {
            unsigned short sum = perenos;
            if (i < size) sum += data[i];
            if (i < other.size) sum += other.data[i];
            res.data[i] = sum % 12;
            perenos = sum / 12;
        }
        
        if (perenos > 0) {
            unsigned char* newData = new unsigned char[mx + 1];
            for (size_t i = 0; i < mx; i++) {
                newData[i] = res.data[i];
            }
            newData[mx] = perenos;
            
            delete[] res.data;
            res.data = newData;
            res.size = mx + 1;
        }
        
        res.check_nulls();
        return res;
}

Twelve Twelve::minus(const Twelve& other) const {
    if (isLess(other)) {
        throw std::underflow_error("Result of subtraction is negative");
    }

    unsigned char* temp_data = new unsigned char[size];
    unsigned char borrow = 0;

    for (size_t i = 0; i < size; ++i) {
        unsigned char d1 = data[i];
        unsigned char d2 = (i < other.size) ? other.data[i] : 0;

        if (d1 < d2 + borrow) {
            temp_data[i] = d1 + 12 - d2 - borrow;
            borrow = 1;
        } else {
            temp_data[i] = d1 - d2 - borrow;
            borrow = 0;
        }
    }
    Twelve result;
    delete[] result.data; 

    result.data = temp_data;
    result.size = size;
    result.check_nulls();
    return result;
}

bool Twelve::isEqual(const Twelve& other) const {
    if (size != other.size) {
        return false;
    }
    for (size_t i = 0; i < size; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

bool Twelve::isGreater(const Twelve& other) const {
    if (size != other.size) {
        return size > other.size;
    }
    for (size_t i = size; i > 0; --i) {
        size_t j = i - 1;
        if (data[j] > other.data[j]) {
            return true;
        }
        if (data[j] < other.data[j]) {
            return false;
        }
    }
    return false;
}

bool Twelve::isLess(const Twelve& other) const {
    if (size != other.size) {
        return size < other.size;
    }
    for (size_t i = size; i > 0; --i) {
        size_t j = i - 1; 
        if (data[j] < other.data[j]) {
            return true;
        }
        if (data[j] > other.data[j]) {
            return false;
        }
    }
    return false; 
}

Twelve::~Twelve() noexcept {
    delete[] data;
}

void Twelve::print() const {
    if (size == 0) {
        std::cout << '0';
    } else {
        for (size_t i = 0; i < size; ++i) {
            unsigned char digit = data[size - 1 - i]; 
            if (digit < 10) {
                std::cout << char('0' + digit);
            } else {
                std::cout << char('A' + (digit - 10));
            }
        }
    }
    std::cout << '\n';
}

void Twelve::check_nulls() {
    size_t curs = size;
    while (curs > 1 && data[curs - 1] == 0) {
        --curs;
    }

    if (curs != size) {
        unsigned char* cordata = new unsigned char[curs];
        for (size_t i = 0; i < curs; ++i) {
            cordata[i] = data[i];
        }
        delete[] data;
        data = cordata;
        size = curs;
    }
}

std::string Twelve::tostr() const {
    if (size == 0) {
        return "0";
    }
    std::string result;
    result.reserve(size); 
    for (size_t i = 0; i < size; ++i) {
        unsigned char digit = data[size - 1 - i];
        if (digit < 10) {
            result += static_cast<char>('0' + digit);
        } else {
            result += static_cast<char>('A' + (digit - 10));
        }
    }
    return result;
}