// PHYS 30762 Programming in C++
// Assignment 5
// Amy Gardiner 10137582
// Program for matrices

#include<iostream>
#include<cmath>

class matrix
{
  private:
    size_t rows{};
    size_t columns{};
    size_t size{};
    double* array{nullptr};
  public:
    matrix(size_t no_rows, size_t no_columns);
    ~matrix()
    { 
        delete array;
    }
    size_t length() const 
    {
        return rows*columns;
    }
    matrix(matrix&); //copy
    matrix& operator=(matrix&); //copy assignment
    matrix(matrix&&); //move
    matrix& operator=(matrix&&); //move assignment
    double & operator[](size_t i);
};
// Copy constructor
matrix::matrix(matrix &arr)
{
  // Copy size and declare new array
  array=nullptr; 
  size=arr.length();
  if(size>0)
    {
      array=new double[size];
      for(size_t i{};i<size;i++) array[i] = arr[i];
    }
}
// Copy assignment operator
matrix & matrix::operator=(matrix &arr)
{
  if(&arr == this) return *this; 
  delete[] array; 
  array=nullptr; 
  size=0;
  size=arr.length();
  if(size>0)
    {
      array=new double[size];
      for(size_t i{};i<size;i++) array[i] = arr[i];
    }
  return *this;
}
// Move constructor
matrix::matrix(matrix &&arr)
{ // steal the data
  std::cout <<"move constructor\n";
  size=arr.size;
  array=arr.array;
  arr.size=0;
  arr.array=nullptr;
}
// Move assignment operator
matrix & matrix::operator=(matrix&& arr)
{
  std::cout <<"Move assignment\n";
  std::swap(size,arr.size);
  std::swap(array,arr.array);
  return *this;
}
// Parameterised constructor
matrix::matrix(size_t no_rows, size_t no_columns)
{
    if(no_rows<1||no_columns<1)
    {
        std::cout<<"The array must have positive size"<<std::endl;
        throw("size not positive");
    }
    rows=no_rows;
    columns=no_columns;
    size_t length=rows*columns;
    array=new double[length];
    for(size_t i{};i<length;i++) array[i]=1;
}
// Overloaded element [] operator implementation
double & matrix::operator[](size_t i)
{
  if(i<0 || i>=size)
    {
      std::cout<<"Error: trying to access array element out of bounds"<<std::endl;
      throw("Out of Bounds error");
    }
  return array[i];
} 
int main()
{ 
    matrix a{3,4};
    matrix b{6,7};
    std::cout<<"Length of a = "<<a.length()<<std::endl;
    std::cout<<"Length of b = "<<b.length()<<std::endl;
    std::cout<<"Copying values from a to b by assignment"<<std::endl;
    b=a;
    std::cout<<"Length of b is now = "<<b.length()<<std::endl;
    matrix c{3,4};
    c=std::move(a);
    return 0;
}