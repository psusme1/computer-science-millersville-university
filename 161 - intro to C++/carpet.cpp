//Program:      carpet.cpp
//Author:       Shawn Englerth
//Date:         February 28, 2003
//Course:       CSCI 161 - 01
//Assignment:   Carpet

//START PROGRAM CARPET---------------------------------

#include <iostream>
using namespace std;

void instructions();  //outputs user instructions
float convert(int, int, int, int); //converts feet & inches to yards squared

//START MAIN--------------------------------------------

int main()
{

//VARIABLE DECLARATIONS---------------------------------
    int wfeet;       //room width in whole feet
    int winch;       //room width remaining in inches
    int lfeet;       //room length in whole feet
    int linch;       //room length remaining in inches
    float totsqyds;  //total square yards of room
        
//START INSTRUCTIONS TO USER----------------------------

	instructions();  //outputs user instructions

//START USER INPUTS-------------------------------------

    cout << "Enter the width of the room in whole feet> "; 
    cin  >> wfeet;
    cout << "Enter the remaining width of the room in whole inches> "; 
    cin  >> winch;
    cout << "Enter the length of the room in whole feet> ";  
    cin  >> lfeet;
    cout << "Enter the remaining length of the room in whole inches> ";  
    cin  >> linch;
    cout << endl << endl << endl;

//MAIN CALCULATION----------------------------------------
    totsqyds = convert(wfeet, winch, lfeet, linch);

//FINAL SCREEN OUTPUT------------------------------------                
    cout << "You will need " << totsqyds << " square yard(s) of carpet for the given" << 
endl; 
    cout << "dimensions." << endl;
    cout << endl;

    return 0;

} 
//END MAIN-----------------------------------------------


//FUNCTION instructions----------------------------------
void instructions()
{
  cout << endl;
  cout << endl;
  cout << "This program is designed to calculate the" << endl;
  cout << endl;
  cout << "amount of carpet needed for a rectangular shaped" << endl;
  cout << endl;
  cout << "room.  You will be asked to enter the length of" << endl;
  cout << endl;
  cout << "the room in feet and inches and the width of the" << endl;
  cout << endl;
  cout << "room in feet and inches.  The program will then" << endl;
  cout << endl;
  cout << "calculate the amount of carpet in square yards" << endl;
  cout << endl;
  cout << "needed to carpet the room." << endl;
  cout << endl << endl;  
} 

//FUNCTION convert---------------------------------------

float convert(int wf, int wi, int lf, int li)  //wf=widthfeet lf=lengthfeet
                                               //wi=widthinch li=lengthinch
{
  return(((wf+(wi/12.0))*(lf+(li/12.0)))/9.0); //converts feet and inches to square yards
} 
