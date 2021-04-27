template <typename T>
    bool is_in_bounds(const T value, const T low, const T high)
    { 
        return !(value < low) && !(high < value); 
    }

template <typename T>
    bool order(const std::string e1, const std::string e2)
    {
        return (e1=="1275") && (e2=="511");
    }

template <typename T>
    void calculations(const double a, const double b, double rate_value_sum, const int day_input, const int month_input, const int year_input)
    {
        double efficiency{2*a/b};
        std::ofstream outfile;
        outfile.open("Results.txt",std::ios_base::out | std::ios_base::app);
        outfile<<"The ratio of detector efficiencies at these energies is: "<<efficiency<<std::endl;
        std::cout<<"Please enter the count rate value of the sum peak, R_sum: "<<std::endl;
        std::cin>>rate_value_sum;
        measurement* third= new value{"R_sum",day_input,month_input,year_input,rate_value_sum};
        third -> save_results();
        double strength{(efficiency*pow(b,2))/2*rate_value_sum};
        outfile<<"The source strength from this spectra is: "<<strength<<std::endl;
        outfile.close();
        delete third;
    }