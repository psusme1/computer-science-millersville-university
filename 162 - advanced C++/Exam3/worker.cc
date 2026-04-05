//Shawn Englerth
//CSCI 162 
//Dr. Zoppetti
//Final Exam
//worker.cc file

  
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

#include "worker.h"


double Worker::total_weekly_pay = 0;

//WORKER CONSTRUCTOR
//====================================
Worker::Worker (string nombre, double rate) :  name (nombre), payrate (rate)
{
}
//====================================
//END CONSTRUCTOR



//GET WORKER
//====================================
void
Worker::getWorker ()
{
  cout << "Name = " << name << " Rate = $" << fixed << showpoint
       << setprecision (2) << payrate;
}
//====================================
//end
 


//INSERTION OPERATOR OVERLOADED
//====================================
ostream&
operator<< (ostream &output, const Worker &worker)
{
  output << "Employee Name = " << worker.name << " Employee Salary Rate = $" << fixed << showpoint << setprecision (2) << worker.payrate << ".";

  return (output);
}
//====================================
//END OSTREAM OVERLOAD


  

