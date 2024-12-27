//
// Created by wtc on 2024/12/25.
//
class Complex {
public:
    int real;
    int imaginary;

    Complex operator+(const Complex& other) {
        this->real += other.real;
        this->imaginary += other.imaginary;
    }
};