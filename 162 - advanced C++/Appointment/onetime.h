//Shawn Englerth
//CSCI 162
//Dr. Zoppetti
//July 10, 2003
//onetime.h file

#ifndef ONETIME_H
#define ONETIME_H

#include "date.h"
#include "appt.h"
#include <string>

class OneTime : public Appointment {

public:
  
  OneTime (const string one_appt, Date one_date);
  virtual ~OneTime ();

  virtual bool occursOn (Date one_date);

}; //end class OneTime

#endif // ONETIME_H
