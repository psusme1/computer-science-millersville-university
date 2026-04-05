// evaluate.cpp
//   This program reads in a boolean expression and evaluates it.

#include <iostream>
#include <string>

using namespace std;

void ReadExpression(float&, char&, float&); // Reads in boolean expression.
bool evalt(float, char, float);             // Evaluates float char float
					    // as boolean expr.
char WriteOp(char);                         // Outputs the operator in char.
void WriteValue(bool);                      // Outputs "true" or "false".

void OutputAnswer(float, char, float);

int main() 
{
    char optr;   // holds boolean optr
    float op1, op2;  // optrs for boolean expression

    cout << "This program evaluates simple logical expressions" << endl;
    ReadExpression(op1, optr, op2);
    OutputAnswer(op1, optr, op2);
	return 0;
}


// Returns true if the expression op1 optr op2 is true, false otherwise.
//
bool evalt(float op1, char optr, float op2)
{
    if (optr == '<')
        return(op1 < op2);
    else if (optr == '>')
        return(op1 > op2);
    else if (optr == '=')    // This is short for == to get it into 1 char.
        return(op1 == op2);
} // end evalt()


// This function reads in boolean expressions, but does no validation
// it assumes that all expressions are valid, and do not use the ! optr
// and use constants for both operands.
//
void ReadExpression(float& op1, char& optr, float& op2)
{
    char firstopchar;   // First character of the "optr".

    cout << "Enter a boolean expression: ";
    cin >> op1;
    cin >> firstopchar;
    if (firstopchar == '=')
        cin >> optr;
    else
        optr = firstopchar;

    cin >> op2;

} // end ReadExpression()


// This functions returns oprtr.  if oprtr is =, = is also printed.
//
char WriteOp(char oprtr)
{
    if (oprtr == '=')
        cout << "=";

    return(oprtr);

} // end WriteOp()


// This function writes True if boolean is nonzero; False otherise.
//
void  WriteValue(bool boolean)
{
    if (boolean)
        cout << "True";
    else
        cout << "False";

} // end WriteValue()


// This function writes out the answer to
// operand(op1) operator(optr) operand(op2).
//
void OutputAnswer(float op1, char optr, float op2)
{
    cout << op1 << " ";
    cout << WriteOp(optr) << " " << op2 << " is ";
    cout << evalt(op1, optr, op2) << "(";

    WriteValue(evalt(op1, optr, op2));

    cout << ")" << endl;

} // end OutputAnswer
