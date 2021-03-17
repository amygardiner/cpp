// PHYS 30762 Programming in C++
// Assignment 4
// Amy Gardiner
// Class for complex numbers

#include<iostream>
#include<cmath>

class complex
{
  // Make function to overload operator<< a friend
  friend std::ostream & operator<<(std::ostream &os, const complex &c);
  //Function for overloading >> also a friend
  friend std::istream& operator>> (std::istream &in, complex &c);
private:
  double re,im;
  char neg;
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
    return im*(-1);
  }
  // Overload + operator for addition 
  complex operator+(const complex &c)
  {
    double real_result=c.get_real()+re;
    double im_result=c.get_imaginary()+im;
    complex res{real_result,im_result};
    return res;
  }
  // Overload - operator for subtraction
  complex operator-(const complex &c)
  {
    double real_result=re-c.get_real();
    double im_result=im-c.get_imaginary();
    complex res{real_result,im_result};
    return res;
  }
  // Overload * operator for multiplication, z1*z2
  complex operator*(const complex &c)
  {
    double real_result=c.get_real()*re 
      + (-1)*(c.get_imaginary()*im);
    double im_result=c.get_real()*im
      + re*c.get_imaginary();
    complex res{real_result,im_result};
    return res;
  }
  // Overload / operator for division, z1/z2
  complex operator/(const complex &c)
  {
    double real_result=((c.get_real()*re)+(c.get_imaginary()*im))/(pow(c.get_real(),2)+pow(c.get_imaginary(),2));
    double im_result=((c.get_imaginary()*re*-1)+(im*c.get_real()))/(pow(c.get_real(),2)+pow(c.get_imaginary(),2));
    complex res{real_result,im_result};
    return res;
  }

};

// Function to overload << operator for complex numbers
std::ostream& operator<< (std::ostream &os, const complex &c)
{
    // Since operator<< is a friend of the complex class, we can access complex's members directly.
    os<<"("<<c.re<<" + "<<c.im<<"i"<<")"; 
 
    return os; 
}

// Function to overload >> operator for complex number input
std::istream& operator>> (std::istream &in, complex &c)
{
    in>>c.re;
    in>>c.neg;
    std::cin.ignore();
    in>>c.im;

    if (c.neg=='-'){
      c.im=-1*c.im;
    }
 
    return in;
}

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
  a.calc_modulus();
  a.calc_argument();
  b.calc_modulus();
  b.calc_argument();

  // Get conjugates
  a.calc_conjugate();
  b.calc_conjugate();

  // Get sum, difference, product and quotient of a and b
  complex e{a+b};
  complex f{b-a};
  complex g{a*b};
  complex h{a/b};

  // Print out results, also demonstrating use of overloaded operator<<
  std::cout<<"The sum of a and b is: "<<e<<std::endl;
  std::cout<<"The difference between a and b is: "<<f<<std::endl;
  std::cout<<"The product of a and b is: "<<g<<std::endl;
  std::cout<<"The quotient of a and b is: "<<h<<std::endl;

  std::cout<<"Enter a complex number in the form a+ib: "<<std::endl;

  complex complex_input{};
  std::cin>>complex_input;
  std::cout<<"You entered: "<<complex_input<<std::endl;
  
  return 0;
}
