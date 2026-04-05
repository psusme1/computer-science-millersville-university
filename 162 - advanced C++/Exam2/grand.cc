//shawn englerth
//grand.cc file


#include <iostream>
#include <string>

#include "grand.h"

using std::string;

//constructor
Grand::Grand (string make, string type,int keys, bool digital) : Piano (make, type, keys, digital)
{
  no_keys = keys;
  manufacturer = make;
  model = type;
  is_digital = digital;
}

void 
Grand::print () const
{
  Piano::print ();
}

void 
Grand::play () const
{
  cout << "\nGrand Piano " << manufacturer << " Now Playing!" << endl;
}

