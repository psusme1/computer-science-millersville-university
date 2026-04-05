//Shawn Englerth
//Csci 162
//Dr. Zoppetti

#include <iostream>
using namespace std;
#include "complex.h"

int 
main ()
{
  Complex c1, c2;

  c1.setReal (5.0);
  c1.setImaginary (5.0);
  c1.printComplex ();
  c2.addComplex (5.0, 6.0);
  c2.printComplex ();
  c1.addComplex (5.3, 20.4);
  c1.printComplex ();

return (0);
}
  

