#ifndef sodium_H
#define sodium_H

#include<iomanip>
#include<stdexcept>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<limits>

// Derived class for the sodium source
class sodium: public measurement
{
protected:
    int day;
    int month;
    int year;
    double count_rate;
public:
    // Default constructor
    sodium() : measurement{}, day{}, month{}, year{}, count_rate{} {}
    // Parameterised constructor 
    sodium(const std::string nm, const int d, const int m, const int y, const double cr) : measurement{nm}, day{d}, month{m}, year{y}, count_rate{cr} {}
    // Destructor
    ~sodium(){}
    double count_error{sqrt(count_rate)};
    void type()
    {
        std::ofstream outfile;
        outfile.open("Results.txt",std::ios_base::out | std::ios_base::app);
        outfile<<"Source: Na22"<<std::endl;
        outfile.close();
    }
    void save_results() 
    { 
        std::ofstream outfile;
        outfile.open("Results.txt",std::ios_base::out | std::ios_base::app);
        outfile<<"Count rate "<<name<<" = "<<std::setprecision(4)<<count_rate<<" \u00B1 "<<count_error<<" (measured "<<day<<"/"<<month<<"/"<<year<<")"<<std::endl;
        outfile.close();
    }
    void file_results()
    {
        std::ofstream outfile;
        outfile.open("Results.txt",std::ios_base::out | std::ios_base::app);
        outfile<<"Count rate R_"<<name<<" = "<<std::setprecision(4)<<count_rate<<" \u00B1 "<<count_error<<" (measured "<<day<<"/"<<month<<"/"<<year<<")"<<std::endl;
        outfile.close();
    }
};

#endif