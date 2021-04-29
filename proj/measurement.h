#ifndef MEASUREMENT_H
#define MEASUREMENT_H

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
    // Pure virtual function
    virtual void type()=0;
    // Virtual function to write textfile with results
    virtual void save_results() 
    { 
        std::ofstream outfile ("Results.txt");
        outfile.close();
    }
};

#endif