/*
This file defines the Table object used to format tabular information.
------------------------------------------------------------
Author: Zhiyu Liu, University of Manchester, 2023.3.3
*/

#ifndef TABLE_HPP
#define TABLE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

/*
Class name: Table
--------------------
Description: The Table class provides a method for formatting and printing an 
object's information in the form of an *width-auto-adjustable* tabular with borders.
User can only initialize the table by passing the rows of the table. Column-initializer is not supported.
----------------------------------------
Attributes:
- headers: a vector of strings representing the headers of the table.
- rows: a vector that consists of the rows of the table, each row is a vector of strings.
        (excluding the header row)
- columns: a vector that consists of the columns of the table, each column is a vector of strings.
- max_length_each_col: a vector of integers representing the maximum length in each column.
----------------------------------------
Methods:
- Table()
    Default constructor.
- Table(std::vector<std::string> headers_in, std::vector<std::vector<std::string>> rows_in)
    Constructor that uses rows to construct the table
    The first argument is a vector of strings that takes in the table headers.
    The second argument is a 2-dimensional vector of strings that takes in the table rows.
    The constructor then gets the columns and maximum lengths in each column using the input headers/rows.
- ~Table() {}
    Destructor.
- get_headers(), get_rows(), get_max_length_each_col()
    Getter methods to protect the object information.
- get_columns()
    A method that returns the columns of the table.
    return type: 2-dimensional vector of strings.
- draw_div_line()
    A method that draws a dividing line between adjacent rows.
- display_table()
    A method that prints the formatted table.
*/
class Table
{
private:
    // Attributes
    std::vector<std::string> headers;              
    std::vector<std::vector<std::string>> rows;    
    std::vector<std::vector<std::string>> columns;  
    std::vector<unsigned> max_length_each_col;
public:
    // Constructors and a destructor
    Table() = default;
    Table(std::vector<std::string> headers_in, std::vector<std::vector<std::string>> rows_in);
    
    ~Table() {}

    // Getters
    std::vector<std::string> get_headers() const {return headers;}
    std::vector<std::vector<std::string>> get_rows() const {return rows;}
    std::vector<unsigned> get_max_length_each_col() const {return max_length_each_col;}

    // Member functions
    std::vector<std::vector<std::string>> get_columns() const;
    void draw_div_line() const;
    void display_table() const;
    
};

// Get the maximum length of each column and stores them in a vector of integers.
std::vector<unsigned> get_max_length(std::vector<std::vector<std::string>> columns)
{
    std::vector<unsigned> vec_max_length;

    for (auto it_col = columns.begin(); it_col != columns.end(); ++it_col) {
        unsigned max_length = 0;
        for (auto it_cell = it_col->begin(); it_cell != it_col->end(); ++it_cell) {
            max_length = std::max(max_length, static_cast<unsigned>(it_cell->length()));
        }
        vec_max_length.push_back(max_length);
    }

    return vec_max_length;
}

// Parameterized constructor.
Table::Table(std::vector<std::string> headers_in, std::vector<std::vector<std::string>> rows_in) :
    headers(headers_in), rows(rows_in) 
{
    columns = get_columns();
    max_length_each_col = get_max_length(columns);
}

std::vector<std::vector<std::string>> Table::get_columns() const
{
    std::vector<std::vector<std::string>> columns;

    // Unsigned integer to track the number of columns in each row.
    unsigned i = 0;

    // Add the header as the first element in each column.
    for (auto it1 = headers.begin(); it1 != headers.end(); ++it1) {
        std::vector<std::string> column{};
        column.push_back(*it1);

        // Add the ith element of each row to each column.
        for (auto it2 = rows.begin(); it2 != rows.end(); ++it2) {
            column.push_back((*it2).at(i));
        }

        columns.push_back(column);
        ++i;
    }
    return columns;
}

void Table::draw_div_line() const
{
    int i = 0;
    for (auto it = headers.begin(); it != headers.end(); ++it) {
        // The length of each cell is given by the maximum length in its column + 2.
        std::cout << "+" << std::setfill('-') << std::setw(max_length_each_col.at(i) + 2) << "";
        ++i;
    }
    std::cout << "+" << std::endl;
}

void Table::display_table() const
{
    draw_div_line();

    // print headers
    int i = 0;  // unsigned integer to track the number of columns
    for (auto it = headers.begin(); it != headers.end(); ++it) {
        std::cout << "|" << std::setfill(' ') << std::setw(max_length_each_col.at(i) + 2);
        std::cout << std::right << *it;
        ++i;
    }
    std::cout << "|" << std::endl;

    draw_div_line();
    
    // print rows
    for (auto it1 = rows.begin(); it1 != rows.end(); ++it1) {
        i = 0;
        for (auto it2 = it1->begin(); it2 != it1->end(); ++it2) {
            std::cout << "|" << std::setfill(' ') << std::setw(max_length_each_col.at(i) + 2);
            std::cout << std::right << *it2;
            ++i;
        }
        std::cout << "|" << std::endl;
        draw_div_line();
    }
}

template <typename T>
std::string to_string_format(const T num)
{
    std::ostringstream oss;
    oss << num;
    return oss.str();
}

#endif