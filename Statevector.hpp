#ifndef Statevector_HPP
#define Statevector_HPP

#include "format.hpp"
#include <map>

class Statevector
{
private:
    size_t qubit_n;
    std::unique_ptr<std::complex<double>[]> array;

public:
    Statevector();
    Statevector(size_t qubit_n_);
    Statevector(std::initializer_list<int> qubit_states);

    Statevector(const Statevector &s);            // copy constructor
    Statevector &operator=(const Statevector &s); // copy assignment operator
    Statevector(Statevector &&s);                 // move constructor
    Statevector &operator=(Statevector &&s);      // move assignment operator

    std::complex<double> &operator[](size_t i);
    const std::complex<double> &operator[](size_t i) const;

    size_t qubit_num() const { return qubit_n; }
    size_t size() { return pow(2, qubit_n); }

    size_t get_max_width() const;
    void display_row();
    void display_column();
    
    void round();
};

Statevector::Statevector()
{
    qubit_n = 0;
    array = std::make_unique<std::complex<double>[]>(1);
    array[0] = 0;
}

// Constructor for 0 statevector with n qubits
Statevector::Statevector(size_t qubit_n_) : qubit_n(qubit_n_)
{
    size_t array_size = pow(2, qubit_n);
    array = std::make_unique<std::complex<double>[]>(array_size);

    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        array[i] = 0;
    }
}

// Parameterized constructor
Statevector::Statevector(std::initializer_list<int> qubit_states)
{
    qubit_n = qubit_states.size();
    size_t array_size = pow(2, qubit_n);

    array = std::make_unique<std::complex<double>[]>(array_size);
    std::vector<int> qubit_list(qubit_states);

    int pos = 0;
    for (int i = 0; i < qubit_n; i++)
    {
        pos += qubit_list[i] * pow(2, qubit_n - i - 1);
    }

    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        if (i == pos)
            array[i] = 1;
        else
            array[i] = 0;
    }
}

// Copy constructor
Statevector::Statevector(const Statevector &s)
{
    qubit_n = s.qubit_n;
    size_t array_size = pow(2, qubit_n);

    array = std::make_unique<std::complex<double>[]>(array_size);
    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        array[i] = s.array[i];
    }
    this->round();
}

// Copy assignment operator
Statevector &Statevector::operator=(const Statevector &s)
{
    if (this == &s)
        return *this;

    qubit_n = s.qubit_n;
    size_t array_size = pow(2, qubit_n);

    array = std::make_unique<std::complex<double>[]>(array_size);
    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        array[i] = s.array[i];
    }

    this->round();
    return *this;
}

// Move constructor
Statevector::Statevector(Statevector &&s)
{
    qubit_n = s.qubit_n;
    array = std::move(s.array);

    s.qubit_n = 0;
    s.array = std::make_unique<std::complex<double>[]>(1);
    s.array[0] = 0;

    this->round();
}

// Move assignment operator
Statevector &Statevector::operator=(Statevector &&s)
{
    if (this == &s)
        return *this;

    qubit_n = s.qubit_n;
    array = std::move(s.array);

    s.qubit_n = 0;
    s.array = std::make_unique<std::complex<double>[]>(1);
    s.array[0] = 0;

    this->round();
    return *this;
}

// Overloading [] operator
std::complex<double> &Statevector::operator[](size_t i)
{
    if (i >= pow(2, qubit_n))
    {
        std::cout << "Error: trying to access an element out of bounds" << std::endl;
        throw("index out of bounds");
    }
    return array[i];
}

// Overloading [] operator for const objects
const std::complex<double> &Statevector::operator[](size_t i) const
{
    if (i >= pow(2, qubit_n))
    {
        std::cout << "Error: trying to access an element out of bounds" << std::endl;
        throw("index out of bounds");
    }
    return array[i];
}

// Displaying the statevector in row form
void Statevector::display_row()
{
    std::cout << "[";
    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        std::cout << " " << complex_to_str(array[i]) << " ";
    }
    std::cout << "]" << std::endl;
}

// Auxiliary function to get the maximum width of a complex number in the statevector
size_t Statevector::get_max_width() const
{
    size_t max_width = 0;
    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        size_t width = complex_to_str(array[i]).length();
        max_width = std::max(max_width, width);
    }
    return max_width;
}

// Displaying the statevector in column form
void Statevector::display_column() 
{
    size_t width = get_max_width();

    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        if (i == 0)
        {
            std::cout << "┌ ";
            std::cout << std::setw(width) << std::right << complex_to_str(array[i]);
            std::cout << " ┐" << std::endl;
        }
        else if (i == pow(2, qubit_n) - 1)
        {
            std::cout << "└ ";
            std::cout << std::setw(width) << std::right << complex_to_str(array[i]);
            std::cout << " ┘" << std::endl;
        }
        else
        {
            std::cout << "| ";
            std::cout << std::setw(width) << std::right << complex_to_str(array[i]);
            std::cout << " |" << std::endl;
        }
    }
}

// Generate standard basis
std::map<std::string, Statevector> generate_std_basis(size_t qubit_n)
{
    std::map<std::string, Statevector> basis;
    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        Statevector s(qubit_n);
        s[i] = 1;
        std::string ket_representation = "";
        for (int j = qubit_n - 1; j >= 0; j--)
        {
            ket_representation += (i & (1 << j)) ? "1" : "0";
        }

        basis[ket_representation] = s;
    }
    return basis;
}

// Round the statevector to 0 if the absolute value is less than 1e-10
void Statevector::round()
{
    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        if (std::abs(array[i].real()) < 1e-10)
            array[i].real(0);
        if (std::abs(array[i].imag()) < 1e-10)
            array[i].imag(0);
    }
}

#endif // Statevector_HPP
