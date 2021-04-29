// PHYS 30762 Programming in C++
// Project
// Amy Gardiner 10137582
// An experimental data management system - Using measurements from a hypothetical Na22 spectrum to determine its source strength.

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

#include"measurement.h"
#include"sodium.h"
#include"cobalt.h"
#include"templates.h"

int main()
{
    while(true){
    char choice;
    int day_input;
    int month_input;
    int year_input;
    std::string source_input{};
    std::vector<std::string> rate_1;
    std::vector<std::string> rate_2;
    std::string rate_prefix{"R_"};
    std::string energy_1{};
    std::string energy_2{};
    double rate_value_1{};
    double rate_value_2{};
    double rate_value_sum{};
    std::stringstream st_1;
    std::stringstream st_2;

    std::cout<<"Enter the date of the measurements in the format DD MM YYYY: "<<std::endl;
    std::cin>>day_input;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    std::cin>>month_input;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    std::cin>>year_input;

    if(is_in_bounds<int>(day_input,1,31)==false || is_in_bounds<int>(month_input,1,12)==false || is_in_bounds<int>(year_input,1,2021)==false){
        std::cout<<"The timestamp is incorrect."<<std::endl;
        continue;
    }

    if (std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout<<"Invalid input. Try again. "<<std::endl;
        continue;
    }

    std::cout<<"Enter the nuclear source used - Na, Co or Cs:"<<std::endl;
    std::cin>>source_input;

    if(source_input=="Na")
    {
        sodium a{};
        a.type();

        std::cout<<"Which count rate energy does this first data entry belong to? Enter 511 or 1275: "<<std::endl;
        std::cin>>energy_1;
        st_1<<rate_prefix<<energy_1;
        rate_1.push_back(st_1.str());
        std::string s_1 = st_1.str();
        std::cout<<"Please enter this count rate value: "<<std::endl;
        std::cin>>rate_value_1;
        measurement* first=new sodium{s_1,day_input,month_input,year_input,rate_value_1};
        first -> save_results();
        std::cout<<"Which count rate energy does this second data entry belong to? Enter 511 or 1275: "<<std::endl;
        std::cin>>energy_2;
        st_2<<rate_prefix<<energy_2;
        rate_2.push_back(st_2.str());
        std::string s_2 = st_2.str();
        std::cout<<"Please enter this count rate value: "<<std::endl;
        std::cin>>rate_value_2;
        measurement* second= new sodium{s_2,day_input,month_input,year_input,rate_value_2};
        second -> save_results();

        if(sodium_order<int>(energy_1, energy_2)==true)
        {
        sodium_calculations<int>(rate_value_1, rate_value_2, rate_value_sum, day_input, month_input, year_input);
        }

        if(sodium_order<int>(energy_1, energy_2)==false)
        {
        sodium_calculations<int>(rate_value_2, rate_value_1, rate_value_sum, day_input, month_input, year_input);
        }
        delete first;
        delete second;
    }

    if(source_input=="Co")
    {
        cobalt a{};
        a.type();
    }

    std::cout<<"Enter more measurements? Enter any key to continue, or N to quit: "<<std::endl;
    std::cin>>choice;

    if (choice=='n'||choice=='N'){
        break;
    }
    }
    return 0;
}