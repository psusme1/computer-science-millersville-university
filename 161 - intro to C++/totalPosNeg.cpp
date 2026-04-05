//sum1.cpp
//this program finds the sum of n numbers

#include <iostream>
using namespace std;

int main()
  {
    int SENTINEL = 0;
    float value;
    int poscount = 0;
    int negcount = 0;
    
    cout << endl << endl;

    while (value != SENTINEL)
     {
      cout << "Enter a value> ";
      cin >> value;
        if(value < 0)
         poscount++;
        else if(value > 0) 
         negcount++;
      
     }

     cout << "The total number of positive values entered is " << poscount << endl;
     cout << "The total number of negative values entered is " << negcount << endl;
     cout << "the total nuber of values entered is " << negcount + poscount << endl;
     cout << endl; 
    return 0;
  }
//end main
	

