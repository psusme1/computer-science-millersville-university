//sum1.cpp
//this program finds the sum of n numbers

#include <iostream>
using namespace std;

int main()
  {
  int n, sum, count;
    
    n = 10;
    count = 1;
    sum = 0;
    
    while (count <= n)
      {
        sum = sum + count;
        count = count + 1;
      }
    cout << "Sum is " << sum << "." << endl;

    return 0;
  }
//end main
	
