//Shawn Englerth
//CSCI 162 
//Dr. Zoppetti
//Final Exam
//worker.h file

#ifndef WORKER_H
#define WORKER_H

#include <string>

class Worker {

  friend ostream &operator<< (ostream &, const Worker &);

public:
  Worker (string, double);       //constructor for Worker
  virtual ~Worker () {};

  void getWorker ();  
  virtual double computePay (int) = 0;    //computes employees pay

  static double total_weekly_pay;  //total weekly pay for company
 
 
protected:
  const string name;    //employee's name
  double payrate;       //hourly wage rate of employee

 
}; //end class Worker

#endif //WORKER_H


