#ifndef cobalt_H
#define cobalt_H

#include<iomanip>
#include<stdexcept>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<limits>

// Derived class for the cobalt source
class cobalt: public measurement
{
protected:
    int day;
    int month;
    int year;
    double count_rate;
    double efficiency;
    double solid_angle;
    double strength;
public:
    // Default constructor
    cobalt() : measurement{}, day{}, month{}, year{}, count_rate{} {}
    // Parameterised constructor 
    cobalt(const std::string nm, const int d, const int m, const int y, const double cr) : measurement{nm}, day{d}, month{m}, year{y}, count_rate{cr} {}
    // Destructor
    ~cobalt(){}
    double count_error{sqrt(count_rate)}; 
    void type()
    {
        std::ofstream outfile;
        outfile.open("Results.txt",std::ios_base::out | std::ios_base::app);
        outfile<<"Source: Co60"<<std::endl;
        outfile.close();
    }
    void save_results() 
    { 
        std::ofstream outfile;
        outfile.open("Results.txt",std::ios_base::out | std::ios_base::app);
        outfile<<"Count rate "<<name<<" = "<<std::setprecision(4)<<count_rate<<" +- "<<count_error<<" (measured "<<day<<"/"<<month<<"/"<<year<<")"<<std::endl;
        outfile.close();
    }
    void calc()
    {
        std::cout<<"Please enter the efficiency of the detector at this energy: "<<std::endl;
        std::cin>>efficiency;
        std::cout<<"Please enter the solid angle of the detector (<4pi)"<<std::endl;
        std::cin>>solid_angle;
        strength=count_rate/(solid_angle*efficiency);
        std::ofstream outfile;
        outfile.open("Results.txt",std::ios_base::out | std::ios_base::app);
        outfile<<"The source strength from this spectra is: "<<std::setprecision(4)<<strength<<" s^-1"<<std::endl;
        outfile.close();

    }
};

#endif