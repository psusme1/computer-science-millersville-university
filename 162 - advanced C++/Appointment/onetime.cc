//Shawn Englerth
//CSCI 162
//Dr. Zoppetti
//July 10, 2003
//onetime.cc file

#include <string>

using namespace std;

#include "appt.h"
#include "date.h"
#include "onetime.h"


//ONETIME APPOINTMENT CONSTRUCTOR
//===========================================================================
OneTime::OneTime (const string one_appt, Date one_date)
  : Appointment (one_appt, one_date)
{
  //empty body
}
//===========================================================================
//END CONSTRUCTOR


//OCCURS ON FUNCTION BEGINS
//===========================================================================
bool
OneTime::occursOn (Date one_date)
{
  return (d.getMonth () == one_date.getMonth () && d.getDay () == one_date.getDay () 
              && d.getYear () == one_date.getYear ());  

  //a one time appointment only occurs once.  it has a unique month, day,
  //and year value assigned to it. all three data members must equal the 
  //current date for the appointment to occur.  if these conditions are 
  //not met exactly, then it is not a one time appointment.
}
//===========================================================================
//END OCCURS ON FUNCTION


//VIRTUAL DESTRUCTOR
//===========================================================================
OneTime::~OneTime ()
{
}
//===========================================================================
//END VIRTUAL DESTRUCTOR
