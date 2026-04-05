// tri.cpp
// This program calculates the time needed to complete a 
// Sprint distance triathlon given the user's swim,bike,run
// pace (all in minutes per hour)

#include <iostream>
using namespace std;

const float swimlength = 0.62;      // length of swim, bike, run in miles
const float bikelength = 14.0;
const float runlength = 3.1;
const float transitiontime = 3.0;   // time for transition in minutes

float CalcLegTime (float, float);

int main()
{
    float totaltime;                    // this will hold the total time
    float swimpace, bikepace, runpace;  // paces for each leg
    float swimtime, biketime, runtime;

    // read in paces for swim, bike run here ...
    cout << "Enter the swim pace> ";
    cin  >> swimpace;
    cout << "Enter the bike pace> ";
    cin  >> bikepace;
    cout << "Enter the run pace> ";
    cin  >> runpace;

    // calculate the swim time
    swimtime = CalcLegTime(swimlength, swimpace);
    // calculate the bike time
    biketime = CalcLegTime(bikelength, bikepace);
    // calculate the run time
    runtime = CalcLegTime(runlength, runpace);

    //totaltime calculates the total time to complete the triathalon
    //at entered paces for each leg plus transition time between legs.
    totaltime = swimtime + runtime + biketime + (2 * transitiontime);

    cout << "The total time to complete the triathlon at your pace";
    cout << " is " << totaltime  << " minutes." << endl;
	return 0;

} // end main



float CalcLegTime (float x, float y)  //calculates the time to complete a leg
                                      //of the triathalon at an entered pace.
{
  return x/y;  //x variable equals length
               //y variable equals pace
}

