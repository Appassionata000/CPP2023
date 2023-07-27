/*
This file defines the Complex class, which represents a complex number.
The object has two attributes: real part and the imaginary part
------------------------------------------------------------
Author: Zhiyu Liu, University of Manchester, 2023.3.10
*/

#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <cmath>
#include <sstream>
#include <cstdlib>
#include "Table.hpp"

/*
Class name: Complex
--------------------
Description: The Complex class contains the real and imaginary part of the complex number.
User can initialize the object by a parameterized constructor or through an input stream.
------------------------------------------------------------
Attributes:
- real: (double type) real part of the complex number
- imaginary: (double type) imaginary part of the complex number
------------------------------------------------------------
Methods:
- Complex()
    Default constructor.
- Complex(double real_in, double imaginary_in)
    Parameterized constructor.
- ~Complex()
    Destructor
- get_real() const, get_imaginary() const 
    Getters
- get_modulus() const, get_argument()
    Get the modulus/argument of the complex number. Return type: double
    The argument is calculated by arctan(Im(z)/Re(z))
- get_conjuate() const
    Return a Complex object which is the complex conjugate of the original object
- operator+, operator-, operator*, operator/
    Overloaded operators follow the rules of complex number arithmetic.
- str()
    Convert the complex object to a string
- display_info()
    Display the information of the object using Table.hpp
*/

class Complex
{
friend std::ostream& operator<<(std::ostream& os, const Complex& c);
friend std::istream& operator>>(std::istream& is, Complex& complex_in);
friend std::ostream& print_paren(std::ostream& os, const Complex& c);
private:
    double real;
    double imaginary;

public:

    Complex() = default;
    Complex(double real_in, double imaginary_in) : real{real_in}, imaginary{imaginary_in} {};
    ~Complex() {}

    double get_real() const { return real; }
    double get_imaginary() const { return imaginary; }
    double get_modulus() const { return sqrt(pow(real, 2) + pow(imaginary, 2)); }
    double get_argument() const { return std::atan2(imaginary, real); }
    Complex get_conjugate() const;

    Complex operator+(const Complex& c) const;
    Complex operator-(const Complex& c) const;
    Complex operator*(const Complex& c) const;
    Complex operator/(const Complex& c) const;

    std::string str() const;
    void display_info() const;
};

Complex Complex::get_conjugate() const
{
    return Complex{real, -1 * imaginary};
}

Complex Complex::operator+(const Complex& c) const
{
    return Complex{real + c.real, imaginary + c.imaginary};
}

Complex Complex::operator-(const Complex& c) const
{
    return Complex{real - c.real, imaginary - c.imaginary};
}

Complex Complex::operator*(const Complex& c) const
{
    return Complex{real * c.real - imaginary * c.imaginary,
                   real * c.imaginary + c.real * imaginary};
}

Complex Complex::operator/(const Complex& c) const
{
    double denominator = pow(c.real, 2) + pow(c.imaginary, 2);
    return Complex{(real * c.real + imaginary * c.imaginary) / denominator,
                   (c.real * imaginary - real * c.imaginary) / denominator};
}

std::string Complex::str() const
{
    std::ostringstream oss;
    oss << real << (imaginary >= 0 ? "+" : "") << imaginary << "i";
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Complex& c)
{
    os << c.real << (c.imaginary >= 0 ? "+" : "") << c.imaginary << "i";
    return os;
}

/*
Possible input number:
1.11+2.22i  1.11-2.22i  -1.11+2.22i  -1.11-2.22i
1.11   -1.11   2.22i   -2.22i
This function categorize these situations separately using if/else conditions
*/
std::istream& operator>>(std::istream& is, Complex& complex_in)
{
    std::string input;
    is >> input;

    std::string real_str, imag_str;
    int real_sign = 1;
    int imag_sign = 1;
    
    // Get the position of the delimeters
    auto plus_pos = input.find_first_of("+");
    auto minus_pos = input.find_first_of("-");
    // The input number may have two minus signs. eg: -1-2i
    auto minus_pos_2 = input.find_first_of("-", 1);
    auto i_pos = input.find_first_of("i");

    if (plus_pos != std::string::npos && i_pos != std::string::npos) {
        // Have real part and imaginary part
        imag_sign = 1;
        if (minus_pos == std::string::npos) {
            // eg: 1.4+3.2i
            real_sign = 1;
            real_str = input.substr(0, plus_pos);
            imag_str = input.substr(plus_pos+1, i_pos);
        } else if (minus_pos == 0) {
            // eg: -1.4+3.2i
            real_sign = -1;
            real_str = input.substr(1, plus_pos);
            imag_str = input.substr(plus_pos+1, i_pos);
        }
    } 
    else if (plus_pos == std::string::npos) {
        if (minus_pos_2 == std::string::npos){
            // Have only real part or imaginary part
            if (i_pos == std::string::npos) {
                // Only have real part
                if (minus_pos == std::string::npos) {
                    // eg: 3.23
                    real_sign = 1;
                    real_str = input;
                } else if (minus_pos == 0) {
                    // eg: -3.23
                    real_sign = -1;
                    real_str = input.substr(1, input.length() - 1);
                }
            } else {
                // Only have imaginary part
                if (minus_pos == std::string::npos) {
                    // eg: 1.23i
                    imag_sign = 1;
                    imag_str = input.substr(0, i_pos);
                } else if (minus_pos == 0) {
                    // eg: -1.23i
                    imag_sign = -1;
                    imag_str = input.substr(1, input.length() - 1);
                }
            }
        } else {
            // two minus sign. eg: -1.3-2.2i
            real_sign = -1;
            imag_sign = -1;
            real_str = input.substr(1, minus_pos_2);
            imag_str = input.substr(minus_pos_2 + 1, i_pos);
        }

    }

    // Set number to 0 if the input is not valid
    try{
        if (!real_str.empty()) {
            if (!imag_str.empty()) {
                complex_in.real = real_sign * std::atof(real_str.c_str());
                complex_in.imaginary = imag_sign * std::atof(imag_str.c_str());
            } else {
                complex_in.real = real_sign * std::atof(real_str.c_str());
                complex_in.imaginary = 0;
            }
        } else {
            if (!imag_str.empty()) {
                complex_in.real = 0;
                complex_in.imaginary = imag_sign * std::atof(imag_str.c_str());
            } 
        }
    } catch(...){
        complex_in.real = 0;
        complex_in.imaginary = 0;
    }


    return is;
}

void Complex::display_info() const
{
    std::vector<std::string> header{"Number", "Real", "Imaginary", "Modulus", "Argument", "Conjugate"};
    std::vector<std::vector<std::string>> rows;
    std::vector<std::string> row {this->str(), to_string_format(real),
                                               to_string_format(imaginary),
                                               to_string_format(this->get_modulus()),
                                               to_string_format(this->get_argument()),
                                               this->get_conjugate().str()};
                                            
    rows.push_back(row);
    Table complex_info{header, rows};
    complex_info.display_table();
}

// Print the complex number surrounded by a parenthesis
std::ostream& print_paren(std::ostream& os, const Complex& c)
{
    os << "(" << c.real << (c.imaginary >= 0 ? "+" : "") << c.imaginary << "i)";
    return os;
}

// Print the result of overloading operations.
std::ostream& print_result(std::ostream& os, std::string op, const Complex& c1, const Complex& c2)
{
    print_paren(os, c1);
    std::cout << " " << op << " ";
    print_paren(os, c2);
    std::cout << " = ";
    if (op == "+")      print_paren(os, c1 + c2); 
    else if (op == "-") print_paren(os, c1 - c2);
    else if (op == "*") print_paren(os, c1 * c2);
    else if (op == "/") print_paren(os, c1 / c2);
    std::cout << std::endl;
    return os;
}

#endif