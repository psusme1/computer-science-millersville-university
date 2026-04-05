//sumNtoN1.cpp
//this program finds the sum of n numbers and compares it to the expression n*(n+1)/2

#include <iostream>
using namespace std;

int main()
  {
  int n, sum, count;
    
    count = 1;
    sum = 0;
    int expression;
    
    cout << endl << endl << "Enter the number you would like to sum up to> ";
    cin >> n;

    for(count = 1; count <= n; count++)
       sum = sum + count;
      
    cout << endl << "Sum is " << sum << "." << endl;
    
    expression = n*(n+1)/2;

    if(sum == expression)
     cout << endl << "The sum of 'n' numbers is equal to the expression n*(n+1)/2." << endl;
    else
     cout << endl << "The sum of 'n' is not equal to the expression n*(n+1)/2." << endl;
     cout << endl << endl;

    return 0;
  }
//end main
	
