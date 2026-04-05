//Shawn Englerth
//CSCI 162 
//Dr. Zoppetti
//Final Exam
//hourly.h file

#ifndef HOURLY_H
#define HOURLY_H

#include <string>

#include "worker.h"


class Hourly : public Worker {

public:
  Hourly (string nombre, double rate);       //constructor for Worker
  
  virtual double computePay (int);           //computes hourly employee's pay
  

protected:
  

}; //end class Hourly

#endif //Hourly_H


