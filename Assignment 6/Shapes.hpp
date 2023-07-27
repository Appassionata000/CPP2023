/*
This file defines the Matrix class
------------------------------------------------------------
Author: Zhiyu Liu, University of Manchester, 2023.3.24
*/

#ifndef Shape_HPP
#define Shape_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>

/*
Class name: Shape
--------------------
Description:
The `Shape` class is an abstract base class for defining geometric shapes. 
It contains pure virtual functions for calculating the area, volume, and perimeter of a shape, 
and also includes protected data members for the shape's dimension and name. 

The `Shape` class is derived from by two other abstract classes, `Shape_2D` and `Shape_3D`, 
which define the behavior of 2D and 3D shapes, respectively. 
These classes in turn are inherited by concrete classes such as `Rectangle`, `Circle`, `Cube`, etc. 
Each of these derived classes implements the pure virtual functions for area, volume, 
and perimeter in a way that is specific to the particular shape.

Public Methods:
- virtual ~Shape()
    A virtual destructor to ensure proper deletion of derived classes.
- Shape(unsigned int x, std::string n)
    A constructor that takes the dimension and name of the shape as parameters.
- virtual double area() = 0;
    A pure virtual function that returns the area of the shape.
- virtual double volume() = 0;
    A pure virtual function that returns the volume of the shape.
- virtual double perimeter() = 0;
    A pure virtual function that returns the perimeter of the shape.
- unsigned int getDim()
    A function that returns the dimension of the shape.
- std::string getName()
    A function that returns the name of the shape.
*/

class Shape
{
protected:
    unsigned int dim;        // Dimension
    std::string name;        // Name of the shape
public:
    virtual ~Shape() { std::cout << "Shape \"" << name << "\" deleted." << std::endl; }
    Shape(unsigned int x, std::string n) : dim{x}, name{n} {}
    
    virtual double area() = 0;
    virtual double volume() = 0;
    virtual double perimeter() = 0;

    unsigned int getDim() { return dim; }
    std::string getName() { return name; }
};

class Shape_2D : public Shape
{
public:
    Shape_2D(std::string n) : Shape{2, n} {}
    ~Shape_2D() {}
    virtual double area() = 0;
    virtual double perimeter() = 0;
    double volume() { return 0; } // 2D shapes have volume 0
};

class Shape_3D : public Shape
{
public:
    Shape_3D(std::string n) : Shape{3, n} {}
    ~Shape_3D() {}
    virtual double volume() = 0;
    virtual double area() = 0;
    double perimeter() { return 0; } // 3D shapes have perimeter 0
};

class Rectangle : public Shape_2D
{
private:
    double width;
    double height;
public:
    Rectangle() : Shape_2D{"Rectangle"}, width{0}, height{0} {}  // Default constructor
    Rectangle(double w, double h) : Shape_2D{"Rectangle"}, width{w}, height{h} {}
    ~Rectangle() {}

    double area() { return width * height; }
    double perimeter() { return 2 * (width + height); }
};

class Square : public Shape_2D
{
private:
    double length;
public:
    Square() : Shape_2D{"Square"}, length{0} {}
    Square(double l) : Shape_2D{"Square"}, length(l) {}
    ~Square() {}

    double area() { return length * length; }
    double perimeter() { return 4 * length; }
};

class Ellipse : public Shape_2D

{
private:
    double a;
    double b;
public:
    Ellipse() : Shape_2D{"Ellipse"}, a{0}, b{0} {}
    Ellipse(double a, double b) : Shape_2D{"Ellipse"}, a{a}, b{b} {}
    ~Ellipse() {}

    double area() { return M_PI * a * b; }
    double perimeter() { return 2 * M_PI * sqrt((a * a + b * b) / 2); }
};

class Circle : public Shape_2D
{
private:
    double radius;
public:
    Circle() : Shape_2D{"Circle"}, radius{0} {}
    Circle(double r) : Shape_2D{"Circle"}, radius{r} {}
    ~Circle() {}

    double area() { return M_PI * radius * radius; }
    double perimeter() { return 2 * M_PI * radius; }
};

class Cuboid : public Shape_3D
{
private:
    double length;
    double width;
    double height;
public:
    Cuboid() : Shape_3D("Cuboid"), length{0}, width{0}, height{0} {}
    Cuboid(double l, double w, double h) : Shape_3D("Cuboid"), length(l), width(w), height(l) {}
    ~Cuboid() {}

    double area() { return 2 * (length * width + width * height + height * length); };
    double volume() { return length * width * height; };
};

class Cube : public Shape_3D
{  
private:
    double length;
public:
    Cube() : Shape_3D("Cube"), length{0} {}
    Cube(double l) : Shape_3D("Cube"), length{l} {}
    ~Cube() {}

    double area() { return 6 * length * length; };
    double volume() { return length * length * length; };
};

class Sphere : public Shape_3D
{
private:
    double radius;
public: 
    Sphere() : Shape_3D("Sphere"), radius{0} {}
    Sphere(double r) : Shape_3D("Sphere"), radius{r} {}
    ~Sphere() {}

    double area() { return 4 * M_PI * radius * radius; };
    double volume() { return (4.0 / 3.0) * M_PI * radius * radius * radius; };
};

class Ellipsoid : public Shape_3D
{
private:
    double a;
    double b;
    double c;  
public:
    Ellipsoid() : Shape_3D("Ellipsoid"), a{0}, b{0}, c{0} {}
    Ellipsoid(double a, double b, double c) : Shape_3D("Ellipsoid"), a{a}, b{b}, c{c} {}
    ~Ellipsoid() {}

    double area() { return 4 * M_PI * a * b; };
    double volume() { return (4.0 / 3.0) * M_PI * a * b * c; };
};

class Prism : public Shape_3D
{
private:
    double depth;
    Shape *base;
public:
    Prism() : Shape_3D{"Prism"}, depth{0}, base{nullptr} {}
    Prism(Shape *b, double d);
    ~Prism() {}

    double area() { return 2 * base->area() + base->perimeter() * depth; }
    double volume() { return base->area() * depth; }

};

Prism::Prism(Shape *b, double d) : Shape_3D{""}, base(b), depth(d)
{
    if (base->getDim() == 2) {
        base = dynamic_cast<Shape_2D*>(base);
    }
    else {
        std::cout << "Error: Prism base must be a 2D shape\n";
        base = nullptr;
    }
    std::string n = base->getName();
    n += " Prism";
    name = n;
}

#endif