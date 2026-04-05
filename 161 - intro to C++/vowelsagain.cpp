/*
** vowelsagain.C:  This program counts the number of vowels and spaces in a file,
**                 and reports the line where the last occurrence of each appears.
*/
#include <iostream>
#include <ctype.h>
#include <fstream>
using namespace std;

void processfiles(ifstream&, ofstream&);

// isvowel():  Returns true if char is vowel; false otherwise.
int isvowel(char);

// increment(): Increments one of the ints based on char.
void increment(char, int&, int&, int&, int&, int&, int&); 

// recordline(): Assigns linenumber to one of ints based on char.
void recordline(char, int, int&, int&, int&, int&, int&, int&); 
 
// initializecounts():  Initialize all counters to 0.
void initializecounts(int&, int&, int&, int&, int&, int&);

int main()
{

    ifstream infile;
    ofstream outfile;


    infile.open("infile.txt");

    if ( infile.fail() )
    {
        cerr << "Could not open file infile.txt for reading." << endl;
        return 1;
    }


    outfile.open("outfile.txt");

    if (infile.fail())
    {
        cerr << "Could not open file outfile.txt for writing." << endl;
        return 1;
    }

    processfiles(infile, outfile);

    infile.close();
    outfile.close();

    return 0;
} // end main()


/* This function counts the number of vowels and spaces
** and outputs it to a file with the line number of the
** last occurence of these.
*/
void processfiles(ifstream& infile, ofstream& outfile)
{

    char inchar; 
    int linecount;
    int as, es, is, os, us, spaces;

    linecount = 0;
    initializecounts(as, es, is, os, us, spaces);

    infile.get(inchar);   // NOTE: This used to be:  infile >> inchar;

    while (!infile.eof ())
    {
        linecount++;
        while ((inchar != '\n')  && (!infile.eof()))  // ** 2 eof checks **
	{
            if ( inchar == ' ' || isvowel(inchar) )
                // if vowel or space, increment appropriate counter
                increment(inchar, as, es, is, os, us, spaces);

            infile.get(inchar);    // NOTE: This used to be: infile >> inchar;
	}

        if ( !infile.eof() )
            infile.get(inchar);     // read past the \n character

    } // end outer while

    outfile << "Number of As: " << as << endl;
    outfile << "Number of Es: " << es << endl;
    outfile << "Number of Is: " << is << endl;
    outfile << "Number of Os: " << os << endl;
    outfile << "Number of Us: " << us << endl;
    outfile << "Number of Spaces: " << spaces << endl;
    outfile << "Total Number of Lines: " << linecount << endl;

} // end processvowels()


/* This function initializes all arguments to 0.
*/
void initializecounts(int &a, int &e, int &i, int &o, int &u, int &space)
{
    a = 0;
    e = 0;
    i = 0;
    o = 0;
    u = 0;
    space = 0;
}


/* This function returns true if ch is a vowel, false otherwise.
*/
int isvowel(char ch) 
{
    ch=toupper(ch);
    return( ch=='A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U');
}


/* This function increments a, e, i, o, or u based on whether
** ch is a, e, i, o, or u.  ch is assumed to be one of those.
*/
void increment(char ch, int& as, int& es, int& is, int& os, int& us, int& spaces)
{
    ch=toupper(ch);
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
            break;

        case ' ': 
	    spaces++;
    }

    return;
}


/* This function assigns linenumber to one of aline, etc based on value of ch
** ch is a, e, i, o, or u.  ch is assumed to be one of those.
*/
void recordline(char ch, int linenumber, int& aline, int& eline, 
               int& iline, int& oline, int& uline, int& spaceline)
{
    switch(ch)
    {
        case 'A': 
	    aline = linenumber;
            break;

        case 'E': 
	    eline = linenumber;
            break;

        case 'I': 
	    iline = linenumber;
            break;

        case 'O': 
	    oline = linenumber;
            break;

        case 'U': 
	    uline = linenumber;
            break;

        case ' ': 
	    spaceline = linenumber;
    }

    return;
}
