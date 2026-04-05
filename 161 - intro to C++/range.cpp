//Shawn Englerth
//page 286 #7
//range.cpp
//this program finds the sum of n numbers

#include <iostream>
using namespace std;

int main()

 {
   float value;
   
   cout << endl << endl; 
     do
      {
       cout << "Enter a number between 0 and 15>  ";
       cin >> value;
      }while (( value < 0) || (value > 15));
    
    cout << "The data value " << value << " is between 0 and 15." << endl; 
    cout << endl << endl;
 
 return 0;
  }
//end main
	
