// PHYS 30762 Programming in C++
// Assignment 4
// Classifying Galaxies
//
// Hubble types: E[0-7], S0, S[a-c], SB[a-c], Irr
// Redshift z in range [0,10]
// Total mass M_tot in range [1e7,1e12] M_sun
// Stellar mass fraction f_* in range [0,0.05]
#include<iostream>
#include<string>
#include<vector>
#include<cmath>

class galaxy
{
private:
  std::string hubble_type {"S0"};
  double redshift {0.0};
  double total_mass {0.0};
  double stellar_mass_fraction {0.0};

public:
  // Constructors
  galaxy() = default;

  galaxy(std::string galaxy_hubble_type , double galaxy_redshift , double galaxy_total_mass , double galaxy_stellar_mass_fraction) :
   hubble_type{galaxy_hubble_type}, redshift{galaxy_redshift}, total_mass{galaxy_total_mass}, stellar_mass_fraction{galaxy_stellar_mass_fraction}
  {}
  // Destructor

  double stellar_mass() {return stellar_mass_fraction * total_mass;}

  // Change galaxy's Hubble type
  void change_type(std::string new_type) {hubble_type = new_type;}
  // Prototype for function to print out an object's data
  void print_data();
  // Add satellite galaxy

};

// Print out an object's data
void galaxy::print_data()
{
  std::cout.precision(3); 
  std::cout<<"Galaxy: [Hubble type,z,m,f_*] = ["<<g.hubble_type<<","<< g.redshift
       <<","<<g.total_mass<<","<<g.stellar_mass_fraction<<"]"<<std::endl;
  return;
}

int main()
{

  // Example using default constructor
  galaxy g1; 

  // Example using parameterised constructor
  galaxy g2;
  g2.hubble_type = "E2";
  g2.redshift = 1.0;
  g2.total_mass = 2.e8; //Units of Msun
  g2.stellar_mass_fraction = 0.02;

  // print out data
  std::vector<galaxy> galaxy_data;
  // Need to check if next line is correct
  galaxy_data.push_back(galaxy("g1"));
  galaxy_data.push_back(galaxy("g2","E2",1.0,2.e8));

  for(auto galaxy_it=galaxy_data.begin(); galaxy_it <galaxy_data.end(); ++galaxy_it){
    galaxy_it->print_data();
    std::cout<<"has stellar mass ="<<galaxy_it-> stellar_mass()<<std::endl;
  }

  // Change Hubble type from Irr to S0
  
  // Add satellite galaxies

  return 0;
}