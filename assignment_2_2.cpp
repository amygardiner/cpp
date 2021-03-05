#include<iostream>
#include<iomanip>
#include<ios>
#include<fstream>
#include<sstream>
#include<cmath>
#include<limits>
#include<string>
#include<vector>

// Function to print range
void print(std::vector<std::string> const &course_titles)
{
    for (int i = 0; i < course_titles.size(); i++) {
        std::cout << course_titles.at(i) << std::endl;
    }
}

int main()
{
    char datafile[30];
    char year_choice;

    std::cout<<"Enter data filename: ";
    std::cin>>datafile;

    std::fstream file1(datafile);

    // Check for file opening
    if(!file1.is_open()){
      std::cerr<<"Error: file could not be opened"<<std::endl;
      return(1);
    }

    int n_data{0};

    // Counter for lines in the datafile
    while(!file1.eof()){
      n_data++;
      file1.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    std::cout<<"Number of courses read is: "<<n_data<<std::endl;
  
    file1.close();

    file1.open(datafile);
    std::vector<std::string> courses;
    double *grades = new double[n_data];
    int course_code;
    std::string course_name;
    const int year_digit{5};

    // Separating the first column of grade data, then using a stringstream to combine "PHYS" with each line of course code and title data
    while (!file1.eof()){ 
        std::string subject{"PHYS"};
        std::stringstream st;
        for (int i{};i<n_data;i++){
          file1>>grades[i];
          file1>>course_code;
          std::getline(file1, course_name);
          st << subject << " " << course_code << course_name;
          courses.push_back(st.str());
          st.str("");
        }
    }

    file1.close();
    
    std::cout<<"Please enter 1,2,3 or 4 to view courses for that year, or enter A for all years: ";
    std::cin>>year_choice;

    char year;

    // Iterator for courses matching the year digit as specified in line 51, which would also match the user input value
    for(auto iterator = courses.begin(); iterator < courses.end(); ++iterator){
        year = (*iterator)[year_digit];
        if (year == year_choice) 
            std::cout<< *iterator << std::endl;
    }

    if (year_choice=='a'||year_choice=='A'){
        print(courses);
    }

    return 0;
}