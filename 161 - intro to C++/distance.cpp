//   .This program calculates the distance between 2 points  -- (x1, y1)
//   and (x2, y2) given by the formula
//   distance = sqrt((x2 - x1)^2 + (y2 - y1)^2)
//
//   It also can calculate the slope of a line -- with some help


#include <iostream>
#include <cmath>
using namespace std;

float sqr (float);
float diff(float, float);

int main ()
{

    float x1, y1, x2, y2;    // the x and y coords of the 2 points
    float distance;          // distance between 2 points
    float slope;             // slope of a line that contains 2 points

    cout << "This program calculates the distance between 2 points." << endl;
    cout << "Enter the x and y coordinates for the first point> ";
    cin >> x1 >> y1;

    cout << "Enter the x and y coordinates for the next point> ";
    cin >> x2 >> y2;

    distance = sqrt(sqr(diff(x2, x1)) + sqr(diff(y2, y1)));

    slope = (y2 - y1)/(x2-x1);

    cout << "the distance between (" << x1 << ", " << y1 << ") and (";
    cout << x2 << ", " << y2 << ") is " << distance << endl;
    cout << "The slope of the line is " << slope << endl;

    return(0);
}



float sqr(float x)
{
  float squared;       // holds x squared

    squared = x * x;

    return (squared);
}


float diff(float x, float y)
{
    return(x - y);
}
