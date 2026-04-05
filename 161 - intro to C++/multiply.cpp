//Author:     Shawn Englerth
//Date:       April 01, 2003
//Course:     CSCI 161
//Assignment: Multiply (lab 6 synthesis)

// this program finds the product of two numbers

#include <iostream>
using namespace std;

int main()
  {
  int x, y, sum, count;
  count = 1;
  sum = 0;

    cout << endl << endl << "This program will calculate the product of two integers."  << 
endl;
    cout << "The second number entered must be non-negative."  << endl << endl;

    cout << "Enter first number> ";
    cin >> x;
    cout << endl;
    cout << "Enter second non-negative number> ";
    cin >> y;
    cout << endl;

    while (y < 0)
      {
        cout << "Please enter a number that is non-negative!";
        cout << endl;
        cout << "Enter second non-negative number> ";
        cin >> y;
        cout << endl;
      }
    
    while (count <= y)

      {
        sum = sum + x;
        count = count++;
      }

    
    cout << "The product is " << sum  << "." << endl << endl << endl;

    return 0;
  }
//end main
	
#
