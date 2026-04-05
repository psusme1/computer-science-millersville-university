// max.cpp
//   This program finds the max of n numbers entered.

#include <iostream>
using namespace std;


int main ()
{
           int n, max, count, number;

           n = 3;
/* 1 */    count = 1;
/* 2 */    max = -9999;   // a small number so all numbers
                          //  are greater than initial value
/* 3 */    while (count <= n)
           {
/* 4 */        cout << "Enter a number> ";
/* 5 */        cin >> number;
/* 6 */        if (number > max)
/* 7 */            max = number;
/* 8 */        count = count + 1;
           }

           cout << "Max is " << max << endl;
		   return 0;

} // end main
