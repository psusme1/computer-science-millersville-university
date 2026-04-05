//Shawn Englerth
//June 17, 2003
//CSCI 162
//Chapter 7, page 545, 7.9
//Dr. Zoppetti
//implementation file integerSet.cc

//PREPROCESSOR DIRECTIVES
//==================================
#include <iostream>
using namespace std;

#include "integerSet.h"
//==================================

//CONTSTRUCTOR INTEGER SET WITH NO ARGUMENTS AND MAX SIZE INITIALIZER
//======================================================================
IntegerSet::IntegerSet ()
{
  emptySet ();
}
//======================================================================
//CONSTRUCTOR INTEGER SET ENDS


//CONSTRUCTOR INTEGER SET WITH TWO ARGUMENTS
//======================================================================
IntegerSet::IntegerSet (int inputArray[], const int size)
{
  emptySet ();

  for (int i = 0; i < size; i++)
    {
      if (validEntry (inputArray[i]))
        array[inputArray[i]] = 1;
    }
}
//======================================================================
//CONSTRUCTOR INTEGER SET ENDS


//EMPTY SET FUNCTION BEGINS
//======================================================================
void
IntegerSet::emptySet ()
{
  for (int i = 0; i < maxSize; i++)
    array[i] = 0;
}
//======================================================================
//EMPTY SET FUNCTION ENDS


//INSERT ELEMENT FUNCTION BEGINS
//======================================================================
IntegerSet&
IntegerSet::insertElement (int number)
{
  if (validEntry (number))
    array[number] = 1;
  else
   cout << "\nInvalid Input! Please enter an integer within the range 0 to " << maxSize - 1 << "." << endl;
  return (*this);
}
//======================================================================
//INSERT ELEMENT FUNCTION ENDS


//DELETE ELEMENT FUNCTION BEGINS
//======================================================================
IntegerSet&
IntegerSet::deleteElement (int number)
{
  if (validEntry (number))
    array[number] = 0;
  else
    cout << "\nInvalid Input! Please enter an integer within the range 0 to " << maxSize - 1 << "." << endl;
  return (*this);
}
//======================================================================
//DELETE ELEMENT FUNCTION ENDS


//INTERSECTION OF TWO SETS FUNCTION BEGINS
//======================================================================
IntegerSet
IntegerSet::intersectionOfSets (const IntegerSet& setA)
{
  IntegerSet setC;

  for (int i = 0; i < maxSize; i++)
    {
      if ((array[i] == setA.array[i]) && array[i])
        setC.array[i] = 1;
    }

  return (setC);
}
//======================================================================
//INTERSECTION OF TWO SETS FUNCTION ENDS


//UNION OF TWO SETS FUNCTION BEGINS
//======================================================================
IntegerSet
IntegerSet::unionOfSets (const IntegerSet& setA)
{
  IntegerSet setC;

  for (int i = 0; i < maxSize; i++)
    if (array[i] == 1 || setA.array[i] == 1)
      setC.array[i]=1;

  return (setC);
}
//======================================================================
//UNION OF TWO SETS FUNCTION ENDS


//IS EQUAL TO FUNCTION BEGINS
//======================================================================
bool
IntegerSet::isEqualTo (const IntegerSet& setA)
{
  int counter = 0;

  for (int i = 0; i < maxSize; i++)
    {
     if (array[i] == setA.array[i])
       counter++;
    }

  return (counter == maxSize);
}
//======================================================================
//IS EQUAL TO FUNCTION ENDS

//PRINT SET FUNCTION BEGINS
//======================================================================
void
IntegerSet::printSet ()
{
  bool empty = true;

  cout << "{ ";
  for (int i = 0; i < maxSize; i++)
    {
      if (array[i])
        {
	  cout << i << " ";
	  empty = false;
	}
    }

  if (empty)
    cout << "--- } ";
  else
    cout << "}";
}
//======================================================================
//PRINT SET FUNCTION ENDS


//OPERATOR+ FUNCTION BEGINS (UNION OF SETS)
//======================================================================
IntegerSet
IntegerSet::operator+ (const IntegerSet& setA)
{
  IntegerSet setC;

  for (int i = 0; i < maxSize; i++)
    if (array[i] == 1 || setA.array[i] == 1)
      setC.array[i] = 1;

  return (setC);
}
//=======================================================================
//OPERATOR+ FUNCTION ENDS (UNION OF SETS)


//OPERATOR* FUNCTION BEGINS (INTERSECTION OF SETS)
//=======================================================================
IntegerSet
IntegerSet::operator* (const IntegerSet& setA)
{
  IntegerSet setC;

  for (int i = 0; i < maxSize; i++)
    if ( (array[i] == setA.array[i]) && array[i])
      setC.array[i] = 1;

  return (setC);

}
//=======================================================================
//OPERATOR * FUNCTION ENDS (INTERSECTION OF SETS)

//FRIEND FUNCTION OPERATOR<< BEGINS
//=======================================================================
ostream&
operator<< (ostream& output, const IntegerSet& setA)
{
  bool empty = true;

  output << "{ ";
  for (int i = 0; i < maxSize; i++)
    {
      if (setA.array[i])
        {
	  output << i << " ";
	  empty = false;
	}
    }

  if (empty)
    output << "--- } ";
  else
    output << "}";

return (output);
}
//=======================================================================
//FRIEND FUNCTION OPERATOR<< ENDS
