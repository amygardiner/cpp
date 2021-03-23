// PHYS 30762 Programming in C++
// Assignment 5
// Amy Gardiner 10137582
// Program for matrices

#include<iostream>
#include<cmath>

class matrix
{
  private:
    int rows;
    int columns;
    double* data;
  public:
    matrix(double no_rows, double no_columns)
    {
        rows=no_rows; 
        columns=no_columns;
        data=new double[(rows+1)*(columns+1)];
    }
    ~matrix()
    { 
        delete []data;
    }
};

int main()
{ 
    matrix a{3,4};
    return 0;
}