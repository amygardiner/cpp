
// PHYS 30762 Programming in C++
// Assignment 2
// Amy Gardiner 10137582
// Program to compute mean, standard deviation and standard
// error of the set of courses. Data is read from file

#include<iostream>
#include<iomanip>
#include<ios>
#include<fstream>
#include<sstream>
#include<cmath>
#include<limits>
#include<string>

// Function to compute mean
double calculate_mean(double *grades, int n_data)
{
  double sum{0};
  for (int i{};i<n_data;i++){
      sum=sum+grades[i];
  }
  double mean{sum/n_data};
  return mean;
}

// Function to compute standard deviation
double calculate_standard_deviation(double *grades, int n_data)
{
  double sum;
  double mean{calculate_mean(grades,n_data)};
  for (int i{};i<n_data;i++){
      sum=sum+(pow(grades[i]-mean,2));
  }
  int divider{n_data-1};
  double standard_deviation{sqrt(sum/divider)};
  return standard_deviation;
}

// Function to compute the standard error on the mean
double calculate_standard_error(double standard_deviation, int n_data)
{
  double temp{pow(n_data, 0.5)};
  double standard_error{standard_deviation/temp};
  return standard_error;
}

int main()
{
  char datafile[30];

  std::cout<<"Enter data filename: ";
  std::cin>>datafile;

  std::fstream file1(datafile);

  //Check that file can be opened
  if(!file1.is_open()){
      std::cerr<<"Error: file could not be opened"<<std::endl;
      return(1);
  }

  int n_data{0};
  
  //Counter for the number of courses in the file
  while(!file1.eof()){
      n_data++;
      file1.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
  }
  std::cout<<"Number of courses read is: "<<n_data<<std::endl;
  
  file1.close();

  double *grades = new double[n_data];
  int *course_code = new int[n_data];
  std::string *course_title = new std::string[n_data];

  //Separate each column
  file1.open(datafile);
      for (int i{};i<n_data;i++){
        file1>>grades[i];
        file1>>course_code[i];
        getline(file1, course_title[i]);

    }
  file1.close();

  double mean{calculate_mean(grades,n_data)};
  double standard_deviation{calculate_standard_deviation(grades,n_data)};
  double standard_error{calculate_standard_error(standard_deviation, n_data)};
  std::cout<<std::endl<<"The mean is: "<<std::setprecision(3)<<mean<<" +- "<<standard_error<<std::endl;
  std::cout<<"The standard deviation is: "<<std::setprecision(3)<<standard_deviation<<std::endl;

  delete[] grades;
  delete[] course_code;
  delete[] course_title;

  return 0;
}