// max2.cpp
//   This program finds the max of numbers until a 0 is entered.

#include <iostream>
using namespace std;


int main ()
{
           int n, max, count, number;

/* 1 */    cout << "Enter a number> ";
/* 2 */    cin >> number;

/* 3 */    max = -9999;
/* 4 */    while (number != 0)
           {
/* 5 */        if (number > max)
/* 6 */            max = number;
/* 7 */        cout << "Enter a number> ";
/* 8 */        cin >> number;
           }

           cout << "Max is " << max << endl;
		   return 0;
}
