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

class square: public shape
{
protected:
    double length;
public:
    square() : shape{}, length{} {}
    square(const std::string nm, const double l) : shape{nm}, length{l} {}
    ~square(){}
    double area{pow(length,2)};
    void info()
    {
        std::cout<<name<<" has area = "<<area<<std::endl;
    }
};

class ellipse: public shape
{
protected:
    double axis1;
    double axis2;
public:
    ellipse() : shape{}, axis1{}, axis2{} {}
    ellipse(const std::string nm, const double a, const double b) : shape{nm}, axis1{a}, axis2{b} {}
    ~ellipse(){}
    double area{M_PI*axis1*axis2};
    void info()
    {
        std::cout<<name<<" has area = "<<area<<std::endl;
    }
};

class circle: public shape
{
protected:
    double radius;
public:
    circle() : shape{}, radius{} {}
    circle(const std::string nm, const double r) : shape{nm}, radius{r} {}
    ~circle(){}
    double area{M_PI*pow(radius,2)};
    void info()
    {
        std::cout<<name<<" has area = "<<area<<std::endl;
    }
};

class cuboid: public shape
{
protected:
    double width;
    double length;
    double height;
public:
    cuboid() : shape{}, width{}, length{}, height{} {}
    cuboid(const std::string nm, const double w, const double l, const double h) : shape{nm}, width{w}, length{l}, height{h} {}
    ~cuboid(){}
    double volume{width*length*height};
    void info()
    {
        std::cout<<name<<" has volume = "<<volume<<std::endl;
    }
};

class cube: public shape
{
protected:
    double length;
public:
    cube() : shape{}, length{} {}
    cube(const std::string nm, const double l) : shape{nm}, length{l} {}
    ~cube(){}
    double volume{pow(length,3)};
    void info()
    {
        std::cout<<name<<" has volume = "<<volume<<std::endl;
    }
};

class ellipsoid: public shape
{
protected:
    double axis1;
    double axis2;
    double axis3;
public:
    ellipsoid() : shape{}, axis1{}, axis2{}, axis3{} {}
    ellipsoid(const std::string nm, const double a, const double b, const double c) : shape{nm}, axis1{a}, axis2{b}, axis3{c} {}
    ~ellipsoid(){}
    double volume{(4.0/3.0)*M_PI*(axis1*axis2*axis3)};
    void info()
    {
        std::cout<<name<<" has volume = "<<volume<<std::endl;
    }
};

class sphere: public shape
{
protected:
    double radius;
public:
    sphere() : shape{}, radius{} {}
    sphere(const std::string nm, const double r) : shape{nm}, radius{r} {}
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
    return 0;
}