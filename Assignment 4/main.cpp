/*
+-----------------------------------------------------+
| Assignment 4 of Object oriented programming in C++  |
| Zhiyu Liu, University of Mancheseter, 2023.3.3      |
+-----------------------------------------------------+
This program demonstrates the usage of operator overloading for arithmetic operations
and the insertion operator to insert complex numbers into an ostream
and an extraction operator to read a complex number from an istream
*/
#include "Complex.hpp"
#include "Table.hpp"
#include <iomanip>

int main()
{
    Complex c1{3, 4}, c2{1, -2}, c3{-1, 3};

    // Store the complex numbers in a vector and demonstrate their properties using Table.hpp
    std::vector<Complex> complex_list;
    complex_list.push_back(c1); complex_list.push_back(c2); complex_list.push_back(c3);

    std::vector<std::string> header{"Number", "Real", "Imaginary", "Modulus", "Argument", "Conjugate"};
    std::vector<std::vector<std::string>> rows;

    for (auto it = complex_list.begin(); it != complex_list.end(); ++it) {
        std::vector<std::string> row {it->str(), to_string_format(it->get_real()), 
                                                 to_string_format(it->get_imaginary()),
                                                 to_string_format(it->get_modulus()),
                                                 to_string_format(it->get_argument()),
                                                 it->get_conjugate().str()};
        rows.push_back(row);
    }

    std::cout << "\nWelcome to the program! " << std::endl;
    std::cout << "\nDemonstration of getting properties of a complex number: " << std::endl;  

    Table complex_info{header, rows};
    complex_info.display_table();

    std::cout << "\nDemonstration of overloading arithmetic operators +, -, *, /: " << std::endl;

    print_result(std::cout, "+", c1, c2);
    print_result(std::cout, "-", c1, c2);
    print_result(std::cout, "*", c1, c2);
    print_result(std::cout, "/", c1, c2);

    std::cout << "\nDemonstrator of using istream to construct a complex object" << std::endl;

    Complex c;
    std::string process{"y"};

    while (process == "y") {
        std::cout << "Please enter a complex number: ";
        std::cin >> c;
        std::cout << "Your complex number: " << std::endl;
        c.display_info();
        std::cout << "Do you want to continue (y/n)? ";
        std::cin >> process;
    }

    return 0;

}