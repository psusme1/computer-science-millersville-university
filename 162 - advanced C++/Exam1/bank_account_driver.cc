//Shawn Englerth
//Csci 162
//Exam1
//Jun 10, 203
//driver file for BankAccount

//**************************
#include <iostream>
#include "bank_account.h"
using namespace std;
//**************************

//TEMPLATE FUNCTION EQUAL BEGINS
//======================================================================
template <class T>
T equal (T value1, T value2, T value3)
{
  return (value1 == value2 && value2 == value3);
}
//======================================================================
//TEMPLATE FUNTION EQUAL ENDS

//PROTOTYPE FOR RECURSIVE POWER FUNCTION
//======================================================================
double power (double base, double exponent = 2);
//======================================================================

//MAIN FUNCTION BEGINS
//======================================================================

int
main ()
{

//TEST CLASS BankAccount 
BankAccount c;

cout << "\nThe default balance of the bank account is> $";
cout << c.retrieveBalance ();  //$100.53
cout << "\nWe will set the balance to $162.00." << endl;
c.setBalance (162.00);  //$162.00     
cout << "\nThe new balance of the account is> $";
cout << c.retrieveBalance ();  //$162.00
cout << "\nWe will deposit $312.35 to the account!";
c.deposit (312.35);  //$474.35
cout << "\nThe new balance of the account is> $";
cout << c.retrieveBalance ();  //$474.35
cout << "\nWe will withdraw $474.35 from the account!";
c.withdraw (474.35);  //$0.00
cout << "\nThe new balance of the account is> $";
cout << c.retrieveBalance ();  //$0.00
cout << "\nWe will withdraw $0.01 from the account!";
c.withdraw (.01);  //-$0.01
cout << "\nThe new balance of the account is> $";
cout << c.retrieveBalance ();  //-$0.01
cout << "\nWe will deposit $999.35 to the account!";
c.deposit (999.35);  //$999.34
cout << "\nThe new balance of the account is> $";
cout << c.retrieveBalance ();  //$999.34

BankAccount dollar;

cout << "\nWe will retrieve the default balance of the account!";
dollar.retrieveBalance ();  //$100.53
cout << "\nThe default balance of the account is> $";
cout << dollar.retrieveBalance ();  //$100.53
cout << endl << endl;

//TEST EQUAL TEMPLATE FUNCTION WITH THREE INTS
 int int1, int2, int3;
  
 cout << "Enter 3 integers to test for equality> ";
 cin >> int1 >> int2 >> int3;
 equal (int1, int2, int3) ? cout << "TRUE" : cout << "FALSE";
 cout << endl;

//TEST EQUAL TEMPLATE FUNCTION WITH THREE CHARS
 char char1, char2, char3;

 cout << "Enter 3 characters to test for equality> ";
 cin >> char1 >> char2 >> char3;
 equal (char1, char2, char3) ? cout << "TRUE" : cout << "FALSE";
 cout << endl;

//TEST EQUAL TEMPLATE FUNCTION WITH THREE FLOATS
 float float1, float2, float3;

 cout << "Enter 3 floats to test for equality> ";
 cin >> float1 >> float2 >> float3;
 equal (float1, float2, float3) ? cout << "TRUE" : cout << "FALSE";
 cout << endl;

//TEST THE RECURSIVE POWER FUNCTION
  double b, ex;

  for (int i = 0; i < 3; i++)
    {
      cout << "Enter a Base number and an integer Exponent number> ";
      cin >> b >> ex;
      double solution = power (b, ex);
      cout << "The answer is " << solution << "." << endl << endl;
    }

  cout << "\nCalling the power function with an Integer of 8 and";
  cout << "\nno exponent specified shoule cause the exponent to";
  cout << "\ndefualt to two." << endl;
  cout << "Call power with (8, ) as it's arguments = " << power (8) << "." << endl << endl;


//TEST THE CONDITIONAL OPERATOR

  for (int j = 0; j < 3; j++)
    {
      double a;
      double b;
      double quotient;
				
      cout << "Enter a numerator > ";
      cin >> a;
      cout << "Enter a denominator > ";
      cin >> b;

      quotient = ( (b != 0) ? a/b: 0);
      cout << "The value of quotient is = ";
      cout << quotient << endl << endl;
    }

  cout << "\nThe End!!!" << endl;
 
return (0);
}
//==========================================================================
//MAIN FUNCTION ENDS

//POWER FUNCTION BEGINS
//==========================================================================

double power (double base, double exponent)
{
  //base case
    if (base == 0.0)
      return (0.0);
    else if (base == 1 || exponent == 0.0)
      return (1.0);
    else if (exponent == 1.0)
      return (base);
	
  //recursive step
    else 
      return (base * (power (base, (exponent-1))));
}
//==========================================================================
//POWER FUNCTION ENDS


