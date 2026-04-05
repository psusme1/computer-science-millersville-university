#include <iostream>
#include "integerSet.h"
using namespace std;

int
main ()
{

  cout << endl << endl << endl;
//DEFINING ARRAYS TO BE USED IN SET1 AND SET2
//===============================================================================
  int a[] = {-1, 0, 1, 2, 3, 4, 5};          //defines an array of 7 integers
  int b[] = {95, 96, 97, 98, 99, 100, 101};  //defines an array of 7 integers 

//CREATE INTEGER SET SET1 AND INTEGER SET SET2
//===============================================================================  
  IntegerSet set1 (a, 7);   //inputs array 'a' into set1 
  IntegerSet set2 (b, 6);   //inputs array 'b' into set2

//PRINT OUT THE CONTENTS OF SET1 AND SET2 USING MEMBER FUNCTION PRINTSET ();
//================================================================================
  cout << "\nset1 = ";          
  set1.printSet ();
  cout << "\nset2 = ";
  set2.printSet ();
  cout << endl;

//INSERT ELEMENTS INTO SET1 AND PRINT OUT NEW SET1 ELEMENTS
//================================================================================
  cout << "\nInsert 5, 6, 99, and 100 into set1";
  set1.insertElement (5);
  set1.insertElement (6);
  set1.insertElement (99);
  set1.insertElement (100);
  cout << "\nset1 = ";
  set1.printSet ();
  cout << endl;

//CREATE INTEGER SET SET3 BY INTERSECTING SET1 AND SET2 WITH INTERSECTIONOFSETS ();
//CREATE INTEGER SET SET4 BY THE UNION OF SET1 AND SET2 WITH UNIONOFSETS ();
//=================================================================================
  IntegerSet set3, set4;

  set3 = set1.intersectionOfSets (set2);
  set4 = set1.unionOfSets (set2);

  cout << "\nIntergerSet set1 = ";
  set1.printSet ();
  cout << "\nIntergerSet set2 = ";
  set2.printSet ();
  cout << "\nthe intersection of set1 and set2 is set3";
  cout << "\nset3 = ";
  set3.printSet ();
  cout << "\nthe union of set1 and set2 is set4";
  cout << "\nset4 = ";
  set4.printSet ();
  cout << endl;

//DELETE ELEMENTS FROM SET4 USING deleteElement MEMBER FUNCTION
//=================================================================================
  cout << "\nDeleting 0, 100, 99, and 2 from set4";
  set4.deleteElement (0);
  set4.deleteElement (100);
  set4.deleteElement (99);
  set4.deleteElement (2);
  cout << "\nset4 = ";
  set4.printSet ();
  cout << endl;

//INSERT ELEMENTS INTO SET1 USING insertElement MEMBER FUNCTION
//=================================================================================
  cout << "\nInserting 55, 66, and 77 into set1.";
  set1.insertElement (55);
  set1.insertElement (66);
  set1.insertElement (77);
  cout << "\nnow set1 = ";
  set1.printSet ();
  cout << endl;

//INSERTING ELEMENTS INTO SET4 USING insertElement MEMBER FUNCTION
//=================================================================================
  cout << "\nInserting 55, 66, and 77 into set4.";
  set4.insertElement (55);
  set4.insertElement (66);
  set4.insertElement (77);
  cout << "\nnow set4 = ";
  set4.printSet ();
  cout << endl;

//CREATE INTEGER SET SET5 BY INTERSECTING SET1 WITH SET4
//================================================================================
  IntegerSet set5;
  
  cout << "\nCreate integer set set5 by intersecting set1 with set4.";
  cout << "\nset1 = ";
  set1.printSet ();
  cout << "\nset4 = ";
  set4.printSet ();
  cout << "\nset5 = ";
  set5 = set1.intersectionOfSets (set4);
  set5.printSet ();
  cout << endl;
 
//CREATE INTEGER ARRAYS TO BE USED FOR INPUT INTO SETS
//=================================================================================
  int c[] = {0, 1, 2, 3, 4, 5};
  int d[] = {0, 1, 2, 3, 4, 5};
  
//CREATE INTEGER SET SET6 AND INTEGER SET SET7 AND PRINT OUT
//=================================================================================
  IntegerSet set6 (c, 6);
  IntegerSet set7 (d, 6);

  cout << "\nset6 = ";
  set6.printSet ();
  cout << "\nset7 = ";
  set7.printSet ();
  cout << endl;

//DETERMINE IF SET6 IS EQUAL TO SET7 USING isEqualTo MEMBER FUNCTION
//=================================================================================
  if (set6.isEqualTo (set7))
    cout << "\nset6 is equal to set7.";
  else
    cout << "\nset6 is not equal to set7.";

//DETERMINE IF SET1 IS EQUAL TO SET7 USING isEqualTo MEMBER FUNCTION
//=================================================================================
  cout << "\nset1 = ";
  set1.printSet ();
  cout << "\nset7 = ";
  set7.printSet ();

  if (set1.isEqualTo (set7))
    cout << "\nset1 is equal to set7.";
  else
    cout << "\nset1 is not equal to set7.";
  cout << endl;

//TRY TO INSERT ELEMENTS OUTSIDE OF ALLOWABLE RANGE OF EACH SET
//=================================================================================
  cout << "\nInsert 105 into set1.";
  set1.insertElement (105);
  cout << "\nDelete 243 from set2.";
  set2.deleteElement (243);
  cout << endl;

//USING CASCADING FUNCTION CALLS INSERT AND DELETE ELEMENTS
//=================================================================================
  cout << "\nSet1 is currently = ";
  set1.printSet ();
  set1.insertElement (18).insertElement (19).deleteElement (55);
  cout << "\nSet1 after 18 through 19 have been inserted and 55 has been removed.";
  cout << "\nSet1 = ";
  set1.printSet ();
  cout << endl;

//DEFINE INTEGER ARRAYS 'e' AND 'f' TO BE USED FOR INPUT
//=================================================================================
  int e[] = {31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41};
  int f[] = {41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 31};

//CREATE INTEGER SET SET8 AND SET9 
//=================================================================================

  IntegerSet set8 (e, 11);
  IntegerSet set9 (f, 11);

//USING OPERATOR<<, COUT STATEMENTS, PRINT SET8 AND SET9
//=================================================================================

  cout << "\nset8 = " << set8 << "\nset9 = " << set9 << endl;
  
//USING THE OPERATOR+ ADD SET8 TO SET9 TO CREATE SET10
//=================================================================================
  
  IntegerSet set10;
  
  cout << "\nThe union of set8 with set9 is set10.";
  cout << "\nSet10 = ";
  set10 = set8 + set9;
  cout << set10 << endl;

//INTERSECT SET8 WITH SET9 USING MEMBER FUNCTION operator* TO CREATE SET11
//=================================================================================
  
  IntegerSet set11;
  
  cout << "\nThe intersection of set8 with set9 is set11.";
  cout << "\nSet11 = ";
  set11 = set8 * set9;
  cout << set11;
  cout << endl;
  
  cout << "==============================================================" << endl;
  cout << "        THIS CONCLUDES THE TEST OF CLASS INTEGER SET          " << endl;
  cout << "==============================================================" << endl;
  
  return (0);

}
