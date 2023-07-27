/*
+-----------------------------------------------------+
| Assignment 5 of Object oriented programming in C++  |
| Zhiyu Liu, University of Mancheseter, 2023.3.3.24   |
+-----------------------------------------------------+
This program is to implement a class hierarchy for geometric shapes.
The program will have a base class Shape and derived classes Rectangle, Square, Ellipse, Circle, Cuboid, Cube, Ellipsoid, and Sphere.
The program will also have a class Prism that is derived from Shape and has a Shape as a member variable.
The program will have a class Table that will display a table of shapes.
*/

#include "Shapes.hpp"
#include "Table.hpp"

void pause_and_continue();

int main()
{
    // Implement an array or vector of at least 8 base class pointers, each pointing to a different shape ;
    std::vector<Shape *> shapes;
    shapes.push_back(new Rectangle(2, 3));
    shapes.push_back(new Square(1));
    shapes.push_back(new Ellipse(1, 2));
    shapes.push_back(new Circle(1));
    shapes.push_back(new Cuboid(1, 2, 3));
    shapes.push_back(new Cube(1));
    shapes.push_back(new Ellipsoid(1, 2, 3));
    shapes.push_back(new Sphere(1));

    shapes.push_back(new Prism(shapes.at(0), 1));
    shapes.push_back(new Prism(shapes.at(1), 1));
    shapes.push_back(new Prism(shapes.at(2), 1));
    shapes.push_back(new Prism(shapes.at(3), 1));

    // Display the table of shapes
    std::vector<std::string> headers{"Dim", "Shape", "Area", "Volume"};
    std::vector<std::string> row{};
    std::vector<std::vector<std::string>> rows{};

    for (auto it = shapes.begin(); it != shapes.end(); ++it)
    {
        row.clear();
        row.push_back(to_string_format((*it)->getDim()));
        row.push_back((*it)->getName());
        row.push_back(to_string_format((*it)->area()));
        row.push_back(to_string_format((*it)->volume()));
        rows.push_back(row);
    }

    Table table(headers, rows);
    table.display_table();

    pause_and_continue();

    // Delete all the shapes
    std::cout << std::endl;
    for (auto it = shapes.begin(); it != shapes.end(); ++it)
    {
        delete *it;
    }

    return 0;
}


void pause_and_continue()
{
    std::cout << "\nPress Enter to Continue...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << std::endl;
}