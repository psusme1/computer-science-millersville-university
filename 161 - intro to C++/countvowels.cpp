//
// countvowels.C: This program counts the number of vowels in a file, and
//                write the answer to an output file.
//

#include <iostream>
#include <ctype.h>
#include <fstream>
using namespace std;

void reportvowels(ifstream&, ofstream&);

// isvowel(): returns true if char is vowel; false otherwise.
int isvowel(char);

// initializecounts(): initializes all vowel counters to 0.
void initializecounts(int&, int&, int&, int&, int&);  

// increment(): increments one of the vowel counters.
void increment(char, int&, int&, int&, int&, int&); 

int main()
{ 

    ifstream infile;
    ofstream outfile;

    infile.open("infile");

    if (infile.fail() )
    {
        cerr << "Could not open file infile for reading." << endl;
        return 1;
    }


    outfile.open("vowelcount");

    if (infile.fail() )
    {
        cerr << "Could not open file vowelcount for writing." << endl;
        return 1;
    }

    reportvowels(infile, outfile);

    infile.close();
    outfile.close();

    return 0;

} // End main()


// This function writes out the number of each vowel in infile.
//
void reportvowels(ifstream& infile, ofstream& out)
{

    char inchar; 
    int as, es, is, os, us;

    initializecounts(as, es, is, os, us);

    infile >> inchar;
    while ( !infile.eof() )
    {
        if ( isvowel(inchar) )  {
            // A vowel detected: now increment appropriate counter.
            increment(inchar, as, es, is, os, us);
        }

        infile >> inchar;
    }

    out << "As: " << as << endl;
    out << "Es: " << es << endl;
    out << "Is: " << is << endl;
    out << "Os: " << os << endl;
    out << "Us: " << us << endl;

    return;
} // End reportvowels()


// initializecounts(): Initializes all arguments to 0.
//
void initializecounts(int &as, int &es, int &is, int &os, int &us)
{
    as = 0;
    es = 0;
    is = 0;
    os = 0;
    us = 0;
}


// isvowel(): This function returns true if ch is a vowel, false otherwise.
//
int isvowel(char ch) 
{
    ch = toupper(ch);
    return((ch=='A') || (ch == 'E') || (ch == 'I') || (ch == 'O') || (ch == 'U'));
}


// increment():  This function increments a, e, i, o, or u based on whether
//               ch is a, e, i, o, or u.  ch is assumed to be one of those.
//
void increment(char ch, int& as, int& es, int& is, int& os, int& us)
{
    ch = toupper(ch);

    switch(ch)
    {
        case 'A': 
  	    as++;
            break;

        case 'E':
	    es++;
            break;

        case 'I':
	    is++;
            break;

        case 'O': 
	    os++;
            break;

        case 'U': 
	    us++;
    }

    return;
}
