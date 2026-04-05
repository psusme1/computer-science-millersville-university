//Shawn Englerth
//June 17, 2003
//CSCI 162
//Chapter 7, page 545, 7.9
//Dr. Zoppetti
//header file IntegerSet.h

#ifndef INTEGERSET_H
#define INTEGERSET_H

#include <iostream>
using namespace std;

const int maxSize = 101;

//class IntegerSet definition
//===============================================================================
class IntegerSet {

friend ostream& operator<< (ostream&, const IntegerSet& setA);

public:
  IntegerSet ();
  IntegerSet (int inputArray[], const int size);

  IntegerSet unionOfSets (const IntegerSet& setA);
  IntegerSet intersectionOfSets (const IntegerSet& setA);
  void emptySet ();
  IntegerSet& insertElement (int);
  IntegerSet& deleteElement (int);
  void printSet ();
  bool isEqualTo (const IntegerSet& setA);
  IntegerSet operator+ (const IntegerSet& setA);
  IntegerSet operator* (const IntegerSet& setA);

private:
  int array[maxSize];

  bool validEntry (int num) const
  {
    return (num >= 0 && num < maxSize);
  }

};
#endif

/* IntegerSet  s1, s2;
   int A[] = { 5, 10, 15, -1, 20 };
   Integerset s3 (A, 5);
   s2.insert (20);
   s1 = s3.unionOfSets (s2);

   */
