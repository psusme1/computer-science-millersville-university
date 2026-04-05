//Shawn Englerth
//CSCI 162 
//Dr. Zoppetti
//Final Exam
//hourly.cc file

#include <string>
#include <iostream>

using namespace std;

#include "worker.h"
#include "hourly.h"


//HOURLY CONSTRUCTOR
//====================================
Hourly::Hourly (string nombre, double rate) :  Worker (nombre, rate)
{
}
//====================================
//END CONSTRUCTOR



//COMPUTE PAY FUNCTION BEGINS
//====================================
double
Hourly::computePay (int hours)
{
  double hh = static_cast <double> (hours);

  if (hh < 40)
    {
      double pay = hh * payrate;
      Worker::total_weekly_pay += pay;
      return (pay);
    }
 
  else 
    {
      double overtime = hh - 40;
      Worker::total_weekly_pay += (overtime * 1.5 + (40 * payrate));
      return (overtime * 1.5 + (40 * payrate));
    }
    
}
//====================================
//END COMPUTE PAY
