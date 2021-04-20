// PHYS 30762 Programming in C++
// Assignment 6
// Amy Gardiner 10137582
// Program for 2D and 3D shapes

#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include<cmath>

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
    virtual void info()=0;
};

class two_dimensional: public shape
{
public:
    two_dimensional() : shape{} {}
    two_dimensional(const std::string nm) : shape{nm} {}
    ~two_dimensional(){}
    void info()
    {
        std::cout<<name<<" has volume = 0"<<std::endl;
    }
};

class three_dimensional: public shape
{
public:
    three_dimensional() : shape{} {}
    three_dimensional(const std::string nm) : shape{nm} {}
    ~three_dimensional(){}
};

class rectangle: public two_dimensional
{
protected:
    double length;
    double width;
public:
    rectangle() : two_dimensional{}, length{}, width{} {}
    rectangle(const std::string nm, const double l, const double w) : two_dimensional{nm}, length{l}, width{w} {}
    ~rectangle(){}
    double area{length*width};
    void info()
    {
        std::cout<<name<<" has area = "<<area<<std::endl;
    }
};

class square: public two_dimensional
{
protected:
    double length;
public:
    square() : two_dimensional{}, length{} {}
    square(const std::string nm, const double l) : two_dimensional{nm}, length{l} {}
    ~square(){}
    double area{pow(length,2)};
    void info()
    {
        std::cout<<name<<" has area = "<<area<<std::endl;
    }
};

class ellipse: public two_dimensional
{
protected:
    double axis1;
    double axis2;
public:
    ellipse() : two_dimensional{}, axis1{}, axis2{} {}
    ellipse(const std::string nm, const double a, const double b) : two_dimensional{nm}, axis1{a}, axis2{b} {}
    ~ellipse(){}
    double area{M_PI*axis1*axis2};
    void info()
    {
        std::cout<<name<<" has area = "<<area<<std::endl;
    }
};

class circle: public two_dimensional
{
protected:
    double radius;
public:
    circle() : two_dimensional{}, radius{} {}
    circle(const std::string nm, const double r) : two_dimensional{nm}, radius{r} {}
    ~circle(){}
    double area{M_PI*pow(radius,2)};
    void info()
    {
        std::cout<<name<<" has area = "<<area<<std::endl;
    }
};

class cuboid: public three_dimensional
{
protected:
    double width;
    double length;
    double height;
public:
    cuboid() : three_dimensional{}, width{}, length{}, height{} {}
    cuboid(const std::string nm, const double w, const double l, const double h) : three_dimensional{nm}, width{w}, length{l}, height{h} {}
    ~cuboid(){}
    double volume{width*length*height};
    void info()
    {
        std::cout<<name<<" has volume = "<<volume<<std::endl;
    }
};

class cube: public three_dimensional
{
protected:
    double length;
public:
    cube() : three_dimensional{}, length{} {}
    cube(const std::string nm, const double l) : three_dimensional{nm}, length{l} {}
    ~cube(){}
    double volume{pow(length,3)};
    void info()
    {
        std::cout<<name<<" has volume = "<<volume<<std::endl;
    }
};

class ellipsoid: public three_dimensional
{
protected:
    double axis1;
    double axis2;
    double axis3;
public:
    ellipsoid() : three_dimensional{}, axis1{}, axis2{}, axis3{} {}
    ellipsoid(const std::string nm, const double a, const double b, const double c) : three_dimensional{nm}, axis1{a}, axis2{b}, axis3{c} {}
    ~ellipsoid(){}
    double volume{(4.0/3.0)*M_PI*(axis1*axis2*axis3)};
    void info()
    {
        std::cout<<name<<" has volume = "<<volume<<std::endl;
    }
};

class sphere: public three_dimensional
{
protected:
    double radius;
public:
    sphere() : three_dimensional{}, radius{} {}
    sphere(const std::string nm, const double r) : three_dimensional{nm}, radius{r} {}
    ~sphere(){}
    double volume{(4.0/3.0)*M_PI*pow(radius,3)};
    void info()
    {
        std::cout<<name<<" has volume = "<<volume<<std::endl;
    }
};

int main() 
{
    shape *shape_array[7];
    shape_array[0]=new rectangle{"Rectangle",2,3};
    shape_array[1]=new square{"Square",2};
    shape_array[2]=new ellipse{"Ellipse",2,3};
    shape_array[3]=new circle{"Circle",5};
    shape_array[4]=new cuboid{"Cuboid",1,2,3};
    shape_array[5]=new cube{"Cube",2};
    shape_array[6]=new ellipsoid{"Ellipsoid",1,2,3};
    shape_array[7]=new sphere{"Sphere",2};
    int i{};
    for(int i{0};i<=7;i++)
        shape_array[i]->info();
        delete shape_array[i];
        shape_array[i]=0;
    std::cout<<std::endl;
    two_dimensional re{"Rectangle"};
    re.info();
    two_dimensional sq{"Square"};
    sq.info();
    two_dimensional el{"Ellipse"};
    el.info();
    two_dimensional ci{"Circle"};
    ci.info();
    return 0;
}