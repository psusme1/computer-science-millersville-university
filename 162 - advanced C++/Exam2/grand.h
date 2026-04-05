#ifndef GRAND_H
#define GRAND_H

#include <iostream>
#include <string>
using namespace std;

#include "piano.h"




//class definition
class Grand : public Piano {

public:
  Grand (string make, string type, int keys, bool digital);
  virtual void print () const;
  virtual void play () const;

}; // end class Grand

#endif //GRAND_H


