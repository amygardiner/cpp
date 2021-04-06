// PHYS 30762 Programming in C++
// Project
// Amy Gardiner 10137582
// An experimental data management system

#include <iostream>
#include <fstream> 

int main()
{
    std::ofstream outfile("results.txt");
    outfile<<"format results here"<<std::endl;
    outfile.close();
}
 
