//Shawn Englerth
//driver file for worker class

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

#include "worker.h"
#include "hourly.h"
#include "salaried.h"

int 
main ()
{ 
  Hourly emp1 ("John Smith", 8.50);
  Hourly emp2 ("Mike Schmidt", 10.00);

  Salaried emp3 ("Dave Thomas", 12.00);
  Salaried emp4 ("Joe Davis", 5.50);

  vector <Worker*> company (4);

  company[0] = &emp1;
  company[1] = &emp2;
  company[2] = &emp3;
  company[3] = &emp4;

  for (int i = 0; i < company.size (); i++)
    {
      int hours_worked;

      cout << endl;
      
      company[i] -> getWorker ();
      cout << "\nPlease Enter Hours worked for this employee > ";
      cin >> hours_worked;
      cout << "Paycheck amount = ";
      cout << company[i] -> computePay (hours_worked) << endl;
    }

  cout << "\nThe company total pay for the week = $" << fixed << showpoint << setprecision (2) <<  Worker::total_weekly_pay;
  cout << endl << endl << endl;

  return (0);
} //end main 
