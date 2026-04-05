// Area.c
// This program calculates the area of triangles, rectangles, and circles.

#include <iostream>
using namespace std;

const float pi = 3.14159;

int main ()
{
    int radius, height, base; // variables from which area is determined
    char choice;              // choice of shape -- NOTE: value NOT validated
    float area;               // holds calculates area

    cout << "This program calculates areas of shapes." << endl;
    cout << "Enter a T for triangle, an R for rectangle, and a C for circle> ";
    cin >> choice;

    if ((choice == 'T') || (choice == 'R'))
        { cout << "Enter the base> ";
          cin >> base;
          cout << "Enter the height> ";
          cin >> height;
        }
    else // choice == C
	{
	cout << "Enter the radius> ";
        cin >> radius;
	}

    if (choice == 'T')
        area = 1.0 / 2.0 * base * height;
    else if (choice == 'R')
        area = base * height;
    else // if (choice == 'C')
        area = pi * radius * radius;

    cout << "The area of the shape is " << area << endl;
	return 0;
}
