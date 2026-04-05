//Shawn Englerth
//CSCI 162
//Dr. Zoppetti
//July 09, 2003
//date.cc file

#include <iostream>

using namespace std;

#include "date.h"

//DATE CONSTRUCTOR
//===========================================================================
Date::Date (int m, int d, int y) 
{ 
   setDate (m, d, y); 
}
//===========================================================================
//END CONSTRUCTOR


//GET DAY FUNCTION BEGINS
//===========================================================================
int
Date::getDay () const
{
   return (day); 
}
//===========================================================================
//END GET DAY


//GET MONTH FUNCTION BEGINS
//===========================================================================
int
Date::getMonth () const
{
   return (month);
}
//===========================================================================
//END GET MONTH


//GET YEAR FUNCTION BEGINS
//===========================================================================
int
Date::getYear () const
{ 
   return (year); 
}
//===========================================================================
//END GET YEAR


//SET DAY FUNCTION BEGINS
//===========================================================================
void
Date::setDay (int d)
{
  //check to see if the month is february and to see if it is a leap year.
  //we must make sure we assign the proper number of days to february 
  //accordingly  
  
  if (month == 2 && isLeapYear ())
    day = (d <= 29 && d >= 1) ? d : 1;  
  
  
  //if it is not february, we must determine what month it is. if an invalid
  //value is entered, we default the setting of the day to the first of the 
  //month.
  
  else
    day = (d <= monthDays () && d >= 1) ? d : 1;
}
//===========================================================================
//END SET DAY


//SET MONTH FUNCTION BEGINS
//===========================================================================
void
Date::setMonth (int m) 
{
  //set the month of the year accordingly.  invalid entries will 
  //default the month to january.
  
  month = m <= 12 && m >= 1 ? m : 1; 
}
//===========================================================================
//END SET MONTH


//SET YEAR FUNCTION BEGINS
//===========================================================================
void
Date::setYear (int y)
{
  //set the year of the date accordingly.  invalid values will default
  //to the year being set to 2003.  the year must be a year between 
  //2003 and 2200.
  
  year = y <= 2200 && y >= 2003 ? y : 2003;
}
//===========================================================================
//END SET YEAR


//SET DATE FUNCTION BEGINS
//===========================================================================
void
Date::setDate (int mo, int dy, int yr)
{
  //allows the user to set the entire date field with one function.  this
  //function makes separate calls to the other individual member functions
  
  setMonth (mo);
  setDay (dy);
  setYear (yr);
}
//===========================================================================
//END SET DATE


//PRINT DATE FUNCTION BEGINS
//===========================================================================
void 
Date::print () const
{ 
  cout << month << '-' << day << '-' << year << '\n'; 
}
//===========================================================================
//END PRINT


//NEXT DAY FUNCTION BEGINS
//===========================================================================
void 
Date::nextDay ()
{
  setDay(day + 1);
  
  if (day == 1)
    {
      setMonth (month + 1);
      if (month == 1)
	setYear (year + 1);
      
    } // end if
}
//===========================================================================
//END NEXT DAY


//IS LEAP YEAR FUNCTION BEGINS
//===========================================================================
bool 
Date::isLeapYear () const
{
  //we need to know if it is a leap year so we can assign the correct
  //number of days to the month of february.  we return true if 
  //the year is evenly divisible by 400 -OR- we can return true if
  //the year is evenly divisible by 4 and it is not a century year.
  
  return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}
//===========================================================================
//END IS LEAP YEAR


//MONTH DAYS FUNCTION BEGINS (RETURNS PROPER NO. OF DAYS FOR MONTH)
//===========================================================================
int 
Date::monthDays ()
{
  const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  
  return (month == 2 && isLeapYear() ? 29 : days[month - 1]);
}
//===========================================================================
//END MONTH DAYS


//OPERATOR EQUALITY OVERLOADED
//===========================================================================
bool
Date::operator== (Date &date) const
{
  return (month == date.month && day == date.day && year == date.year);
}
//===========================================================================
//END OPERATOR EQUALITY OVERLOAD


//OPERATION<< OVERLOADED
//===========================================================================
ostream&
operator<< (ostream &output, const Date &date)
{
  output << date.month << "-" << date.day << "-" << date.year;
  
  return (output);
}
//===========================================================================
//END OPERATION<< OVERLOADED


//OPERATION LESS THAN OR EQUAL 
//===========================================================================
bool
Date::operator<= (Date &date) const
{
  if (year > date.year)
    return (true);
  else if (month > date.month)
    return (true);
  else if (day > date.day)
    return (true);
  else 
    return (false);
  
}
//===========================================================================
//END OPERATION LESS THAN OR EQUAL 


//OPERATION GREATER THAN
//===========================================================================
bool
Date::operator> (Date &date) const
{
  if (date.year > year)
    return (true);
  else if (date.month > month)
    return (true);
  else if (date.day > day)
    return (true);
  else
    return (false);
}
//===========================================================================
//OPERATION GREATER THAN

//EXTRACTION OPERATOR OVERLOAD
//===========================================================================
istream&
operator>> (istream &input, Date &date)
{
  input >> date.month;
  input.ignore ();
  input >> date.day;
  input.ignore ();
  input >> date.year;
  
  return (input);
}
//===========================================================================
//END
