//shawn englerth
//csci 162
//exam 2
//piano.h file

#ifndef PIANO_H
#define PIANO_H

#include <string>

//class definition
class Piano 
{

public:

  Piano (string make, string type, int keys, bool digital);
  virtual void print () const;
  virtual void play () const = 0;
    
  
protected:

  string manufacturer;
  string model;
  int no_keys;
  bool is_digital;

};

 // end class Piano

#endif //PIANO_H

