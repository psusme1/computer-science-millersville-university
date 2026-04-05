//
//  swap.C: This program swaps its two input values.
//

#include <iostream>
using namespace std;

// Put function prototype for swap() here, swap() has 2
// int params and returns a void.
void swap(int&, int&);

int main()
{
    int x, y;

    cout << "This program swaps its two input values" << endl;
    cout << "Input two values> ";
    cin >> x >> y;

    cout << "The initial values are " << x << " and " << y << endl;

    // Put function call here.  use x and y as the 2 paramters.
    swap(x, y);

    cout << "The swapped values are " << x << " and " << y << endl;
	return 0;
}


// Put function header for swap() here.
void swap(int &x, int &y)
{
    int temp;

    temp = x;
    x = y;
    y = temp;
}
