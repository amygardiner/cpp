// PHYS 30762 Programming in C++
// Assignment 5
// Amy Gardiner 10137582
// Program for matrices

#include<iostream>
#include<cmath>

class matrix
{
  friend std::ostream & operator<<(std::ostream &os, const matrix &arr);
  private:
    int rows{};
    int columns{};
    size_t size{};
    double* array{nullptr};
  public:
    // Parameterised constructor
    matrix(int no_rows, int no_columns);
    // Destructor
    ~matrix()
    { 
        delete array;
        rows=0;
        columns=0;
    }
    size_t length() const 
    {
        return rows*columns;
    }
    // Copy constructor and assignment
    matrix(matrix&);
    matrix& operator=(matrix&);
    // Move constructor and assignment
    matrix(matrix&&);
    matrix& operator=(matrix&&);
    int getrows() const 
    {
        return rows;
    }
    int getcols() const 
    {
        return columns;
    }
    int loc(int no_rows, int no_columns) const
    {
        if(no_rows>0 && no_rows<=rows && no_columns>0 && no_columns<=columns) 
          return (no_rows-1)+(no_columns-1)*columns;
        else 
        {
            std::cout<<"Cannot compute."<<std::endl;
            return 0;
        }
    }
    void setval(int m, int n, double val) 
    {
        array[loc(m,n)]=val;
    }
    double getval(int m, int n) const 
    {
        return array[loc(m,n)];
    }
    double & operator()(int m, int n) 
    {
        return array[loc(m,n)];
    } 
    // Overload addition operator
    matrix operator+(const matrix &arr)
    {
    if(rows==arr.getrows() && columns==arr.getcols())
    {
        matrix temp(rows,columns);
        for(int i{1};i<=rows;i++)
          {
            for(int j{1};j<=columns;j++)
              {
                temp.setval(i,j,(array[loc(i,j)]+arr.getval(i,j)));
              }
          }
        return temp;
    } else {
        std::cout<<"Unable to perform addition."<<std::endl; 
        exit(1);
    }
    }
    // Overload subtraction operator
    matrix operator-(const matrix &arr)
    {
    if(rows==arr.getrows() && columns==arr.getcols())
    {
        matrix temp(rows,columns);
        for(int i{1};i<=rows;i++)
          {
            for(int j{1};j<=columns;j++)
              {
                temp.setval(i,j,(array[loc(i,j)]-arr.getval(i,j)));
              }
          }
        return temp;
    } else {
        std::cout<<"Unable to perform subtraction."<<std::endl; 
        exit(1);
    }
    }
    // Overload multiplication operation
    matrix operator*(const matrix &arr)
    {
    if(columns==arr.getrows())
    {
        matrix temp(rows,arr.getcols());
        for(int i{1};i<=rows;i++)
          {
          for(int j{1};j<=arr.getcols();j++)
            {
              double sum{0};
              for(int k{1};k<=columns;k++) 
                {
                  sum+=array[loc(i,k)]*arr.getval(i,k); 
                  temp.setval(i,j,sum);
                }
            }
          }
        return temp;
    } else {
        std::cout<<"Unable to perform subtraction."<<std::endl; 
        exit(1);
    }
    }
};
// Copy constructor
matrix::matrix(matrix &arr)
{
  // Copy size and declare new array
  rows=0;
  columns=0;
  array=nullptr; 
  int no_rows(arr.getrows());
  int no_columns(arr.getcols());
  size=arr.length();
  if(size>0)
    {
      array=new double[size];
      for(int i{1};i<=no_rows;i++)
        {
          for(int j{1};j<=no_columns;j++)
            {
              array[loc(i,j)]=arr.getval(i,j);
            }
        }
    }
}
// Copy assignment operator
matrix & matrix::operator=(matrix &arr)
{
  if(&arr == this) return *this; 
  delete[] array;
  rows=0;
  columns=0; 
  int no_rows(arr.getrows());
  int no_columns(arr.getcols());
  size=arr.length();
  if(no_rows>0 && no_columns>0)
    {
      array=new double[size];
      rows=no_rows;
      columns=no_columns;
      for(int i{1};i<=no_rows;i++)
        {
          for(int j{1};j<=no_columns;j++)
            {
              array[loc(i,j)]=arr.getval(i,j);
            }
        }
    }
  return *this;
}
// Move constructor
matrix::matrix(matrix &&arr)
{ 
  size=arr.size;
  array=arr.array;
  arr.size=0;
  arr.array=nullptr;
}
// Move assignment operator
matrix & matrix::operator=(matrix&& arr)
{
  std::swap(size,arr.size);
  std::swap(array,arr.array);
  return *this;
}
// Parameterised constructor
matrix::matrix(int no_rows, int no_columns)
{
    if(no_rows<1||no_columns<1)
    {
      std::cout<<"The array must have positive size"<<std::endl;
      throw("size not positive");
    }
    else
    {
      rows=no_rows;
      columns=no_columns;
      size_t length=rows*columns;
      array=new double[length];
    }
}
//Overload << for matrix format
std::ostream & operator<<(std::ostream &os, const matrix &arr)
{
  for(int i{1};i<=arr.rows;i++)
    {
      std::cout<<"( ";
      for(int j{1};j<=arr.columns;j++)
        {
          std::cout<<arr.array[arr.loc(i,j)]<<" ";
        }
      std::cout<<")"<<std::endl;
    }
  return os;
}
int main()
{ 
    matrix a{2,2};
    matrix b{2,2};
    matrix c{2,2};
    b.setval(1,1,1);
    b.setval(1,2,2);
    b.setval(2,1,3);
    b.setval(2,2,4);
    std::cout<<"Matrix a is: "<<std::endl<<a<<std::endl;
    std::cout<<"Matrix b is: "<<std::endl<<b<<std::endl;
    std::cout<<"Copying values from b to a by assignment"<<std::endl;
    a=b;
    std::cout<<"Matrix a is now: "<<std::endl<<a<<std::endl;
    std::cout<<"Matrix c is empty: "<<std::endl<<c<<std::endl;
    std::cout<<"Moving values from a to c"<<std::endl;
    c=std::move(a);
    matrix d{b+c};
    matrix e{b-c};
    matrix f{b*c};
    std::cout<<"Matrix c is now: "<<std::endl<<c<<std::endl;
    std::cout<<"b + c is: "<<std::endl<<d<<std::endl;
    std::cout<<"b - c is: "<<std::endl<<e<<std::endl;
    std::cout<<"b * c is: "<<std::endl<<f<<std::endl;
    return 0;
}