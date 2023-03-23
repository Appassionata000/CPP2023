#ifndef Matrix_HPP
#define Matrix_HPP

#include <iostream>
#include <string>
#include <vector>

class Matrix
{
private:
    size_t rows;
    size_t columns;
    double *data;

public:
    Matrix() = default;
    Matrix(const size_t rows_in, const size_t columns_in);
    ~Matrix();

    double &operator()(size_t row, size_t column);

    size_t size();
    void set_element();
};

Matrix::Matrix(const size_t rows_in, const size_t columns_in) : rows(rows_in), columns(columns_in)
{
    if (rows_in < 1 || columns_in < 1) {
        throw ("Invalid Matrix size");
    }
    data = new double[rows_in * columns_in];
}

// Destructor implementation
Matrix::~Matrix()
{
    delete[] data;
}

double &Matrix::operator() (size_t i, size_t j)
{
    return data[(j - 1) + (i - 1) * columns];
}

size_t Matrix::size()
{
    return rows * columns;
}

void set_element()
{
    
}

#endif