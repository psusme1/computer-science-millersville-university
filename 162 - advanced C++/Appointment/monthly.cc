//Shawn Englerth
//CSCI 162
//Dr. Zoppetti
//July 10, 2003
//monthly.cc file

#include <string>

using namespace std;

#include "appt.h"
#include "date.h"
#include "monthly.h"


//MONTHLY APPOINTMENT CONSTRUCTOR
//===========================================================================
Monthly::Monthly (const string month_appt, Date month_date)
  : Appointment (month_appt, month_date)
{
  //empty body
}
//===========================================================================
//END CONSTRUCTOR


//OCCURS ON FUNCTION BEGINS
//===========================================================================
bool
Monthly::occursOn (Date month_date)
{
  return (d.getDay () == month_date.getDay ());
}
//===========================================================================
//END OCCURS ON FUNCTION


//VIRTUAL DESTRUCTOR
//===========================================================================
Monthly::~Monthly ()
{
}
//===========================================================================
//END VIRTUAL DESTRUCTOR
//Monthly A ("see dentist", 07, 08, 1974);
//cout << A.occursOn (07, 08, 1974) ? "True" : "False";
