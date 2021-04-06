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
std::ostream& operator<<(std::ostream& o, const shape& sh)
{
    o<<"Shape: "<<sh.name<<std::endl;
    return o;
}
int main() 
{
    shape rect{"rectangle"};
    std::cout<<rect;
    return 0;
}