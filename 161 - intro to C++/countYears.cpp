//countYears.cpp
//this program finds the population of a town after n years.
//page 253 #1


#include <iostream>
using namespace std;

int main()
  {
  int years, count;
  float pop;
    
    count = 1;
    pop = 9870;
    
    cout << "Enter the number of years to calculate population> ";
    cin >> years;    
    
    for(count = 1; count <= years; count++)
       pop = pop * 1.1;
      
    cout << endl << "The population after " << years << " years is " << pop << "." << endl;
    cout << endl << endl;

    return 0;
  }
//end main
	
