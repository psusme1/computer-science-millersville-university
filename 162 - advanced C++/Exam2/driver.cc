//shawn englerth
//driver file

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

#include "piano.h"
#include "grand.h"

int 
main ()
{
  Grand myPiano ("Steinway", "ST200", 56, true);
 
  myPiano.print ();

}
//end main
  
  
