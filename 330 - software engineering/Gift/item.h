//Shawn Englerth
//Csci 330
//September 13, 2003
//Class Item header file

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

using namespace std;

class Item {

  friend ostream &operator<< (ostream &, const Item &);
  friend istream &operator>> (istream &, Item &);
  
public:
  Item (float, string);
  Item ();

  void setDescription (string);
  void setPrice (float);
  float getPrice ();
  string getDescription ();
  ~Item ();   
  
private:
  float price;
  string description;
  
}; //END CLASS ITEM

#endif
