// PHYS 30762 Programming in C++
// Project
// Amy Gardiner 10137582
// An experimental data management system - Using measurements from a hypothetical radioactive spectrum to determine its source strength.

#include<iomanip>
#include<stdexcept>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<limits>
#include<cmath> 
#include<math.h> 
#include<cstdlib> 

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
    // Virtual function to write textfile with results
    virtual void save_results() 
    { 
        std::ofstream outfile ("Results.txt");
        outfile.close();
    }
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
    //virtual void save_results() 
    void save_results() 
    { 
        std::ofstream outfile;
        outfile.open("Results.txt",std::ios_base::out | std::ios_base::app);
        outfile<<"Count rate "<<name<<" = "<<std::setprecision(4)<<count_rate<<" +- "<<count_error<<" (measured "<<day<<"/"<<month<<"/"<<year<<")"<<std::endl;
        outfile.close();
    }
};

// Derived class for the systematic error
class systematic: public measurement
{

};

int main()
{
    while(true){
    char choice;
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

    if(day_input<=0 || day_input>31){
        std::cout<<"The day is incorrect."<<std::endl;
        continue;
    }

    if(month_input<=0 || month_input>12){
        std::cout<<"The month is incorrect."<<std::endl;
        continue;
    }

    if(year_input<=0 || year_input>2021){
        std::cout<<"The year is incorrect."<<std::endl;
        continue;
    }

    if (std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout<<"Invalid input. Try again. "<<std::endl;
        continue;
    }
    
    // Using stringstreams with user input to create the count rate names as required with the base class parameterised constructor
    std::vector<std::string> rate_1;
    std::vector<std::string> rate_2;
    std::string rate_prefix{"R_"};
    std::string energy_1{};
    std::string energy_2{};
    double rate_value_1{};
    double rate_value_2{};
    std::cout<<"Which count rate does this first data entry belong to? Enter 511 or sum: ";
    std::cin>>energy_1;
    std::stringstream st_1;
    st_1<<rate_prefix<<energy_1;
    rate_1.push_back(st_1.str());
    std::string s_1 = st_1.str();
    std::cout<<"Please enter this count rate value: "<<std::endl;
    std::cin>>rate_value_1;
    measurement* first=new value{s_1,day_input,month_input,year_input,rate_value_1};
    first -> save_results();
    std::cout<<"Which count rate does this second data entry belong to? Enter 511 or sum: ";
    std::cin>>energy_2;
    std::stringstream st_2;
    st_2<<rate_prefix<<energy_2;
    rate_2.push_back(st_2.str());
    std::string s_2 = st_2.str();
    std::cout<<"Please enter this count rate value: "<<std::endl;
    std::cin>>rate_value_2;
    measurement* second= new value{s_2,day_input,month_input,year_input,rate_value_2};
    second -> save_results();

    delete first;
    delete second;

    std::cout<<"Enter more measurements? Enter any key to continue, or N to quit: "<<std::endl;
    std::cin>>choice;

    if (choice=='n'||choice=='N'){
        break;
    }
    }
    return 0;
}