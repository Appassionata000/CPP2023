/*
This file defines the Matrix class
------------------------------------------------------------
Author: Zhiyu Liu, University of Manchester, 2023.3.24
*/

#ifndef Matrix_HPP
#define Matrix_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>

/*
Class name: Matrix
--------------------
Description:
The matrix class store the elements of a 2D matrix in a 1D array in the following way,

     0    1     2      3                   (2-1)*4+(3-1) => data[6]
0 ┌  x    x     x      x ┐                            ↓ 
1 |  x    x   (2, 3)   x |  ==> data [ x  x  x  x  x  x  (2, 3) x ....  ]
2 |  x    x     x      x |             0  1  2  3  4  5    6
3 └  x    x     x      x ┘4x4

The (a, b) element in mxn matrix => data[(a-1)*n + (b-1)].
------------------------------------------------------------
Private Attributes:
- rows (type: size_t) number of rows of the matrix.
- columns (type: size_t) number of columns of the matrix.
- data (type: double*) array used to store the elements.
------------------------------------------------------------
Public Methods:
- Matrix()
    Default constructor.
- Matrix(const size_t rows_in, const size_t columns_in)
    Parameterized constructor. Take in the number of rows and columns and allocate memory for the data array.
- ~Matrix()
    Destructor. Delete the allocated memory.
- Matrix(const Matrix &m)
    Copy constructor. Clear the original data and deep copy the data from m.
- Matrix(Matrix &&m)
    Move constructor. Take in rvalue data to construct the object.
- double& operator()(size_t row, size_t column)
    Overload index operator. Return the reference of the element to allow modification.
- Matrix operator+(const Matrix& m) const;
    Overload the '+' operator following the matrix addtion rule. Return a new matrix.
- Matrix operator-(const Matrix& m) const;
    Overload the '-' operator following the matrix subtraction rule. Return a new matrix.
- Matrix operator*(const Matrix& m) const;
    Overload the '*' operator following the matrix multiplication rule. Return a new matrix.
- double determinant();
    Return the determinant of the matrix. The shape of the matrix must square.
- Matrix delete_row_column(size_t i, size_t j) const
    Delete the row i and column j of the original matrix and return the deleted matrix.
- size_t* get_width() const;
    Get the maximum width of each column and store them in an array. Auxiliary function for formatted printing.
- void display() const
    Display the matrix in formatted form.
------------------------------------------------------------
Public Attributes:
- static bool SHOW_DESTRUCTION_INFO;
    Variable for printing information about the destruction of the object.
- static bool SHOW_MOVE_INFO;
- static bool SHOW_COPY_INFO;
    Variables for printing information about which constructor (move/copy) is being used
------------------------------------------------------------
Friend functions:
- friend std::ostream& operator<<(std::ostream& os, const Matrix& m)
    Overload the '<<' operator to print the formatted form of the matrix. This has the same effect as using 
    the display() method while providing a way to integrate into the output stream.
- friend std::istream& operator>>(std::istream& is, Matrix& m_in)
    Overload the '>>' operator to construct the matrix object from user input.
*/


class Matrix
{
friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
friend std::istream& operator>>(std::istream& is, Matrix& m_in);
private:
    size_t rows;
    size_t columns;
    double *data;

public:
    Matrix() = default;
    Matrix(const size_t rows_in, const size_t columns_in);  // Parameterized constructor
    ~Matrix();                      // Destructor
    Matrix(const Matrix &m);        // Copy constructor
    Matrix(Matrix &&m);             // Move constructor

    double& operator()(size_t row, size_t column);  // Overload index operator
    Matrix& operator=(const Matrix& m);   // Assignment operator
    Matrix& operator=(Matrix &&m);        // Move assignment operator

    size_t size() const;
    void set(std::initializer_list<double> elements);

    Matrix operator+(const Matrix& m) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;
    double determinant();

    Matrix delete_row_column(size_t i, size_t j) const;

    size_t* get_width() const;
    void display() const;

    static bool SHOW_DESTRUCTION_INFO;
    static bool SHOW_MOVE_INFO;
    static bool SHOW_COPY_INFO;
};

// Parameterized constructor implementation
Matrix::Matrix(const size_t rows_in, const size_t columns_in) : rows(rows_in), columns(columns_in)
{
    if (rows_in < 1 || columns_in < 1)
    {
        throw("Invalid Matrix size");
    }
    data = new double[rows_in * columns_in];
}

// Destructor implementation
Matrix::~Matrix()
{
    if (SHOW_DESTRUCTION_INFO)
    {
        // Display information about the object to be destructed.
        std::cout << "Destructing Matrix with size " << this->size();
        std::cout << " and first row ";
        for (int i = 0; i < columns; ++i) 
        {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    delete[] data;
}

// Copy constructor implementation
Matrix::Matrix(const Matrix &m) : rows(m.rows), columns(m.columns)
{
    if (SHOW_COPY_INFO)
        std::cout << "Using copy constructor" << std::endl;

    data = nullptr;
    auto size = m.size();

    if (size > 0)
    {
        data = new double[size];
        for (size_t i = 0; i < size; ++i)
            data[i] = m.data[i];
    }
}

// Move constructor implementation
Matrix::Matrix(Matrix &&m) : rows(m.rows), columns(m.columns), data(m.data)
{
    if (SHOW_MOVE_INFO)
        std::cout << "Using move constructor" << std::endl;

    m.rows = 0;
    m.columns = 0;
    m.data = nullptr;
}

// Assignment operator implementation
Matrix& Matrix::operator=(const Matrix& m)
{
    if (SHOW_COPY_INFO)
        std::cout << "Using deep copy assignment operator" << std::endl;

    // Avoid self assignment.
    if (&m == this)
        return *this;
    
    delete[] data;
    data = nullptr;
    rows = m.rows;
    columns = m.columns;
    auto size = m.size();

    if (size > 0)
    {
        data = new double[size];
        for (size_t i = 0; i < size; ++i)
            data[i] = m.data[i];
    }
    return *this;
}

// Move assignment operator implementation
Matrix& Matrix::operator=(Matrix &&m)
{
    if (SHOW_MOVE_INFO)
        std::cout << "Using move assignment operator" << std::endl;

    std::swap(rows, m.rows);
    std::swap(columns, m.columns);
    std::swap(data, m.data);
    
    return *this;
}

// Overload operator() to get the matrix element with row, col indices
double& Matrix::operator()(size_t i, size_t j)
{
    return data[(j - 1) + (i - 1) * columns];
}

// Get the number of elements in the matrix
size_t Matrix::size() const
{
    return rows * columns;
}

// Set elements for the matrix once and for all
void Matrix::set(std::initializer_list<double> elements)
{
    int i = 1, j = 1;

    for (auto it = elements.begin(); it != elements.end(); ++it)
    {
        data[(i - 1) * columns + (j - 1)] = *it;
        if (j == columns)
        {
            ++i;
            j = 1;
        }
        else
        {
            ++j;
        }
    }
}

// Overload operator '+' implementation
Matrix Matrix::operator+(const Matrix& m) const
{
    Matrix result {rows, columns};
    if (rows == m.rows && columns == m.columns)
    { 
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.data[i] = data[i] + m.data[i]; 
        }
    }
    else 
    {
        std::cout << "Matrices must have the same shape" << std::endl;
    }
    return result;   
}

// Overload operator '-' implementation
Matrix Matrix::operator-(const Matrix& m) const
{
    Matrix result {rows, columns};
    if (rows == m.rows && columns == m.columns)
    {
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.data[i] = data[i] - m.data[i]; 
        }
    }
    else 
    {
        std::cout << "Matrices must have the same shape" << std::endl;
    }
    return result;   
}

// Overload operator '*' implementation
Matrix Matrix::operator*(const Matrix& m) const
{
    Matrix result {rows, m.columns};
    if (columns == m.rows) 
    {
        for (int i = 1; i <= rows; ++i)
        {
            for (int j = 1; j <= m.columns; ++j)
            {
                // Get the (i, j) element of the result
                double sum = 0;
                for (int k = 1; k <= columns; ++k)
                {
                    sum += data[(i - 1) * columns + (k - 1)] * m.data[(k - 1) * columns + (j - 1)];
                }
                result.data[(i - 1) * columns + (j - 1)] = sum;
            }
        }
    }
    else
    {
        std::cout << "The columns of the first matrix should be equal to the rows of the second matrix" << std::endl;
    }
    return result;
}

/*
| 1 2 3 |        | 8 7 |              | 9 7 |            | 9 8 |
| 9 8 7 | =  1 * | 2 6 | + (-1) * 2 * | 4 6 | + 1 * 3 *  | 4 2 |
| 4 2 6 |        

| 8 7 |
| 2 6 |  = 1 * 8 * 6 * (-1) * 7 * 2
*/
double Matrix::determinant()
{
    double result = 0;

    if (rows == columns) 
    {
        if (rows > 1)
        {
            for (int j = 1; j <= columns; ++j)
            {
                Matrix minor = this->delete_row_column(1, j);
                int sign = pow(-1, j);
                result += sign * data[j - 1] * (minor.determinant());
            }
            return result;
        }
        else
        {
            result = data[0];
            return result;
        }
    }
    else
    {
        std::cout << "This is not a square matrix." << std::endl;
        return 0;
    }
}

// Create a new matrix object with the ith row and jth column deleted from the original matrix
Matrix Matrix::delete_row_column(size_t i, size_t j) const
{
    Matrix result {rows - 1, columns - 1};

    int e = 0;

    for (int ri = 1; ri <= rows; ++ri)
    {
        for (int rj = 1; rj <= columns; ++rj)
        {
            if (ri != i && rj != j)
            {
                result.data[e] = data[(ri - 1) * columns + (rj - 1)];
                ++e;
            }   
        }
    }
    return result;
}

size_t* Matrix::get_width() const
{
    size_t *width = new size_t[columns];

    for (int j = 0; j < columns; ++j)
    {
        size_t longest = 0;
        for (int i = 0; i < rows; ++i)
        {
            std::ostringstream oss;
            oss << data[i * columns + j];
            std::string str = oss.str();
            longest = std::max(longest, str.length());
        }
        width[j] = longest;
    }
    
    return width;
}

void Matrix::display() const
{
    int i = 1, j = 1;
    size_t *width = this->get_width();

    for (i = 1; i <= rows; ++i, j = 1)
    {
        if (i == 1 && j == 1) { std::cout << "┌ "; }
        else if (i == rows && j == 1) { std::cout << "└ "; }
        else { std::cout << "| "; }

        for (j = 1; j <= columns; ++j)
        {
            std::cout << std::setw(width[j - 1]) << std::right << data[(i - 1) * columns + (j - 1)] << " ";
        }

        if (i == 1 && j == columns + 1) { std::cout << "┐" << std::endl; }
        else if (i == rows && j == columns + 1) { std::cout << "┘" << std::endl; }
        else { std::cout << "|" << std::endl; }
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    int i = 1, j = 1;
    size_t *width = m.get_width();
    
    for (i = 1; i <= m.rows; ++i, j = 1)
    {
        if (i == 1 && j == 1) { os << "┌ "; }
        else if (i == m.rows && j == 1) { os << "└ "; }
        else { os << "| "; }

        for (j = 1; j <= m.columns; ++j)
        {
            os << std::setw(width[j - 1]) << std::right << m.data[(i - 1) * m.columns + (j - 1)] << " ";
        }

        if (i == 1 && j == m.columns + 1) { std::cout << "┐" << std::endl; }
        else if (i == m.rows && j == m.columns + 1) { std::cout << "┘" << std::endl; }
        else { std::cout << "|" << std::endl; }
    }

    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m_in)
{
    size_t rows, columns;

    std::cout << "Please enter the number of rows: ";
    is >> rows;
    std::cout << "Please enter the number of columns: ";
    is >> columns;

    Matrix temp{rows, columns};

    std::cout << "Please enter the matrix elements in the form shown below\n";
    std::cout << "1 2 3\n";
    std::cout << "2 3 4\n";
    std::cout << "5 6 7\n";
    std::cout << "Your matrix: " << std::endl;

    for (size_t i = 1; i <= rows; ++i)
    {
        for (size_t j = 1; j <= columns; ++j)
        {
            is >> temp.data[(i - 1) * columns + (j - 1)];
        }
    }

    m_in = std::move(temp);

    return is;
}


bool Matrix::SHOW_DESTRUCTION_INFO = 0;
bool Matrix::SHOW_MOVE_INFO = 0;
bool Matrix::SHOW_COPY_INFO = 0;

#endif