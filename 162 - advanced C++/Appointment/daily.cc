//Shawn Englerth
//CSCI 162
//Dr. Zoppetti
//July 10, 2003
//daily.cc file

#include <string>

using namespace std;

#include "appt.h"
#include "date.h"
#include "daily.h"


//DAILY APPOINTMENT CONSTRUCTOR
//===========================================================================
Daily::Daily (const string daily_appt, Date daily_date)
  : Appointment (daily_appt, daily_date)
{
  //empty body
}
//===========================================================================
//END CONSTRUCTOR


//OCCURS ON FUNCTION BEGINS
//===========================================================================
bool
Daily::occursOn (Date daily_date)
{
  if (daily_date.getYear () > d.getYear ())
    return (true);
  else if (daily_date.getMonth () > d.getMonth ())
    return (true);
  else if (daily_date.getDay () >= d.getDay ())
    return (true);
  else
    return (false);         
}
//===========================================================================
//END OCCURS ON FUNCTION

//VIRTUAL DESTRUCTOR
//===========================================================================
Daily::~Daily ()
{
}
//===========================================================================
//END VIRTUAL DESTRUCTOR
//Daily A ("see dentist", 07, 08, 1974);
//cout << A.occursOn (07, 08, 1974) ? "True" : "False";
