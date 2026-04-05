//Shawn Englerth
//Csci 330
//September 13, 2003
//Class Item header file
//===========================================================================
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

#include "item.h"



//===========================================================================
//ITEM DEFAULT CONSTRUCTOR 
//===========================================================================
Item::Item () : price (1.00) , description ("")
{

}



//===========================================================================
//ITEM CONSTRUCTOR 
//===========================================================================
Item::Item (float amount, string descript) : description (descript)
{
  setPrice (amount);
  setDescription (descript);
}



//===========================================================================
//SET PRICE FUNCTION BEGINS
//===========================================================================
void
Item::setPrice (float amount)
{
  if (amount < 1000 && amount >= 0)
    {
      price = amount;
    }
 
  else
    {
      price = 1;
    }
}  



//===========================================================================
//SET DESCRIPTION FUNCTION BEGINS
//===========================================================================
void 
Item::setDescription (string descript)
{
  description.assign (descript, 0, 40);
}



//===========================================================================
//OPERATOR<< OVERLOADED FRIEND FUNCTION BEGINS
//===========================================================================
ostream&
operator<< (ostream &output, const Item &item)
{
  output << setw (40) << left << item.description << "  ";
  
  output << setw (8) << right << fixed << showpoint 
	 << setprecision (2) << item.price;
  
  return (output);
}



//===========================================================================
//OPERATOR>> OVERLOADED FRIEND FUNCTION BEGINS
//===========================================================================
istream&
operator>> (istream &input, Item &item)
{
  input >> item.price;
  input >> ws;
  input >> item.description;

  return (input);
}



//===========================================================================
//GET PRICE FUNCTION BEGINS
//===========================================================================
float
Item::getPrice ()
{
  return (price);
}



//===========================================================================
//GET DESCRIPTION FUNCTION BEGINS
//===========================================================================
string
Item::getDescription ()
{
  return (description);
}



//===========================================================================
//ITEM DESTRUCTOR
//===========================================================================
Item::~Item ()
{
  //Item object destroyed
}
