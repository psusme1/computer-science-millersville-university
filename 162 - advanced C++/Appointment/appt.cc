//Shawn Englerth
//CSCI 162
//Dr. Zoppetti
//July 07, 2003
//base_appt.cc file

#include <iostream>

using namespace std;

#include "date.h"
#include "appt.h"

//APPOINTMENT CONSTRUCTOR
//===========================================================================
Appointment::Appointment (const string some_appt, Date some_date)
  : appt (some_appt), d (some_date)
{
}
//===========================================================================
//END CONSTRUCTOR


//APPOINTMENT DESTRUCTOR
//===========================================================================
Appointment::~Appointment ()
{
  //Appointment object Destroyed
}
//===========================================================================
//END DESTRUCTOR


//GET APPOINTMENT DESCRIPTION FUNCTION
//===========================================================================
void 
Appointment::getAppointment ()
{
  cout << appt;  
}
//===========================================================================
//END 
