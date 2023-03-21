[TOC]

# Week 2

## Prelecture

### Dynamic memory allocation

```cpp
// General syntax
DataType1 *my_scalar{new data_type_1};		// memory is assessed with pointer my_scalar
DataTyle2 *my_array{new data_type_2[N]};	// memory is assessed with pointer my_array
// Memory is freed
delete my_scalar;
delete[] my_array;
```

### File streams

```cpp
#include <fstream>
std::ifstream my_input_file; 	// A file stream for reading only
std::ofstream my_output_file;	// A file stream for writing only
std::fstream my_file;		// A file stream for both reading and writing
```

```cpp
my_file.open("data1.dat");	// open file
std::ftstream my_file{"data1.dat"}	// open and attach file to my_file
my_file.close()
```

```cpp
int my_data;
my_file >> my_data;	// extract an integer from the file stream my_file
int my_code{234};
my_file << my_code;	// insert mycode into file stream my_file
```

#### Member functions inherited from `std::basic_ios`

```cpp
if (!my_file.good()){
    // To check if our file opened successfully
    std::cerr << "Error: file could not be opened" << std::endl;
    return(1);
}
```

```cpp
if (!my_file.fail()){
    // To check if data is read successfully
    std::cerr << "Error: could not read data from file" << std::endl;
    return(1);
}
```

```cpp
std::ifstream file("test.txt");
if(!file)  // operator! is used here
{  
    std::cout << "File opening failed\n";
    return EXIT_FAILURE;
}
ba
// typical C++ I/O loop uses the return value of the I/O function
// as the loop controlling condition, operator bool() is used here
for(int n; file >> n; ) {
   std::cout << n << ' ';
}
std::cout << '\n';

if (file.bad())
    std::cout << "I/O error while reading\n";
else if (file.eof())
    std::cout << "End of file reached successfully\n";
else if (file.fail())
    std::cout << "Non-integer data encountered\n";
```

```cpp
constexpr auto max_size = std::numeric_limits<std::streamsize>::max();

std::istringstream input("1\n"
                         "some non-numeric input\n"
                         "2\n");
for (;;)
{
    int n;
    input >> n;

    if (input.eof() || input.bad())
        break;
    else if (input.fail())
    {
        input.clear(); // unset failbit
        input.ignore(max_size, '\n'); // skip bad input
    }
    else
        std::cout << n << '\n';
}
```

```cpp
#include <iostream>
#include <string>
 
int main()
{
    for (char c : {'\n', '4', '1', '.', '3', '\n', 'Z', 'Y', 'X'})
        std::cin.putback(c); // emulate user's input (not portable: see ungetc Notes)
 
    double n;
    while (std::cout << "Please, enter a number: " && !(std::cin >> n))
    {
        std::cin.clear();
        std::string line;
        std::getline(std::cin, line);
        std::cout << line << "\nI am sorry, but '" << line << "' is not a number\n";
    }
    std::cout << n << "\nThank you for entering the number " << n << '\n';
}
```

# Week 3

## Prelecture

### Strings

#### Strings as array of characters

```cpp
// define string
const size_t no_char{100}; 		// Size of array, keep constant as it won’t change
char string1[no_char]; 			//fixed length array to store string
char *string2;
string2 = new char[no_char];
// Get the string filled with something
sprintf(string2, "This is a string that has fewer than 100 characters.");
delete string2;
```

```cpp
#include <cstring>
strcpy(string1,"This is string1");
strcpy(string2,"This is string2");
```

**`sprintf`**

```cpp
// Incorporate non-string data and format it correctly
int sprintf(char *str, const char *format, ...)
```

```cpp
char output_filename[100];
int file_index{123};
sprintf(output_filename, "FileData.%d", file_index);
std::cout << output_filename << std::endl;
```

```cpp
char str[80];
sprintf(str, "Value of pi=%f", M_PI);		// Value of Pi = 3.141593
```

#### Strings from the standard library

```cpp
#include <string>
std::string my_first_string{"Hello, world!"};
std::cout << "Length of string = " << my_first_string.length() << std::endl;
std::cout << "2nd character in string is " << my_first_string[1] << std::endl;
```

```cpp
// Define them from terminal input
std::string input_string;
std::cout << "Endter a phrase: ";
std::cin >> input_string;
```

- This only extracts one word as the input terminates at fist whitspace character (leaving rest of text and newline in buffer)

```cpp
// An entire sentence
getline(std::cin, input_string);
```

**String manipulation**

```cpp
string my_first_string{"Hello, world!"};
string my_second_string{"Hello, world!"};
if (my_first_string == my_second_string)
    std::cout << "Strings match!" << std::endl;
```

```cpp
string joined_string{first_string + second_string};		// join
first_string += second_string; 	// append
```

```cpp
// Extracting
extracted_str = str.substr(0, 4)	
```

#### `sstream`

```cpp
int file_index{123};
ostringstream output_stream;
output_stream << "FileData." << file_index;
string output_filename{output_stream.str()};
std::cout << output_filename << std::endl;
```

```cpp
// clear the content of the buffer
output_stream.str()
```

### Arrays and vectors

#### Iterators

```cpp
std::vector<double>::iterator vector_begin{vector_double.begin()};
std::vector<double>::iterator vector_end{vector_double.end()};
std::vector<double>::iterator vector_iterator;
```

# Week 4

## Lecture

Object-Oriented Programming

- Abstracton: keep data private, alter properties via methods only.
- Encapsulation: keep data private, alter properties via methods only.
- Inheritance: classes can be based on other classes to avoid code duplication.
- Polymorphism: can decide at run-time what methods to invoke for a certain class, based on the object itself.

> How many different access specifiers can we have in class?
>
> > 3, (`private`, `protected`, `public`)
>
> The fields in a class in a C++ program are by default
>
> > `private`
>
> Constructors in a class are used to:
>
> > Initialise objects and construct an object's data
>
> What are the main difference between struct and class?
>
> > Acess in a struct is public by default



# Week 5

## Prelecture

###  `class`

#### `const` in functions

The `const` modifier can be used in functoin parameter lists

```cpp
// Passing by reference
double dot_product(const vector3 &v1, const vector3 &v2);
```

- It guarantees argument cannot be modified inside the function.
- Useful when passing by reference to speed thigns up.

```cpp
// Const member functions
vector3 plus(const vector3 &v) const
```

- It guarantees data members are not modified.

---

#### Objects as function arguments & Returning objects from functions

```cpp
// Example (old-fashioned)
double dot_product(const vector3 &v1, const vector3 &v2)
{
    double result = v1.get_x() * v2.get_x() + v1.get_y() * v2.get_y() + v1.get_z() * v2.get_z()
}
```

```cpp
// Example (key feature of OOP: encapsulation)
// Passing objects to member functions
double dot_product(const vector3 &v) const
{
    return (x * v.x + y * v.y + z * v.z);
}
double dp = b.dot_product(c);
```

```cpp
// Return objects from functionsv
vector3 plus(const vector3 &v) const
{
    vector3 temp{x + v.x, y + v.y, z + v.z}
    return temp;
}
```

#### Operator overloading

```cpp
vector3 operator+(const vector3 &v) const
{
    vector3 temp{x + v.x, y + v.y, z + v.z};
    return temp;
}
vector3 e{b + c};
```

```cpp
// Right addition of a scalar to a vector
vector3 operator+(const double scalar) const
{
    vector3 temp{x + scalar, y + scalar, z + scalar};
}
vector3 f{e + 1.5}
```

```cpp
// Non-member function to left-add scalar to vector
vector3 operator+(double scalar, const vector3 &v)
{
    vector3 temp;
    temp.set_x(scalar + v.get_x());
    temp.set_y(scalar + v.get_y());
    temp.set_z(scalar + v.get_z());
    return temp;
}
```

Functions that are friends are ordinary functions but can access members' data of "friendly" objects.

```cpp
friend vector3 operator+(double scalar, const vector3 &v);
vector3 operator+(const vector3 &v)
{
    vector3 temp{scalar + v.x, scalar + v.y, scalar + v.z};
    return temp;
}
```

## Lecture

```cpp
class class_b; // forward declaration
class class_a 
{
public:
  int function1(class_b& b); // must be public since declared as friend 
  int function2(class_b& b);
};
class class_b 
{
private:
  int b_store;
  friend int class_a::function1(class_b&);
};
int class_a::function1(class_b& b) {return b.b_store;}  //legal since friend
int class_a::function2(class_b& b) {return b.b_store;}  //illegal
int main() {
  return 0;
}
```

```cpp
class class1
{
	friend class friend_class;  // Declare a friend class
public:
    class1() : top_secret{rand()} {}
    void print_member() { std::cout << top_secret << std::endl; }
private:
    int top_secret;
};
class friend_class
{
public:
    void change(class1& object1, int x){object1.top_secret = x;}
};
int main() 
{
    class1 befriended;
    friend_class friendly;
    befriended.print_member();
    friendly.change(befriended,rand());
    befriended.print_member();
}
```

> Operator that cannot be overloaded: `.`, `::`, `?:`, `sizeof`

### Overloading insertion operator `<<`

```cpp
friend vector3 operator+(double scalar, const vector3 &v);
friend std::ostream & operator<<(std::osream &os, const vector3 &v);
```

```cpp
std::ostream & operator<<(std::ostream &os, const vector3 &v)
{
    os << "(" << v.x << v.y << "," << v.z << ")";
    return os;
}
```

### Static (Data) members

```cpp
class item
{
  static int count;
  int number;
public:
  void getdata(int a) {number=a; count ++;}
  void getcount(void)
    {
      std::cout<<"count:"<<count<<"\n";
    }
};
int item:: count;
int main()
{
    item a, b, c; //count is initialized to zero
    a.getcount(); //display count
    b.getcount();
    c.getcount();
    a.getdata(100); //getting data into object a
    b.getdata(200); //getting data into object b
    c.getdata(300); //getting data into object c
    std::cout<<"After reading data"<<"\n";
    a.getcount(); //display count
    b.getcount();
    c.getcount();
    return 0;
}
```

```cpp
int ** const p_int;				// const pointer to (a pointer to an int)
int * const * p_int;			// pointer to (a const pointer to an int)
int const ** p_int;				// pointer to (a pointer to a const int)
int const * const * p_int;		// const pointer to (a const pointer to an int)
```



# Week 6
## Prelecture

### Overload `[]` operator

```cpp
double & dynamic_array::operator[](size_t i)
{
    if(i < 0 || i >=size) {
        throw("OutOfBoundError");
    }
    return array[i];
}
```

### Replicate objects

```cpp
// Copy constructor for deep copying
dynamic_array::dynamic_array(dynamic_array &arr)
{
    array = nullptr;
    size = arr.length();
    if (size > 0) {
        array = new double[size];
        for (size_t i{}; i < size; i++)
            array[i] = arr[i];
    }
}
dynamic_array a3 = a1;
dynamic_array a4{a1};
```

Assignment operator: similar to copy constructor except that we assume the object is already constructed.

```cpp
dynamic_array & dynamic_array::operator=(dynamic_array &arr)
{
    if (&arr == this)
        return *this;
    
    delete[] array;
    array = nullptr;
    size = arr.length();
    
    if (size > 0) {
        array = new double[size];
        for (size_t i{}; i < size; i++)
            array[i] = arr[i];
    }
    return *this;
}
```

The assignment operator



























