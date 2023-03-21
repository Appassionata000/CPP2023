/*
Examples from course video.
Can be found in https://github.com/UofM-PHYS30762/prelecture-codes/tree/main/Prelecture5
*/

#include <iostream>

class vector3
{
friend vector3 operator+(double scalar, const vector3 &v);
private:
    double x{};
    double y{};
    double z{};
public:
    // Constructors and destructor
    vector3() = default;
    vector3(double x_in, double y_in, double z_in) : x{x_in}, y{y_in}, z{z_in} {}
    ~vector3() {std::cout << "Destroying vector" << std::endl;}

    // Access functions to set and get vector components
    void set_x(const double x_in) { x = x_in; }
    void set_y(const double y_in) { x = y_in; }
    void set_z(const double z_in) { x = z_in; }
    double get_x() const { return x; }
    double get_y() const { return y; }
    double get_z() const { return z; }

    void show() const { std::cout << "(" << x << "," << y << "," << z << ")" << std::endl; }
    void add_scalar(const double s) { x += s; y += s; z += s; }
    double dot_product(const vector3 &v) const { return (x * v.x + y * v.y + z * v.z); }
    vector3 plus(const vector3 &v) const;

    // Operator overloading
    vector3 operator+(const vector3 &v) const;
    vector3 operator+(const double scalar) const;
};

vector3 vector3::plus(const vector3 &v) const
{
    vector3 temp{x + v.x, y + v.y, z + v.z}
    return temp;
}

vector3 vector3::operator+(const vector3 &v) const
{
    vector3 temp{x + v.x, y + v.y, z + v.z};
    return temp;
}

vector3 vector3::operator+(const double scalar) const
{
    vector3 temp{x + scalar, y + scalar, z + scalar};
    return temp;
}

vector3 operator+(double scalar, const vector3 &v)
{
    vector3 temp{scalar + v.x, scalar + v.y, scalar + v.z};
    return temp;
}