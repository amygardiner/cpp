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
        rows=columns=0;
    }
    size_t length() const 
    {
        return rows*columns;
    }
    double & operator[](size_t i);
    // Copy and copy assignment
    matrix(matrix&);
    matrix& operator=(matrix&);
    // Move and move assignment
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
            std::cout<<"Error: out of range"<<std::endl;
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
    matrix operator+(const matrix &mat);
    matrix operator-(const matrix &mat);
    matrix operator*(const matrix &mat);
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
            for(int j{1};j<=no_columns;j++)
              array[loc(i,j)]=arr.getval(i,j);
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
            for(int j{1};j<=no_columns;j++)
              array[loc(i,j)]=arr.getval(i,j);
    }
  return *this;
}
// Move constructor
matrix::matrix(matrix &&arr)
{ 
  std::cout <<"move constructor\n";
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
        for(size_t i{};i<length;i++) array[i]=0;
    }
}
//Overload << for matrices
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
    matrix a{2,2};
    std::cout<<"Matrix a is: "<<std::endl<<a<<std::endl;
    matrix b{2,2};
    b.setval(1,1,1);
    b.setval(1,2,2);
    b.setval(2,1,3);
    b.setval(2,2,4);
    std::cout<<"Matrix b is: "<<std::endl<<b<<std::endl;
    std::cout<<"Copying values from b to a by assignment"<<std::endl;
    a=b;
    std::cout<<"Matrix a is now: "<<std::endl<<a<<std::endl;
    matrix c{2,2};
    std::cout<<"Matrix c is empty: "<<std::endl<<c<<std::endl;
    std::cout<<"Moving values from a to c"<<std::endl;
    c=std::move(a);
    std::cout<<"Matrix c is now: "<<std::endl<<c<<std::endl;
    return 0;
}