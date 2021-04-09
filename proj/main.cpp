// PHYS 30762 Programming in C++
// Project
// Amy Gardiner 10137582
// An experimental data management system - Using measurements from a hypothetical radioactive spectrum to determine its source strength.

#include<iomanip>
#include <stdexcept>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<limits>
#include<cmath> 
#include<math.h> 
#include <cstdlib> 

// Base class for measurement
class measurement
{
protected:
    std::string name;
public:
    // Default constructor
    measurement() : name{"Untitled"} {}
    // Parameterised constructor
    measurement(const std::string nm) : name{nm} {}
    // Destructor
    virtual ~measurement(){}
    // Virtual pure function to override
    virtual void info()=0;
};

// Derived class for the measurement value 
class value: public measurement
{
protected:
    int day;
    int month;
    int year;
    double count_rate;
public:
    // Default constructor
    value() : measurement{}, day{}, month{}, year{}, count_rate{} {}
    // Parameterised constructor 
    value(const std::string nm, const int d, const int m, const int y, const double cr) : measurement{nm}, day{d}, month{m}, year{y}, count_rate{cr} {}
    // Destructor
    ~value(){}
    double count_error{sqrt(count_rate)};
    void info()
    {
        std::cout<<"Count rate "<<name<<" = "<<std::setprecision(4)<<count_rate<<" +- "<<count_error<<" (measured "<<day<<"/"<<month<<"/"<<year<<")"<<std::endl;
    }
};

// Derived class for the systematic error
class systematic: public measurement
{

};

int at(int day_input) {
  if(day_input<=0 || day_input>31)
    throw std::out_of_range("The day is not correct.");

  return day_input;
}

int main()
{
    int day_input;
    int month_input;
    int year_input;

    std::cout<<"Enter the date of the measurements in the format DD MM YYYY: "<<std::endl;
    std::cin>>day_input;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    std::cin>>month_input;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    std::cin>>year_input;
    at(day_input);
    

    if (std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout<<"Invalid input. Try again. "<<std::endl;
        return -1;
    }
    
    // Using stringstreams with user input to create the count rate names as required with the base class parameterised constructor
    std::vector<std::string> rate_1;
    std::vector<std::string> rate_2;
    std::string rate_prefix{"R_"};
    std::string rate_input_1{};
    std::string rate_input_2{};
    std::cout<<"Which count rate does this first data belong to? Enter 511 or sum: ";
    std::cin>>rate_input_1;
    std::cout<<"Which count rate does this second data belong to? Enter 511 or sum: ";
    std::cin>>rate_input_2;
    std::stringstream st_1;
    std::stringstream st_2;
    st_1<<rate_prefix<<rate_input_1;
    st_2<<rate_prefix<<rate_input_2;
    rate_1.push_back(st_1.str());
    rate_2.push_back(st_2.str());
    std::string s_1 = st_1.str();
    std::string s_2 = st_2.str();

    measurement *count_rates[1];
    count_rates[0]=new value{s_1,day_input,month_input,year_input,6564.55};
    count_rates[1]=new value{s_2,day_input,month_input,year_input,28.34};
    count_rates[0]->info();
    delete count_rates[0];
    count_rates[0]=0;
    count_rates[1]->info();
    delete count_rates[1];
    count_rates[1]=0;
    /*
    std::ofstream outfile("results.txt");
    outfile<<"format results here"<<std::endl;
    outfile.close();
    */

    return 0;
}