// PHYS 30762 Programming in C++
// Project
// Amy Gardiner 10137582
// An experimental data management system - Using measurements from hypothetical nuclear spectra to determine their source strength.

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
#include<ctime>
#include<memory>

#include"measurement.h"
#include"sodium.h"
#include"cobalt.h"

template<typename T>
    bool sodium_order(const std::string energy_1, const std::string energy_2)
    {
        return (energy_1=="1275") && (energy_2=="511");
    }

template<typename T>
    void sodium_calculations(const double a, const double b, double c, const int day, const int month, const int year)
    {
        double efficiency{2*a/b};
        std::ofstream outfile;
        outfile.open("Results.txt",std::ios_base::out | std::ios_base::app);
        outfile<<"The ratio of detector efficiencies at these energies is: "<<efficiency<<std::endl;
        std::cout<<"Please enter the count rate value of the sum peak, R_sum: "<<std::endl;
        std::cin>>c;
        std::unique_ptr<sodium> third(new sodium("R_sum",day,month,year,c));
        third -> save_results();
        double strength{(efficiency*pow(b,2))/(2*c)};
        outfile<<"The source strength from this spectra is: "<<strength<<" s^-1"<<std::endl;
        outfile.close();
    }

// Function for user input of the experiment date, returns the elements within a vector
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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),' ');
    std::cin>>month_input;
    date_vector.push_back(month_input);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),' ');
    std::cin>>year_input;
    date_vector.push_back(year_input);
    return date_vector;
}

int main()
{
    // Add current timestamp to document
    std::time_t result = std::time(nullptr);
    std::ofstream outfile;
    outfile.open("Results.txt",std::ios_base::out | std::ios_base::app);
    outfile<<"Document created: "<<std::asctime(std::localtime(&result));
    outfile.close();

    char input_type;
    char datafile[30];
    std::cout<<"Type f to input data from a file, or any other key to input through the terminal: "<<std::endl;
    std::cin>>input_type;

    if(input_type=='f'||input_type=='F'){
        char datafile[30];
        std::cout<<"Enter data filename (it's sodium.txt): ";
        std::cin>>datafile;
        std::fstream sodiumfile(datafile);

        if(!sodiumfile.is_open()){
            std::cerr<<"Error: file could not be opened"<<std::endl;
            return(1);
        }

        // Extracting the information from the datafile
        std::ifstream in(datafile);
        std::vector<int> days, months, years;
        std::vector<std::string> energies;
        std::vector<double> rates;
        int j,k,l,n;
        std::string m;

        while(in>>j>>k>>l>>m>>n){
            days.push_back(j);
            months.push_back(k);
            years.push_back(l);
            energies.push_back(m);
            rates.push_back(n);
        }

        for(int i{0};i<=days.size()-1;i++){
            sodium *temp_array[days.size()];
            temp_array[i]=new sodium(energies[i],days[i],months[i],years[i],rates[i]);
            temp_array[i]->file_results();
        }

        for(int i{0};i<=days.size()-1;i++){
            // Each 3 consecutive lines within the file are a set of measurements to be used for the calculations
            if(i==0 || i%3==0){
                double rate_511{rates[i]};
                double rate_1275{rates[i+1]};
                double rate_sum{rates[i+2]};
                double efficiency{(2*rate_1275)/rate_511};
                std::ofstream outfile;
                outfile.open("Results.txt",std::ios_base::out | std::ios_base::app);
                outfile<<"The ratio of detector efficiencies for the energies at lines "<<i+2<<" - "<<i+4<<" is: "<<efficiency<<std::endl;
                double numerator{efficiency*(pow(rate_511,2))};
                double denominator{2*rate_sum};
                double strength{numerator/denominator};
                outfile<<"The source strength from the spectra at lines "<<i+2<<" - "<<i+4<<" is: "<<strength<<" s^-1"<<std::endl;
                outfile.close();
            }
        }
        return(1);  
    }

    // Implementation for user input through the terminal 
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
        std::stringstream stream_1;
        std::stringstream stream_2;

        std::vector<int> myvec=date_input();
        int day=myvec[0];
        int month=myvec[1];
        int year=myvec[2];

        // Lambda function for error handling of the date elements
        auto is_in_bounds=[](auto l1, auto l2, auto l3){return !(l1 < l2) && !(l3 < l1);};
        bool a=is_in_bounds(day,1,31);
        bool b=is_in_bounds(month,1,12);
        bool c=is_in_bounds(year,1,2021);

        if(a==false || b==false || c==false){
            std::cout<<"The timestamp is incorrect."<<std::endl;
            continue;
        }

        std::cout<<"Enter the nuclear source used - Na or Co:"<<std::endl;
        std::cin>>source_input;

        if(source_input=="Na"||source_input=="na"){
            // Default sodium instance created so that it's type is printed in the text file
            sodium a{};
            a.type();

            while(true){
            std::cout<<"Which count rate energy does this first data entry belong to? Enter 511 or 1275: "<<std::endl;
            std::cin>>energy_1;
            if(energy_1=="511"||energy_1=="1275"){
                // Creating stringstreams for the count rate values to be used within sodium instances
                stream_1<<rate_prefix<<energy_1;
                rate_1.push_back(stream_1.str());
                std::string string_1 = stream_1.str();
                std::cout<<"Please enter this count rate value: "<<std::endl;
                std::cin>>rate_value_1;
                std::unique_ptr<sodium> first(new sodium(string_1,day,month,year,rate_value_1));
                first->save_results();
                while(true){
                    std::cout<<"Which count rate energy does this second data entry belong to? Enter 511 or 1275: "<<std::endl;
                    std::cin>>energy_2;
                    if(energy_2=="511"||energy_2=="1275"){
                        stream_2<<rate_prefix<<energy_2;
                        rate_2.push_back(stream_2.str());
                        std::string string_2 = stream_2.str();
                        std::cout<<"Please enter this count rate value: "<<std::endl;
                        std::cin>>rate_value_2;
                        std::unique_ptr<sodium> second(new sodium(string_2,day,month,year,rate_value_2));
                        second->save_results();

                        // The equation for source strength is dependent on R_511 not R_1275 so the order in which they are input matters
                        if(sodium_order<int>(energy_1, energy_2)==true){
                            sodium_calculations<int>(rate_value_1, rate_value_2, rate_value_sum, day, month, year);
                        }

                        if(sodium_order<int>(energy_1, energy_2)==false){
                            sodium_calculations<int>(rate_value_2, rate_value_1, rate_value_sum, day, month, year);
                        }
                        break;
                    } else{
                        std::cout<<"This energy doesn't fit the requirement."<<std::endl;
                        continue;
                    }
                }
                break;
            } else{
                std::cout<<"This energy doesn't fit the requirement."<<std::endl;
                continue;
            }
            }
        }

        if(source_input=="Co"||source_input=="co"){
            cobalt a{};
            a.type();
            while(true){
            std::cout<<"Which count rate energy does this data entry belong to? Enter 1173 or 1332: "<<std::endl;
            std::cin>>energy_1;
            if(energy_1=="1173"||energy_1=="1332"){
                stream_1<<rate_prefix<<energy_1;
                rate_1.push_back(stream_1.str());
                std::string string_1 = stream_1.str();
                std::cout<<"Please enter this count rate value: "<<std::endl;
                std::cin>>rate_value_1;
                std::unique_ptr<cobalt> first(new cobalt(string_1,day,month,year,rate_value_1));
                first->save_results();
                first->calculation();
            break;
            } else{
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