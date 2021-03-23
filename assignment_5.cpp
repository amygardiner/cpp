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
    double* array{nullptr};
  public:
    matrix(size_t no_rows, size_t no_columns);
    ~matrix()
    { 
        delete array;
    }
};
matrix::matrix(size_t no_rows, size_t no_columns)
{
    if(no_rows<1||no_columns<1)
    {
        std::cout<<"The array must have positive size"<<std::endl;
        throw("size not positive");
    }
    rows=no_rows;
    columns=no_columns;
    size_t length=(rows+1)*(columns+1);
    array=new double[length];
    for(size_t i{};i<length;i++) array[i]=1;
}
int main()
{ 
    matrix a{3,4};
    matrix b{3,4};
    return 0;
}