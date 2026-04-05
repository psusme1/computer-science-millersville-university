// Tele.cpp
// This program prints the number that appears on the phone for a
// given letter.

#include <iostream>
#include <ctype.h>
using namespace std;

int main ()

{

  char letter; // The letter on the telephone.

  cout << "This program gives the number on the phone given a letter." <<  endl;
  cout << "Enter a letter> ";
  cin >> letter;
  letter = toupper(letter);
  while ((letter < 'A') || (letter > 'Y'))

    {
      cout << "You must enter a letter between A and Y" << endl;
      cout << "Enter a letter> ";
      cin >> letter;
      letter = toupper(letter);
    }

   if (letter == 'Q')
     cout << "Q does not appear on the telephone dial" << endl;
   else if (letter <= 'C')
     cout << "The number corresponding to " << letter << " is 2." << endl;
   else if (letter <= 'F')
     cout << "The number corresponding to " << letter << " is 3." << endl;
   else if (letter <= 'I')
     cout << "The number corresponding to " << letter << " is 4." << endl;
   else if (letter <= 'L')
     cout << "The number corresponding to " << letter << " is 5." << endl;
   else if (letter <= 'O')
     cout << "The number corresponding to " << letter << " is 6." << endl;
   else if (letter <= 'S')
     cout << "The number corresponding to " << letter << " is 7." << endl;
   else if (letter <= 'V')
     cout << "The number corresponding to " << letter << " is 8." << endl;
   else  // If (letter <= 'Y'): only possibility left...
     cout << "The number corresponding to " << letter << " is 9." << endl;

return 0;

}


