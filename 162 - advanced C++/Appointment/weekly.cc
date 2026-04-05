//Shawn Englerth
//CSCI 162
//Dr. Zoppetti
//July 10, 2003
//weekly.cc file

#include <string>
#include <ctime>
#include <cmath>

using namespace std;

#include "appt.h"
#include "date.h"
#include "weekly.h"

//WEEKLY APPOINTMENT CONSTRUCTOR
//===========================================================================
Weekly::Weekly (const string week_appt, Date week_date)
  : Appointment (week_appt, week_date)
{
  //empty body
}
//===========================================================================
//END CONSTRUCTOR


//OCCURS ON FUNCTION BEGINS
//===========================================================================
bool
Weekly::occursOn (Date week_date)
{
   tm x;
   
   x.tm_sec = 0;  //all unused members of struct tm must be initialized to
   x.tm_min = 0;  //zero for proper processing of the function difftime.
   x.tm_hour = 0; //struct tm is found in the <ctime> header file.
   x.tm_wday = 0;
   x.tm_yday = 0;
   x.tm_isdst = 0;

   x.tm_mday = week_date.getDay ();  //sets struct data member mday to the day of year
   x.tm_mon = week_date.getMonth () - 1;  //starts default at zero for january
   x.tm_year = week_date.getYear () - 1900;  //years since 1900

   tm y;
    
   y.tm_sec = 0;    //all notes from above apply exactly here
   y.tm_min = 0;
   y.tm_hour = 0;
   y.tm_wday = 0;
   y.tm_yday = 0;
   y.tm_isdst = 0;

   y.tm_mday = d.getDay ();
   y.tm_mon = d.getMonth () - 1;
   y.tm_year = d.getYear () - 1900;

   time_t a, b;  //must create two time_t objects so we can use function difftime ()

   a = mktime (&x); //converts tm struct objects to time_t objects
   b = mktime (&y); //converts tm struct objects to time_t objects

   double sec = difftime (a, b);  //calculates time difference in seconds
   
   if (sec < 0)  //negative seconds represent date that has passed
     return (false);  //false if date is before current date
   
   int days = static_cast<int> (sec / (60 * 60 * 24)); //cast double seconds to integer 
                                                       //value of seconds
   return (days % 7 == 0);  //determines if it is current date or a 7 day
                            //multiple of the date for weekly assingnment
}
//===========================================================================
//END OCCURS ON FUNCTION


//VIRTUAL DESTRUCTOR
//===========================================================================
Weekly::~Weekly ()
{
}
//===========================================================================
//END VIRTUAL DESTRUCTOR

 
