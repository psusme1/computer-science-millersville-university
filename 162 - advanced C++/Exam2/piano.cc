#include <iostream>
#include <string>

using namespace std;

#include "piano.h"

//constructor
Piano::Piano (string make, string type, int keys, bool digital) 
{
  no_keys = keys;
  manufacturer = make;
  model = type;
  is_digital = digital;
}

void
Piano::print () const
{
  cout << "Manufacturer = " << manufacturer << " , Model = " << model 
       << " , Keys = " << no_keys << " ,Digital = " << (is_digital ? "True" : "False") << endl;
}
//end print function
