//
// min.C: This program finds the minimum of three input characters.
//

#include<iostream>
using namespace std;

// Write a function prototype for findmin():  returns a char.
// has 3 in char params
char findmin(char &, char &, char &);
int main()
{

    char x, y, z;
    char min;       // holds the min of x, y, z

    cout << "This program finds the minimum of three input characters." << endl;
    cout << "Enter three characters> ";
    cin >> x >> y >> z;

    min = findmin(x,y,z);

    cout << "The smallest of " << x << " " << y << " and " << z << " is "
         << min << endl;
	return 0;
}


// Write the function header here.
char findmin(char &x, char &y, char&z)

{
    char tempmin;

    //  This function finds the min of x, y, z
    //  by finding min of x and y, then min of that and z

    if (x < y)
        tempmin = x;
    else
        tempmin = y;

    if (tempmin < z)
        // Write a statement to return tempmin.
	return tempmin;
    else
        // Write a statement to return z.
	return z;
}



















