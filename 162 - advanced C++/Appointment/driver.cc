//Shawn Englerth
//CSCI 162 
//Dr. Zoppetti
//July 08, 2003
//driver file for appointment

//INCLUDED HEADER FILES
//==========================================================================
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

using namespace std;

#include "date.h"
#include "appt.h"
#include "weekly.h"
#include "monthly.h"
#include "daily.h"
#include "onetime.h"
//==========================================================================

//PROTOTYPE FUNCTIONS
//==========================================================================

void setAppointment (string &, Date &);
Date getDate ();
void printMenu ();
//==========================================================================


//MAIN FUNCTION BEGINS
//==========================================================================
int 
main ()
{

  bool invalid;
  //bool invalid2;       //boolean variables for do-while loop control
  Date dd;                      //instantiate a Date object for Appointment parameters
  string descript;              //instantiate a 'string' variable for Appointment param.
  vector <Appointment *> v;     //to store our created appointment objects in.
  Appointment *apptPtr;         //used to assign the 'new' returned pointer
  int choice, choice2;                   //used for menu choice.

  for (int i = 0; i < 20; i++)
    cout << endl;
  
  cout << "IMPORTANT NOTE IMPORTANT NOTE IMPORTANT NOTE IMPORTANT NOTE IMPORTANT NOTE\n"
       << "==========================================================================\n" 
       << "The following program will allow the user to choose different\n"
       << "types of appointments to enter into the appointment book.  Each\n"
       << "appointment consists of a description and a date.  The description\n"
       << "consists of a brief phrase or sentence.  The date part of the\n"
       << "appointment consists of a CURRENT or FUTURE month, day, and year.\n"
       << "Invalid entries will be set to 01-01-2003 for MM-DD-YYYY respectively.\n"; 
  do { 
    
    cout << "\nCHOOSE A TYPE OF APPOINTMENT TO ADD TO THE APPOINTMENT BOOK!\n";
    printMenu ();
    cin >> choice;
    
    switch (choice)
      {
      case 1 : 
	invalid = false;
	break;
	
      case 2 :
	setAppointment (descript, dd);
	apptPtr = new OneTime (descript, dd);
	v.push_back (apptPtr);
	invalid = true;
	break;
	
      case 3 :
	setAppointment (descript, dd);
	apptPtr = new Daily (descript, dd);
	v.push_back (apptPtr);
	invalid = true;
	break;
	
      case 4 :
	setAppointment (descript, dd);
	apptPtr = new Monthly (descript, dd);
	v.push_back (apptPtr);
	invalid = true;
	break;
	
      case 5 :
	setAppointment (descript, dd);
	apptPtr = new Weekly (descript, dd);
	v.push_back (apptPtr);
	invalid = true;
	break;
      }//end switch
    
    
  }while (invalid); //end inner do while
  
  do {  
    Date date1 = getDate ();
    
    for ( unsigned i = 0; i < v.size (); i++)
      if ( v[i] -> occursOn (date1))
        {
	  cout << typeid (*v[i]).name () << " ";
	  v[i]->getAppointment ();
          cout << endl;
	}

    cout << "\nENTER 0 TO QUIT: ENTER 1 TO CONTINUE > ";
    cin >> choice2;
    
  } while (choice2 != 0);  //end outter do while
  
  
  return (0);
}
//end main


//PRINT MENU FUNCTION
//==================================================================================
void
printMenu ()
{
  
  cout << "\nCHOOSE A TYPE OF APPOINTMENT.\n\n";
  cout << "1 = TO QUIT ADDING APPOINTMENTS\n";
  cout << "2 = ONE TIME APPOINTMENT\n";
  cout << "3 = DAILY APPOINTMENT\n";
  cout << "4 MONTHLY APPOINTMENT\n";
  cout << "5 WEEKLY APPOINTMENT\n";
  cout << "ENTER CHOICE 1 THROUGH 5...> ";
}

//SET APPOINTMENT FUNCTION
//===================================================================================
void
setAppointment (string &descript, Date &dd)
{
  cout << "\nEnter a description of the appointment > ";
  cin.ignore ();
  getline (cin, descript);
  
  cout << "\nEnter the date of the appointment (example: 07-08-2003) > ";
  cin >> dd;
}
//===================================================================================
//END


//GET DATE FUNCTION BEGINS
//===================================================================================
Date
getDate ()
{
  Date temp;

  cout << "\n\nWHAT DATE WOULD YOU LIKE TO VIEW THE APPOINTMENTS OF.\n";
  cout << "\nENTER THE DATE IN THE FOLLOWING FORMAT: MM-DD-YYYY\n > ";
  cin >> temp;

  return (temp);
}
//===================================================================================
//END


