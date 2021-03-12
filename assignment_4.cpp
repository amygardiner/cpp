// PHYS 30762 Programming in C++
// Assignment 4
// Amy Gardiner
// Class for complex numbers

#include<iostream>
#include<cmath>

class complex
{
  // Make function to overload operator<< a friend
  friend std::ostream & operator<<(std::ostream &os, const complex &z);
private:
  double re,im;
public:
  // Constructors & destructor
  complex(){re=im=0;}
  complex(double real_part, double im_part){re=real_part; im=im_part;}
  ~complex(){}
  // Return real component
  void set_real(const double real_part) 
  {
    re=real_part;
  }
  double get_real() const
  {
    return re;
  }
  // Return imaginary component
  void set_imaginary(const double im_part) 
  {
    im=im_part;
  }
  double get_imaginary() const
  {
    return im;
  }
  // Return modulus
  double calc_modulus() const
  {
    double mod_1{pow(re,2)};
    double mod_2{pow(im,2)};
    double mod_3{mod_1+mod_2};

    return pow(mod_3,0.5);
  }
  // Return argument - need to incorporate +pi if second quadrant result, -pi if third quadrant
  double calc_argument() const
  {
    return atan(im/re);
  }
  // Return complex conjugate
  double calc_conjugate() const
  {
    return im*=(-1);
  }
  // Overload + operator for addition 
  complex operator+(const complex &c)
  {
    double real_result=c.get_real()+re.get_real();
    double im_result=c.get_imaginary()+im.get_imaginary();
    complex c{real_result,im_result};
    return c;
  }
  // Overload - operator for subtraction
  complex operator-(const complex &c)
  {
    double real_result=c.get_real()-re.get_real();
    double im_result=c.get_imaginary()-im.get_imaginary();
    complex c{real_result,im_result};
    return c;
  }
  // Overload * operator for multiplication, z1*z2
  complex operator*(const complex &c)
  {
    double real_result = c.get_real()*re.get_real() 
      + (-1)*(c.get_imaginary()*im.get_imaginary());
    double im_result = c.get_real()*im.get_imaginary()
      + re.get_real()*c.get_imaginary();
    complex c{real_result, im_result};
    return c;
  }
  // Overload / operator for division, z1/z2

};

// Function to overload << operator for complex numbers

int main()
{  
  std::cout.precision(3);

  // Create two complex numbers
  complex a{3,4};
  complex b{1,-2};

 // Get real and imaginary components, modulus and argument
  a.get_real();
  a.get_imaginary();
  b.get_real();
  b.get_imaginary();

  // Get conjugates

  // Get sum, difference, product and quotient of a and b
  complex e{a+b};
  complex f{b-a};
  complex g{a*b};

  // Print out results, also demonstrating use of overloaded operator<<

  // Show results of overloading arithmetic operators

  return 0;
}
