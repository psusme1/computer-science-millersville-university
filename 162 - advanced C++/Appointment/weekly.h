//Shawn Englerth
//CSCI 162
//Dr. Zoppetti
//July 10, 2003
//weekly.h file

#ifndef WEEKLY_H
#define WEEKLY_H

#include "date.h"
#include "appt.h"
#include <string>

class Weekly : public Appointment {

public:
  
  Weekly (const string one_appt, Date one_date);
  virtual ~Weekly ();

  virtual bool occursOn (Date one_date);

}; //end class Weekly

#endif // WEEKLY_H
