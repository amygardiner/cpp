// PHYS 30762 Programming in C++
// Assignment 6
// Amy Gardiner 10137582
// Program for 2D and 3D shapes

#include <iostream>
#include <string>

// Base class for shapes
class shape
{
protected:
    std::string name;
public:
    // Default constructor
    shape() : name{"no-name"} {}
    // Parameterised constructor
    shape(const std::string nm) : name{nm} {}
    // Destructor
    ~shape(){}
    std::string shape_name()
    {
        return name;
    }
    friend std::ostream& operator<<(std::ostream&, const shape&); 
};

class rectangle: public shape
{
protected:
    double length;
    double width;
public:
    rectangle() : shape{}, length{}, width{} {}
    rectangle(const std::string nm, const double l, const double w) : shape{nm}, length{l}, width{w} {}
    ~rectangle(){}
    double area() const
    {
        return length*width;
    }
    friend std::ostream& operator<<(std::ostream&, const rectangle&);
};

std::ostream& operator<<(std::ostream& o, const rectangle& re)
{
    o<<"Area of rectangle = "<<re.area()<<std::endl;
    return o;
}

std::ostream& operator<<(std::ostream& o, const shape& sh)
{
    o<<"Shape: "<<sh.name<<std::endl;
    return o;
}
int main() 
{
    rectangle rect1{"rectangle1", 2, 3};
    std::cout<<rect1;
    return 0;
}