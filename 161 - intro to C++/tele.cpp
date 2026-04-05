// tele.cpp
// This program prints the number that appears on the phone for a given letter

#include <iostream>
using namespace std;

int main ()
{
    char letter;               // letter on telephone
    int  number;                // corresponding number

    cout << "This program gives the number on the phone given a letter." << endl;
    cout << "Enter a letter> ";
    cin >> letter;
    if ((letter < 'A') || (letter > 'Y'))
        cout << "You must enter a letter between A and Y." << endl;
          else if (letter == 'Q')
             cout << "Q does not appear on the telephone dial." << endl;
          else if (letter >= 'W')
	      number = 9;
          else if (letter >= 'T')
	      number = 8;
          else if (letter >= 'P')
	      number = 7
          else if (letter >= 'M')
	      number = 6;
          else if (letter >= 'J')
	      number = 5;
          else if (letter >= 'G')
	      number = 4;
          else if (letter >= 'D')
	      number = 3;
	  else
              number = 2;

	  cout << "The letter " << letter << " corresponds to the number " << number << endl;
	  }

