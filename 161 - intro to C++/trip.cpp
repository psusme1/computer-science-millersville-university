// Trip.C
//     This program calculates the amount of time that it
//     takes to go on a trip given the speed and distance
//     (assuming a constant speed).

#include <iostream>
using namespace std;

int main()
{
  float speed, distance; // IN: the speed and the distance traveled
  float time;            // OUT: the time taken to travel the distance at speed   

    cout << "This program calculates the time of a trip\n"  ;
    cout << "Enter the speed you will be traveling (in mph)> "; 
    cin >> speed;

    cout << "Enter the distance you will be traveling (in miles)> "; 
    cin >> distance;

    time =  distance / speed ;

    cout << "To travel at " << speed << "mph for " << distance;
    cout << " miles will take you " << time << " hours.\n";
	return 0;

} // end main


