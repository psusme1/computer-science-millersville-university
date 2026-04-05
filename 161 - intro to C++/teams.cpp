// Shawn Englerth
// teams.cpp
// This program reports on programming teams
#include <iostream>
using namespace std;

void NameTeam(char);
void NextOpponent(char);  // Put the prototypes for your two functions here:

int main ()
{
    char choice;               // W for which team I'm on; N for next opponent
    char initial;              // first initial -- determines team membership

    cout << endl << endl;
    cout << "This program gives information on four programming teams." << endl;
    cout << endl;
    cout << "Would you rather know which team you're on?...(enter a 'W')" << endl;
    cout << "Or which team you play next?...(enter an 'N')" << endl << endl;
    cout << "Enter a W or N> ";
    cin >> choice;
    cout << endl << endl;

    if ((choice != 'W') && (choice != 'N'))
        cout << "You must enter a W or an N" << endl;
    else
    {  
	 
	  cout << "Enter the first letter of your last name> ";
          cin >> initial;
          cout << endl << endl;
         
        if (choice == 'W')
         {
          cout << "The team that you play on is the ";
          NameTeam (initial);
          cout << "." << endl << endl << endl;
         }

        
	else
        {
           cout << "The team that you play next is the ";
           NextOpponent (initial);
           cout << "." << endl << endl << endl;
        }
    }
    return 0;
}
// end main

// Put your two function definitions here:
void NameTeam(char x)
{
    if (x < 'G')
        cout << "Giants";
    else if (x < 'M')
        cout << "Gators";
    else if (x < 'Q')
        cout << "Grizzlys";
    else if (x < 'Z')
	cout << "Gazelles";
    
}


void NextOpponent(char y)

{
    if (y <'G')
        cout << "Gazelles";
    else if (y < 'M')
        cout << "Grizzlys";
    else if (y < 'Q')
        cout << "Gators";
    else
        cout << "Giants";
}




