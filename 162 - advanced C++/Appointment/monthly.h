//Shawn Englerth
//CSCI 162
//Dr. Zoppetti
//July 10, 2003
//monthly.h file

#ifndef MONTHLY_H
#define MONTHLY_H

#include "date.h"
#include "appt.h"
#include <string>

class Monthly : public Appointment {

public:
  
  Monthly (const string one_appt, Date one_date);
  virtual ~Monthly ();

  virtual bool occursOn (Date one_date);

}; //end class Monthly

#endif // MONTHLY_H
