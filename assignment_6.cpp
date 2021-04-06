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
    virtual ~shape(){}
    virtual void info()
    {
        std::cout<<name<<std::endl;
    }
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
    double area{length*width};
    void info()
    {
        std::cout<<name<<" has area = "<<area<<std::endl;
    }
};

int main() 
{
    shape rect1{};
    rectangle rect2{"Rectangle", 2, 3};
    shape *shape_pointer;
    shape_pointer=&rect1;
    shape_pointer->info();
    shape_pointer=&rect2;
    shape_pointer->info();

/* For when all derived classes are made
    shape *shape_array[8];
    shape_array[0]=new shape{};
    shape_array[1]=new rectangle{"Rectangle",2,3};
    shape_array[2]=new square{"Square",2};
    shape_array[3]=new ellipse{"Ellipse",2,3};
    shape_array[4]=new circle{"Circle",2,3};
    shape_array[5]=new cuboid{"Cuboid",2,3};
    shape_array[6]=new cube{"Cube",2};
    shape_array[7]=new ellipsoid{"Ellipsoid",2,3};
    shape_array[8]=new sphere{"Sphere",2};
    for(int i{0};i<=8;i++)
        shape_array[i]->info();
        delete shape_array[i];
        shape_array[i]=0;
*/
    return 0;
}