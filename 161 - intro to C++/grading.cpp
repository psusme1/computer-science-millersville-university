// Grading.cpp
//   This program calculates grades on a 10 point scale.

#include <iostream>
using namespace std;

int main ()
{ 
           char letter;               // letter grade
           int number;                // number grade

/* 1 */    cout << "This program calculates letter grades for a given";
/* 2 */    cout << " number grade." << endl;
/* 3 */    cout << "Enter a number grade> ";
/* 4 */    cin >> number;

/* 5 */    if (number < 0)
           {
/* 6 */        letter = 'e';      // for error
/* 7 */        cout << "You must enter a positive number for your grade" << endl;
           }
/* 8 */    else if (number < 60)
/* 9 */        letter = 'F';
/* 10*/    else  if (number < 70)
/* 11*/        letter = 'D';    
/* 12*/    else if (number < 80)
/* 13*/        letter = 'C';
/* 14*/    else  if (number < 90)
/* 15*/        letter = 'B';    
/* 16*/    else  if (number <= 100)
/* 17*/        letter = 'A';    
/* 18*/    else  // grade > 100 not possible
           {
/* 19*/        letter = 'e';      // for error
/* 20*/        cout << "Grade must be between 0 and 100" << endl;
	   }
/* 21*/    if (letter != 'e')
           {
/* 22*/        cout << "A " << number << " is equalivalent to a letter grade of ";
/* 23*/        cout << letter << "." << endl;
	   }
/* 24*/        return 0;
} // end main()
