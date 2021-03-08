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
  std::string hubble_type;
  double redshift;
  double total_mass;
  double stellar_mass_fraction;
  int satellites;
  std::vector<galaxy> satellite_data;

public:
  // Constructors
  galaxy() : hubble_type{"Irr"}, redshift{}, total_mass{}, stellar_mass_fraction{}, satellites{}  {}

  galaxy(std::string g_hubble_type , double g_redshift , double g_total_mass , double g_stellar_mass_fraction, int g_satellites) :
   hubble_type{g_hubble_type}, redshift{g_redshift}, total_mass{g_total_mass}, stellar_mass_fraction{g_stellar_mass_fraction}, satellites{g_satellites}
  {}
  // Destructor
  ~galaxy() {}

  double stellar_mass() 
  {
    return stellar_mass_fraction * total_mass;
  }

  // Change galaxy's Hubble type
  void change_type(std::string new_type) 
  {
    hubble_type = new_type;
  }

  // Prototype for function to print out an object's data
  void print_data();

  // Add a satellite galaxy
  void add_satellite()
  {
    galaxy s1("SBa,",5.0,1.e10,0.03,0);
    satellite_data.push_back(s1);
  }
};

// Print out an object's data
void galaxy::print_data()
{
  std::cout.precision(3); 
  std::cout<<"Galaxy: [Hubble type,z,m,f_*,no. satellites] = ["<<hubble_type<<","<< redshift
       <<","<<total_mass<<","<<stellar_mass_fraction<<","<<satellites<<"]"<<std::endl;
  if(satellites>0)
    for(int i{};i<satellite_data.size();i++)
      {
        std::cout<<"Satellite: [Hubble type,z,m,f_*, no. satellites] = ["<<std::endl;
        satellite_data[i].print_data();
      }
  return;
}

int main()
{

  // Example using default constructor
  galaxy g1; 

  // Example using parameterised constructor
  galaxy g2("E2",1.0,3.e8,0.02,1);

  // Print out data
  std::vector<galaxy> galaxy_data;
  galaxy_data.push_back(g1);
  galaxy_data.push_back(g2);

  for(auto galaxy_it=galaxy_data.begin(); galaxy_it <galaxy_data.end(); ++galaxy_it){
    galaxy_it->print_data();
    std::cout<<"has stellar mass ="<<galaxy_it-> stellar_mass()<<std::endl;
  }
  
  // Change Hubble type from Irr to S0
  galaxy_data[0].change_type("S0");

  std::cout<<"Changing Irr to S0:"<<std::endl;

  for(auto galaxy_it=galaxy_data.begin(); galaxy_it <galaxy_data.end(); ++galaxy_it){
    galaxy_it->print_data();
  }
  
  return 0;
}