//Shawn Englerth
//CSCI 162 
//Dr. Zoppetti
//Final Exam
//salaried.h file

#ifndef SALARIED_H
#define SALARIED_H

#include <string>

#include "worker.h"

class Salaried : public Worker {

  friend ostream &operator<< (ostream &, const Worker &);

public:
  Salaried (string, double);       //constructor for Worker
  virtual ~Salaried () {};
  
  virtual double computePay (int);    //computes employees pay
  

protected:
  


}; //end class Salaried

#endif //SALARIED_H
