//Shawn Englerth
//CSCI 162
//Dr. Zoppetti
//July 10, 2003
//daily.h file

#ifndef DAILY_H
#define DAILY_H

#include "date.h"
#include "appt.h"
#include <string>

class Daily : public Appointment {

public:
  
  Daily (const string one_appt, Date one_date);
  virtual ~Daily ();

  virtual bool occursOn (Date one_date);

}; //end class Daily

#endif // DAILY_H
