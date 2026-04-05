//Shawn Englerth
//Csci 330 
//October 6, 2003
//Proffesor Katz
//Vector Lab



#ifndef _LBVECTOR_H
#define _LBVECTOR_H

#include <cstdlib>
#include <cassert>
#include <iostream>

//templated vector class, partially based on Budd, Classic Data Structures in C++


// written 11/5/93, modified 3/23/94
// changed on 3/9/95 to make all methods inline (defined in class decl)
// changed on 10/14/99 to clean up for vector lab in CS 330
// updated 10/03 by Shawn Englerth to allow lower and upperbounds


// for a vector of Items use lbvector<Item>,
//                   e.g., lbvector <int> intvector;
//                   note: Item must have a default constructor
//
// CONSTRUCTORS:
//
//   1.  lbvector ()     
//       --- default constructor
//                                   
//   2.  lbvector (int lower, int upper)
//       --- vector with lower and upper bounnd entries
//
//   3.  lbvector (int lower, int upper, Item fillValue)     
//       --- vector w/ lower bound, lower bound, and a fillValue
//
//   4.  lbvector (const lbvector & vec) 
//       --- copy constructor
//    
//   int capacity ()
//       --- returns capacity of vector
// 
//   void resize(int lower, int upper) 
//       --- resizes the vector to a new lower bound and a new upper bound.
//            can result in losing elements if new size < old size)
//
//   void fill(Item fillValue)  
//       --- set all entries equal to fillValue
//
//   operator =
//       --- assignment operator works properly
//
//   operator []
//       --- indexes both const and non-const vectors
//    
//
//  EXAMPLES OF USE:
//
//     lbvector <double> dlist (-3, 3);       
//       --- a vector with a lower bound of -3, and an upper bound of 3.
//
//     lbvector <double> dzlist (-3, 3, 0.0);
//       --- lower bound -3, upper bound 3, and each element initialized to 0.0
//
//     lbvector <int> ilist ();
//       --- has room for 0 ints
//
//
//  class invariant:
//  myList points to the beginning of the allocated space 
//  myCapacity is the number of elements allocated
//  myZero points to the zeroth element of the allocated space
//  myLower is the lowest bound of the allocated space
//  myUpper is the highest bound of the allocated space
//
/////////////////////////////////////////////////////////////////////////////

template <class Item> class lbvector
{
 public:
  //=================================================================================
  // default constructor 0 elements
  // postcondition: vector of zero items constructed and pointers are 
  // initialized to NULL.  Upper bound and lower bound are set to values that
  // are inaccesable to correctly represent an empty array.   
  lbvector () : myListPtr (0), myCapacity (0), myUpper (-1), myLower (0), myZeroPtr (0)
    {
     
    }
  
  
  //=================================================================================    
  // specify vector with a lower and an upper bound. set a pointer "myZeroPtr" to 
  // to point to where zeroth element would actually exist.  "myZeroPtr" is used
  // to allow user to use negative subscripting.
  // precondition: lower bound is less than or equal to upper bound
  // postcondition: vector with appropriate lower and upper bounds is created.
  // myListPtr should point to array Item and myZeroPtr should point to where
  // the zeroth element would be located.
  lbvector (int LB, int UB) : myUpper (UB), myLower (LB) 
    {
      //tests to make sure user supplies bounds in proper order
      assert (myLower <= myUpper);   

      myCapacity = ((myUpper - myLower) +1);

      //allocate new space and aim myListPtr to starting location of space
      myListPtr = new Item [myCapacity];

      //confirm myListPtr is pointing to something
      assert (myListPtr != 0);      

      //aim myZeroPtr to where zeroth element would be located
      myZeroPtr = (myListPtr - myLower);
    }
  
  
  //=================================================================================     
  // specify size and fill value
  // precondition: lower bound is less than or equal to upper bound.  
  // postcondition: constructed vector of size myCapacity.  myCapacity is greater than
  // or equal to zero.  myListPtr points to beginning of allocated space.  myZeroPtr
  // points to where zeroth element would be located.  Each item initialized 
  // to fillValue. Allocated space is filled with fillValue's.
  lbvector (int LB, int UB, Item fillValue) : myUpper (UB), myLower (LB)
    {
      assert (myLower <= myUpper);
      myCapacity = ((myUpper - myLower) +1);
      myListPtr = new Item [myCapacity];
      assert (myListPtr != 0);      
      myZeroPtr = (myListPtr - myLower);
      
      fill (fillValue);
    }
  
  
  //================================================================================= 
  // copy constructor
  // used to create a new and complete copy of the object (vec)
  // as when passing the object by value or returning object 
  // as a result - need a deep copy when using dynamic memory
  // precondition: Item supports assignment. vec.myCapacity >= 0.  
  // postcondition: constructed vector is an exact duplicate of vec.  All instance
  // variables are set appropriately.  myListPtr and myZeroPtr are pointing to 
  // the appropriate areas.          
  lbvector (const lbvector <Item> & vec) 
    {
      // allocate storage
      myCapacity = vec.myCapacity;
      myLower = vec.myLower;
      myUpper = vec.myUpper;
      myListPtr = new Item [myCapacity];
      assert (myListPtr != 0);
      myZeroPtr = (myListPtr - myLower);
      
      // copy elements from vec using myZeroPtr  
      for (int k = vec.myLower; k <= vec.myUpper; k++) 
	{
	  myZeroPtr[k] = vec.myZeroPtr[k];  
	}       
    }
  
  
  //================================================================================= 
  // free new'd storage
  // precondition: delete space only if it has been allocated.
  // postcondition: dynamically allocated storage freed
  ~lbvector () 
    {
      delete [] myListPtr;
    }
  
  
  //================================================================================= 
  // assignment
  // need a deep copy when using dynamic memory
  // precondition: Item supports assignment. vec.myCapacity >= 0.  
  // postcondition: vector is assigned exact copies of vec's contents.  All instance
  // variables are set appropriately.  myListPtr and myZeroPtr are pointing to 
  // the appropriate areas.
  lbvector & operator = (const lbvector <Item> & vec) 
    {
      // don't assign to self!
      if (this != &vec) 
	{
	  // out with old list, in with new
	  delete [] myListPtr;
	  myCapacity = vec.myCapacity;
	  myUpper = vec.myUpper;
	  myLower = vec.myLower;
	  myListPtr = new Item [myCapacity];
	  assert (myListPtr != 0);
	  myZeroPtr = (myListPtr - myLower);
	  	  
	  // copy elements from vec using myZero and vec.myZeroPtr
	  for (int k = vec.myLower; k <= vec.myUpper; k++) 
	    {
	      myZeroPtr[k] = vec.myZeroPtr[k];
	    }
	}
      return *this; //return this vec
    }
  
  
  //=================================================================================
  // change size dynamically
  // precondition: vector has room for myCapacity entries     
  // postcondition: vector has room for newSize entries the first myCapacity of
  //                which are copies of original unless newSize < myCapacity, then
  //                truncated copy occurs
  void resize(int newLower, int newUpper)
    {

      //use resize bounds to determine new space needed
      int newCapacity = ((newUpper - newLower) + 1);  

      //declare new pointer.  Allocate new space and point newMyListPtr to it
      Item * newMyListPtr = new Item[newCapacity];
      assert (newMyListPtr != 0);
      
      //declare new pointer.  Aim newMyZeroPtr to where zeroth element would
      //be located in newly allocate space.
      Item * newMyZeroPtr = (newMyListPtr - newLower);
      assert (newMyListPtr != 0);
      
      //create two variables that will be used for loop control purposes when copying
      //indices that are common between the original and resized bounds.  
      int lowControl;
      int upperControl;

      
      //if no bounds are common do not enter bracketed code
      if (!(myUpper < newLower && myLower > newUpper))
	{
	  //if bounds are exactly the same do not enter bracketed code
	  if (!(myUpper == newUpper && myLower == newLower))
	    {
	      //take the greatest negative bound and assign it to lowControl
	      lowControl = (myLower <= newLower ? newLower : myLower);
	      
	      //take the smallest positive bound and assign it to highControl
	      upperControl = (myUpper <= newUpper ? myUpper : newUpper);
	      
	      //the ordered pair (lowControl, highControl) will give you the
	      //common indices of the resized vector.  these two loop controls
	      //are used to copy the common indices values to the resized vector.
	      for (int i = lowControl; i <= upperControl; i++)
		{
		  newMyZeroPtr[i] = myZeroPtr[i];
		}
	    }
	}
      
      //deallocate unused space
      delete [] myListPtr;  

      //set all instance variables to the resized vectors values
      myCapacity = newCapacity;
      myUpper = newUpper;
      myLower = newLower;
      myListPtr = newMyListPtr;
      myZeroPtr = newMyZeroPtr;
      assert (myListPtr != 0);
      assert (myZeroPtr != 0);
    }
   
  
  //================================================================================= 
  // capacity of vector
  int capacity () const 
    {
      return (myCapacity);
    }


  //=================================================================================
  // returns the lower bound data member
  int lower () const
    {
      return (myLower);
    }


  //=================================================================================
  // returns the upper bound data member
  int upper () const 
    {
      return (myUpper);
    }
  
  
  //================================================================================= 
  // postcondition: all entries are equal to fillValue
  void fill (Item fillValue) 
    {
      for (int k = myLower; k <= myUpper; k++) 
	{
	  myZeroPtr[k] = fillValue;
	}
    }
  
  
  //================================================================================= 
  // safe indexing, returning reference
  // precondition: 0 <= index < myCapacity
  // postcondition: return index-th item
  // exception: aborts if index is out-of-bounds
  Item & operator [] (int index) 
    {
      checkIndex (index);
      return (myZeroPtr[index]);     
    }
  
  
  //================================================================================= 
  // const index 
  // safe indexing, returning const reference to avoid modification
  // precondition: 0 <= index < myCapacity
  // postcondition: return index-th item
  // exception: aborts if index is out-of-bounds
  const Item & operator [] (int index) const 
    {
      checkIndex (index);
      return myZeroPtr[index]; 
    }
  
  
 private:
  Item * myListPtr;    //a pointer to the array of Items
  int myCapacity;      //# of things in vector (array), 0,1,...,(myCapacity-1)
  int myUpper;         //upper bound of declared vector
  int myLower;         //lower bound of declared vector
  Item * myZeroPtr;    //a pointer to the virtual origin in the Item array
  
  
  //================================================================================= 
  // aborts with appropriate message if index is not in appropriate range
  // use std:: to access names in std namespace
  void checkIndex (int index) const 
    {
      if (index < myLower || index > myUpper) 
	{
	  std::cerr << "Illegal vector index: " << index
		    << ". (Maximum index allowed = " << myUpper 
		    << ", and Minimum index allowed = " << myLower 
		    << ".)" << std::endl;
	  assert (index >= myLower);
	  assert (index <= myUpper);
	}
    }
};

#endif                // _LBVECTOR_H not defined
