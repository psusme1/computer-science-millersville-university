#include <iostream>
#include <string>

using namespace std;

#define ENDFILE "CTRL-D"

int main()
{
   const char NWLN = '\n';	//new line character

   char next;			//next character in current line
   int charCount;		//number of characters in current line
   int totChar = 0;
   int lineCount;		//keeps track of number of lines in file
   lineCount = 0;

   cout << "Enter a line or press " << ENDFILE << ": ";
   cin.get(next);
     while (!cin.eof())
     {
        charCount = 0;
        while (next != NWLN)
        { 
          cout.put(next);		
          charCount++;		//increment char count
          cin.get(next);		//get next character
        }				// end inner loop
     
      totChar += charCount;
      cout.put(NWLN);		//mark end of current display line
      lineCount++;			//increment line count
      cout << "Number of characters in line " << lineCount << " is " << charCount << "." << endl;
      cout << "Enter a line or press " << ENDFILE << ": ";
      cin.get(next);
     } // end outter while loop

  cout << endl << endl << "Number of lines processed is " << lineCount << endl; 
  cout << endl << "Total characters printed is " << totChar << "." << endl;
  
  return 0;
}


