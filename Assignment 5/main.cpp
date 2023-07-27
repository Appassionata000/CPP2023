/*
+-----------------------------------------------------+
| Assignment 5 of Object oriented programming in C++  |
| Zhiyu Liu, University of Mancheseter, 2023.3.3.24   |
+-----------------------------------------------------+
This program demonstrates several class-related C++ functionalities through the usage of a 2D matrix.
Functionalities to be demosntrated:
- Using `new` and `delete` to manage the memory.
- Parameterized/copy/move constructor.
- Overload index operator to modify the data.
- Overload assignment operator to allow deep copying.
- Overload arithmetic operators '+'/'-'/'*' following the matrix arithmetic rules.
- Overload '>>'/'<<' operators to allow input/output manipulation of the object.
- Calculate the determinant of the matrix using recursive method.
*/

#include "matrix.hpp"
#include <limits>

// Utility function to pause the program and wait for the user to press Enter.
void pause_and_continue();

int main()
{
    // Declare and initialize matrix objects and set their data.
    Matrix A{3, 3}, B{3, 3}, C{2, 3}, D{5, 4};

    A.set({1, 2, 3,
           9, 8, 7,
           4, 2, 6});

    B.set({5, 5, 4,
           1, 2, 3,
           6, 9, 8});

    C.set({3, 4, 1,
           2, 5, 6});

    D.set({1,  2,  3,  4,
           5,  6,  7,  8,
           9,  10, 11, 12,
           13, 14, 15, 16,
           17, 18, 19, 20});

    std::cout << "Matrix A:\n" << A << std::endl;
    std::cout << "Matrix B:\n" << B << std::endl;
    std::cout << "Matrix C:\n" << C << std::endl;

    pause_and_continue();

    Matrix A_plus_B = A + B;
    Matrix A_minus_B = A - B;
    Matrix A_times_B = A * B;
    Matrix C_times_B = C * B;

    std::cout << "A + B:\n" << A_plus_B  << std::endl;
    std::cout << "A - B:\n" << A_minus_B << std::endl;
    std::cout << "A * B:\n" << A_times_B << std::endl;
    std::cout << "C * B:\n" << C_times_B << std::endl;

    std::cout << "B * C: ";
    Matrix B_times_C = B * C;

    pause_and_continue();

    // Demonstration of deleteing the ith row and jth column
    std::cout << "Matrix D:\n" << D << std::endl;

    Matrix D_deleted = D.delete_row_column(2, 2);
    std::cout << "Matrix with row 2 and column 2 deleted:\n" << D_deleted << std::endl;

    pause_and_continue();

    // Demonstration of calculating the determinant of A and B.
    double det_A = A.determinant();
    double det_B = B.determinant();
    std::cout << "det(A): " << det_A << ".  det(B): " << det_B << "\n" << std::endl;

    std::cout << "Calculating the determinant of matrix C...";
    double det_C = C.determinant();

    pause_and_continue();

    // Demonstration of copy constructor
    Matrix A_copy = A;
    A(1, 1) = 0;      // Modify the original matrix

    std::cout << "Modified matrix A:\n" << A << std::endl;
    std::cout << "Copied original A:\n" << A_copy << std::endl;

    pause_and_continue();

    // Demonstration of the move constructor
    std::cout << "Matrix D before move:\n" << D << std::endl;
    
    Matrix E {std::move(D)};
    std::cout << "Matrix E after move:\n" << E << std::endl;
    std::cout << "Matrix D after move:\n" << D << std::endl;
    std::cout << "Size of D: " << D.size() << std::endl;
    
    pause_and_continue();

    // Demonstration of constructing the matrix from user input.
    std::cout << "Demonstration of constructing the matrix from user input." << std::endl;
    Matrix M {};
    std::cin >> M;
    std::cout << M << std::endl;

    pause_and_continue();

    // Show that destructors are being called
    Matrix::SHOW_DESTRUCTION_INFO = true;
    
    return 0;
}

void pause_and_continue()
{
    std::cout << std::setw(20) << std::setfill('-') << " " << std::endl;
    std::cout << std::setw(0) << std::setfill(' ');
    std::cout << "Press Enter to Continue...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << std::endl;
}