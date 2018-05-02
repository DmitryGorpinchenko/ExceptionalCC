#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
public:
    Complex(double real, double imaginary = 0)
        : real_(real)
        , imaginary_(imaginary)
    {}
    
    double Re() const { return real_; }
    double Im() const { return imaginary_; }
    
    Complex& operator +=(const Complex& rhs) {
        real_ += rhs.real_;
        imaginary_ += rhs.imaginary_;
        return *this;
    }

    Complex& operator ++() {
        ++real_;
        return *this;
    }
    
    const Complex operator ++(int) {
        Complex temp = *this;
        ++(*this);
        return temp;
    }
    
    void print(std::ostream& os) const {
        os << "(" << real_ << "," << imaginary_ << ")";
    }

private:
    double real_, imaginary_;
};

const Complex operator +(Complex lhs, const Complex& rhs) {
    lhs += rhs;
    return lhs;
}

inline std::ostream& operator <<(std::ostream& os, const Complex& num) {
    num.print(os);
    return os;
}

#endif
