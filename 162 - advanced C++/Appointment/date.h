//Shawn Englerth
//CSCI 162
//Dr. Zoppetti
//July 03, 2003
//date.h File
 
#ifndef DATE_H
#define DATE_H

#include <iostream>

// class Date definition
class Date {

  friend ostream &operator<< (ostream &, const Date &);
  friend istream &operator>> (istream &, Date &);

public:
   Date (int = 1, int = 1, int = 2003); // default constructor
   void print () const;

   void setDate (int, int, int);
   
   void setMonth (int);
   int getMonth () const;

   void setDay (int);
   int getDay () const;

   void setYear (int);
   int getYear () const;
   
   bool isLeapYear () const;
   bool operator== (Date&) const;
   bool operator> (Date&) const;
   
   bool operator<= (Date&) const;
     
   int monthDays ();
   void nextDay ();

private:
   int month;
   int day;
   int year;

}; // end class Date

#endif // DATE_H

