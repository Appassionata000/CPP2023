# CPP 2023

Course assignments of Objected Oriented Programming in C++ 2023 in the University of Manchester.


```
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
C++                             11            115             88            850
C/C++ Header                     5            125            299            549
-------------------------------------------------------------------------------
```


### Assignment 5: A Matrix Class

Write a C++ class for matrices:
• The class should at least contain the following private data: the number of rows, the number of columns
and a pointer to the matrix data (matrix data should be of type double).
• When constructing a matrix object, dynamic memory allocation should be used to store the matrix data.
• Store the data in a one-dimensional array. For an matrix , the location loc of the element is
then given by
• The and terms are due to the fact that C++ arrays start at zero, while the indices of our
matrices start at 1!
• The destructor should explicitly delete any dynamically allocated memory when called.
• The assignment operator and copy constructor functions should perform deep copies of the data.
• Challenge: a recursive calculation of a determinant.

#### Variadic templates

> (ref)[https://stackoverflow.com/questions/1657883/variable-number-of-arguments-in-c]

```cpp
template<typename T> void func(std::vector<T> vec)
{
    for (typename std::vector<T>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
    {
        std::cout << *iter << std::endl;
    }
}
```
