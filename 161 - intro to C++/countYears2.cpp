//countYears.cpp
//this program finds the population of a town after n years.
//page 253 #1


#include <iostream>
using namespace std;

int main()
  {
  int count;
  float pop;
    
    count = 1;
    pop = 9870;
    
    cout << endl << endl;
 
    for(count = 1; pop <= 30000; count++)
       {
        pop = pop * 1.1;
        cout << "After " << count << " years, the population equals ";
        cout << pop << "." << endl; 
       }

    cout << endl << "It takes " << count-1; 
    cout << " years for the population to exceed 30,000 people." << endl << endl;

  
    return 0;
  }
//end main
	
