#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

//интерфейс
class Twelve { 
public:
    //КОНСТРУКТОРЫ
    Twelve();
    Twelve(const size_t &baseNo12, unsigned char ch = 0);
    Twelve(const std::initializer_list<unsigned char> &list);
    Twelve(const std::string &t);
    Twelve(const Twelve& other);
    Twelve(Twelve&& other) noexcept;
    
    //ОПЕРАТОРЫ
    Twelve& operator=(const Twelve& other);
    Twelve& operator=(Twelve&& other) noexcept;

    //АРИФМЕТИЧЕСКИЕ МЕТОДЫ
    Twelve add(const Twelve& other) const;
    Twelve minus(const Twelve& other) const;

    //КОМПАРАТОРЫ
    bool isEqual(const Twelve& other) const;
    bool isLess(const Twelve& other) const;
    bool isGreater(const Twelve& other) const;

    //ДЕСТРУКТОР
    virtual ~Twelve() noexcept;

    void print() const;
    std::string tostr() const;

    private:
        unsigned char* data;  
        size_t size;
        void check_nulls();            
};

