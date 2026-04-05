// Shawn Englerth
// count.cpp This program counts the number of spaces and lines.
// April 28th, 2003
// Lab practice

#include <iostream>
#include <ctype.h>
#include <fstream>
using namespace std;

void processfiles(ifstream&, ofstream&);

int main()
{

    ifstream ins;  // Declare ifstream variable named "ins" here...
    ofstream outs; // Declare ofstream variable named "outs" here...



    ins.open("incounts");   // Open input file "incounts" using your ifstream variable here...
      if(ins.fail())
       {
         cerr << "Could not open file infile for reading." << endl;
	 return 1;
       }


    outs.open("outcounts"); // Open output file "outcounts" using your ofstream variable here...
       if(outs.fail() )
        {
	  cerr << "Could not open file outcounts for writing." << endl;
	  return 1;
        }

    processfiles(ins, outs);

    ins.close();   // close files here...
    outs.close();

    return 0;
} // end main


/* This function writes to outs the number of digits and chars
** comming from ins.
*/
void processfiles(ifstream& ins, ofstream& outs)
{
    char inchar;
    int chars, digits;

    chars = 0;
    digits = 0;

    ins >> inchar; // Read a first character from infile into inchar variable...

    /* The logical expression in the while condition should call the function
    ** eof() to check for the end of file using the intput file stream ins
    ** check countvowels.C to see the syntax of this.
    */
    while (!ins.eof() )
    {
        if ( isalpha(inchar) )
            chars++;
        else if ( isdigit(inchar) )
            digits++;

      ins >> inchar;  // Read next char from infile into inchar variable...

    }

    cout << "Total Number of Spaces: " << spaces << "." << endl;
    cout << "Total Number of Lines: " << lines << "." << endl << endl;
     /* Output number of letters and digits so that to outs so that output will
    ** look like the following example:
    ** Letters: 16; Digits: 6
    */

}
