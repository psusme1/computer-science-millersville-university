//sum1.cpp
//this program finds the sum of n numbers

#include <iostream>
using namespace std;

int main()
  {
  int n, sum, count;
    
    count = 1;
    sum = 0;
    
    cout << "Enter the number you would like to sum up to> ";
    cin >> n;

    while (count <= n)
      {
        sum = sum + count;
        count = count + 1;
      }
    cout << "Sum is " << sum << "." << endl;

    return 0;
  }
//end main
	
