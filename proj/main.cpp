// PHYS 30762 Programming in C++
// Project
// Amy Gardiner 10137582
// An experimental data management system - Using measurements from a hypothetical Na22 spectrum to determine its source strength.

#include<iomanip>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<limits>
#include<cmath> 
#include<math.h> 
#include<cstdlib>
#include<memory>

#include"measurement.h"
#include"sodium.h"
#include"cobalt.h"
#include"templates.h"
#include"date.h"

std::vector<int> date_input()
{
    int day_input;
    int month_input;
    int year_input;
    std::vector<int> date_vector;
    std::cout<<"Enter the date of the measurements in the format DD MM YYYY: "<<std::endl;
    std::cin>>day_input;
    date_vector.push_back(day_input);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    std::cin>>month_input;
    date_vector.push_back(month_input);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    std::cin>>year_input;
    date_vector.push_back(year_input);
    return date_vector;
}

int main()
{
    // Using the 'date' library and code for conversions sourced at https://howardhinnant.github.io/date/date.html for current time
    using namespace date;
    using namespace std::chrono;
    auto tp=system_clock::now();
    const auto tpm=floor<minutes>(tp);
    const auto dp=floor<days>(tpm);
    const auto ymd=year_month_day{dp};
    auto time=make_time(tpm-dp);

    // Writes this current time to the text file
    std::ofstream outfile;
    outfile.open("Results.txt",std::ios_base::out | std::ios_base::app);
    outfile<<"Document created: "<<ymd<<" "<<time<<std::endl;
    outfile.close();

    while(true){
    char choice;
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

    std::vector<int> myvec=date_input();
    int day=myvec[0];
    int month=myvec[1];
    int year=myvec[2];

    // Error checking for the user-input datestamp
    if(is_in_bounds<int>(day,1,31)==false || is_in_bounds<int>(month,1,12)==false || is_in_bounds<int>(year,1,2021)==false){
        std::cout<<"The timestamp is incorrect."<<std::endl;
        continue;
    }

    std::cout<<"Enter the nuclear source used - Na or Co:"<<std::endl;
    std::cin>>source_input;

    if(source_input=="Na"||source_input=="na")
    {
        // Sodium instance created (default constructor) so that it's type is printed in the text file
        sodium a{};
        a.type();

        while(true){
        std::cout<<"Which count rate energy does this first data entry belong to? Enter 511 or 1275: "<<std::endl;
        std::cin>>energy_1;
        if(energy_1=="511"||energy_1=="1275")
        {
            st_1<<rate_prefix<<energy_1;
            rate_1.push_back(st_1.str());
            std::string s_1 = st_1.str();
            std::cout<<"Please enter this count rate value: "<<std::endl;
            std::cin>>rate_value_1;
            std::unique_ptr<sodium> first(new sodium(s_1,day,month,year,rate_value_1));
            first->save_results();
            while(true){
            std::cout<<"Which count rate energy does this second data entry belong to? Enter 511 or 1275: "<<std::endl;
            std::cin>>energy_2;
            if(energy_2=="511"||energy_2=="1275")
            {
                st_2<<rate_prefix<<energy_2;
                rate_2.push_back(st_2.str());
                std::string s_2 = st_2.str();
                std::cout<<"Please enter this count rate value: "<<std::endl;
                std::cin>>rate_value_2;
                std::unique_ptr<sodium> second(new sodium(s_2,day,month,year,rate_value_2));
                second->save_results();

                if(sodium_order<int>(energy_1, energy_2)==true)
                {
                sodium_calculations<int>(rate_value_1, rate_value_2, rate_value_sum, day, month, year);
                }

                if(sodium_order<int>(energy_1, energy_2)==false)
                {
                sodium_calculations<int>(rate_value_2, rate_value_1, rate_value_sum, day, month, year);
                }
                break;
                } else
                {
                std::cout<<"This energy doesn't fit the requirement."<<std::endl;
                continue;
            }
            }
            break;
        } else
        {
            std::cout<<"This energy doesn't fit the requirement."<<std::endl;
            continue;
        }
        }
    }

    if(source_input=="Co"||source_input=="co")
    {
        cobalt a{};
        a.type();
        while(true){
        std::cout<<"Which count rate energy does this data entry belong to? Enter 1173 or 1332: "<<std::endl;
        std::cin>>energy_1;
        if(energy_1=="1173"||energy_1=="1332")
        {
            st_1<<rate_prefix<<energy_1;
            rate_1.push_back(st_1.str());
            std::string s_1 = st_1.str();
            std::cout<<"Please enter this count rate value: "<<std::endl;
            std::cin>>rate_value_1;
            std::unique_ptr<cobalt> first(new cobalt(s_1,day,month,year,rate_value_1));
            first->save_results();
            first->calc();
        break;
        } else
        {
            std::cout<<"This energy doesn't fit the requirement."<<std::endl;
            continue;
        }
        }
    }

    std::cout<<"Enter more measurements? Enter any key to continue, or N to quit: "<<std::endl;
    std::cin>>choice;

    if (choice=='n'||choice=='N'){
        break;
    }
    }
    return 0;
}