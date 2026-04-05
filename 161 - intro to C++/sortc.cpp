 //
// sortc.C:  This program sorts its 3 input characters.
//

#include <iostream>
using namespace std;

// put prototype for function sort() here:  3 char params, returns void
void sort(char&, char&, char&);
// Put prototype for function swap() here:  returns void, has
// two in-out char parameters.
void swap(char &, char &);

int main()
{

    char x, y, z;

    cout << "This program sorts its 3 input characters." << endl;
    cout << "Enter three characters> ";
    cin >> x >> y >> z;

    cout << "The unsorted characters are: " << x << " " << y << " " << z << endl;

    // Put call for function sort here, use x, y, z as the 3 params.
    sort(x, y, z);

    cout << "The   sorted characters are: " << x << " " << y << " " << z << endl;
	return 0;
}


// Put header for function sort() here.
void sort(char &x, char &y,char &z)
{

    if (x > y)
        swap(x,y);

    if (x > z)
        swap(x, z);

    if (y > z)
        swap(y,z);
}


// Put header for function swap here.
void swap(char &x, char &y)
{
    char temp;

    temp = x;
    x = y;
    y = temp;
}
