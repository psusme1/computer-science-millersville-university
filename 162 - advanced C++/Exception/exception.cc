//shawn englerth
//csci 162
//dr. zoppetti
//july 03, 2003
//exception handling

#include <iostream>
#include <exception>
#include <fstream>

using namespace std;

class FileError : public exception {

public:

  FileError () {}

};  //END CLASS FileError

int 
main ()
{
  
  ifstream infile;
  ofstream outfile;

  infile.open ("file.txt");
    

  try 
    {
      if (infile.fail ())
	throw FileError ();
    }

  catch (FileError &FileError)
    {
      cout << "Exception Occurred!" << FileError.what () << endl;
    }

  cout << "good bye!" << endl;

    return 0;
}
     


