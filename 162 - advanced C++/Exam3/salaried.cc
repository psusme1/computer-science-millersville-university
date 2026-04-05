//Shawn Englerth
//CSCI 162 
//Dr. Zoppetti
//Final Exam
//salaried.cc file

#include <string>
#include <iostream>

using namespace std;

#include "worker.h"
#include "salaried.h"


//HOURLY CONSTRUCTOR
//====================================
Salaried::Salaried (string nombre, double rate) :  Worker (nombre, rate)
{
}
//====================================
//END CONSTRUCTOR



//COMPUTE PAY FUNCTION BEGINS
//====================================
double
Salaried::computePay (int hours)
{
  Worker::total_weekly_pay += (40.0 * payrate);

  return (40.0 * payrate);
}
//====================================
//END COMPUTE PAY

