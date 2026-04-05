//Shawn Englerth
//CSCI 162
//Dr. Zoppetti
//July, 03, 2003
//Abstract Base Class appointment.h

#ifndef Appointment_H
#define Appointment_H

#include <string>
#include "date.h"


class Appointment {

public:
  Appointment (const string some_appt, Date some_date);
  virtual ~Appointment ();
  
  virtual bool occursOn (Date some_date) = 0;
  void getAppointment (); 
   
protected:
  const string appt;
  Date d;

};

#endif //Appointment_H
