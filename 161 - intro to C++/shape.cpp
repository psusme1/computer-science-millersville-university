//Shawn Englerth
//Shape
//shapes.cpp
//this program will draw a requested shape

#include <iostream>
#include <string>
using namespace std;

int getInt(string);     //uses a prompt to get an interger from user, returns integer.
char getChar();         //uses a prompt to get a character from user, returns char.
void drawN(int,  char); //has int n and char ch as params.  draws n ch's on same line.
void printMenu();       //prints menu of implemented commands.
void instructions();    //prints out user instructions.
void drawRect();        //draws a rectangle with user supplied data.
void drawSq();          //draws a square with user supplied data.
void drawHolBox();      //draws a hollow box with user supplied data.
void drawTri();         //draws a triangle with user supplied data.
void quitProg();        //quits program and returns to user prompt.

int main()
{
  char shape;
  
  cout << endl << endl;
  instructions();
  printMenu();
  
      
while(shape != 'q')
 {
   cout << endl << endl;
  
   cout << "Please choose a shape to draw> ";
   cin >> shape;
   cout << endl << endl;


   while(shape != 'b' && shape != 'r' && shape != 'q' && shape != 's' && shape !='t' && 
shape != '?')
      {
        cout << "Please enter a valid choice from the menu> ";
        cin >> shape;
        cout << endl << endl;
      }
 
   if(shape == 'q')
      quitProg();        
   else if(shape == 'b')
      drawHolBox();
   else if (shape == 'r')
      drawRect();
   else if (shape == 's')
      drawSq();
   else if (shape == 't')
      drawTri();
   else if (shape == '?')
      printMenu();
   else;
      
  
 }


  return 0;
 
}
//end main

void instructions()
 {
  cout << "This program will print out the shape that you would like to see." << endl;
  cout << "You will be asked to type in a lower-case letter for a" << endl;
  cout << "corresponding shape.  The program will then ask you to enter the" << endl;
  cout << "type of character you want to use to build the shape and any" << endl;
  cout << "dimensions required to build that shape." << endl << endl;
 }

void printMenu()
 {
  cout << "Choose a command." << endl;
  cout << "-----------------------------" << endl;
  cout << "B draw a hollow box" << endl;
  cout << "Q quit the program" << endl;
  cout << "R draw a rectangle" << endl;
  cout << "S draw a square" << endl;
  cout << "T draw a triangle" << endl;
  cout << "? get this Help menu" << endl;
  cout << "MAKE SURE CAPS LOCK IS TURNED OFF!!!" << endl << endl;
 }



void drawHolBox()
 {
  int height = getInt("Please enter the height of the hollow  box> ");
  int width = getInt("Please enter the width of the hollow box> ");
  char symbol = getChar();
  int hollowArea = width - 2;
  cout << endl << endl;
  
     drawN(width, symbol);
      
     cout << endl;
     
     for(int count = 3; count <= height; count ++)
       {
       cout << symbol;
       drawN(hollowArea, ' ');
       cout << symbol;
       cout << endl;
       }
     drawN(width, symbol);
  
  cout << endl << endl;
 }



void quitProg()
 {
  cout << endl << endl;
  cout << "You have quit the program.  Have a nice day!";
  cout << endl << endl;
 }



void drawRect()
 {
  int height = getInt("Enter the desired height> ");
  int width = getInt("Enter the desired width> ");
  char symbol = getChar();
  cout << endl << endl;
    
    for(int count = 1; count <= height; count ++)
       {
        drawN(width, symbol);
        cout << endl;
       }
  cout << endl << endl;
 }



void drawSq()
 {
  int side = getInt("Please enter length of square> ");
  char symbol = getChar();
  cout << endl << endl;
    for(int count = 0; count <= side; count++)
       {
        drawN(side, symbol);
        cout << endl;
       }
  cout << endl << endl;
 }



void drawTri()
 {
 int base = getInt("Please enter triangle's base length> ");
 char symbol = getChar();
 cout << endl << endl;
   for(int count = 1; count <= base; count++)
      {
       drawN(count, symbol);
       cout << endl;
      }
  cout << endl << endl;
 }




int getInt(string prompt)
{
 int value; 
 
 cout << prompt;
 cin >> value;
 
 while (value < 0)
  {
   cout << "Entry Invalid... " << prompt;
   cin >> value;
  }
 
  return value;
}



char getChar()
 {
  char symbol;

  cout << "Please choose a sybmol to build this shape> ";
  cin >> symbol;
  return symbol;
 }




void drawN(int width, char symbol)
 {
  for(int w = 1; w <= width; w++)
    cout << symbol;
 } 
  
