//Shawn Englerth
//Csci 330
//September 13, 2003
//Gift program

//This program is a basic shopping program.  The program presents
//the user with an inventory list and the user then makes menu choices.
//The user must choose from printing out the inventory list, adding an item
//to their basket, printing out the current contents of the basket, or
//printing a receipt and checking out.


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

#include "item.h"


//FUNCTION PROTOTYPES
//==========================================================================
void inputInvItem (ifstream& inventoryFile, vector <Item>& inventory);

void printProgDescription ();

void printMenu ();

void menuChoice (vector <Item>& inventory);

void printInventory (vector <Item>& inventory);

void printBasket (vector <Item>& basket);

void addItem (vector <Item>& inventory, vector <Item>& basket);

void checkOut (vector <Item>& basket);

void validateUserChoice (char& userChoice);

bool checkItemRange (int& itemNumber, vector <Item>& inventory);

void sumPrices (vector <Item>& basket);

void printHeader ();

void printVector (const vector <Item>& someVector);
//==========================================================================



//==========================================================================
//MAIN FUNCTION BEGINS======================================================
//==========================================================================
int 
main (int argc, char *argv[])
{
  vector <Item> inventory;
  
  printProgDescription ();
  
  //check to make sure command line has proper number of arguments
  if (argc != 2)
    {
      cerr << "Usage: " << argv[0] << " Command line arguments error.\n";
      //argv[0] is executable command name 
      exit (4);
    }
  
  //open invetory file for reading
  ifstream inventoryFile (argv[1]);
  
  //if open failed
  if (inventoryFile.fail ())
    {
      cerr << "Cannot open " << argv[1] << endl;
      exit (4);
    }
    
  //call function that will input inventory from file.
  inputInvItem (inventoryFile, inventory);
  
  //prints out inventory list for user at beginning of program.
  printInventory (inventory);
  
  //call function menuChoice to give user a interactive menu.
  menuChoice (inventory);
  
  //close inventory file
  inventoryFile.close ();

  return (0);
}



//==========================================================================
//BEGIN PRINT MENU FUNCTION=================================================
//this function prints out a menu for the user to make a selection from.
//==========================================================================
void
printMenu ()
{
  cout << "\n";
  cout << "*********************** MENU ************************\n";
  cout << "     PLEASE CHOOSE ONE OF THE FOLLOWING ACTIONS!\n";
  cout << "*****************************************************\n"; 
  cout << "'I' = Print Inventory\n";
  cout << "'B' = Print Basket\n";
  cout << "'A' = Add Item\n";
  cout << "'C' = Checkout and Quit\n";
}



//==========================================================================
//BEGIN MENU CHOICE FUNCTION================================================
//This functon lets the user make a selection from the printMenu's menu.    
//==========================================================================
void 
menuChoice (vector <Item>& inventory)
{
  vector <Item> basket;
  char userChoice;
  
  do
    {
      printMenu ();
      cin.clear (); //clear bad input from user if any
      
      cout << "Please choose an option!\n"; //get user's selection
      cin >> userChoice;
      userChoice = toupper (userChoice); //change choice to upper if lower
      validateUserChoice (userChoice);   //is user choice a menu option
      
      switch (userChoice)  //perform the action corresponding to user choice
	{
	case 'I':
	  printInventory (inventory);
	  break;
	  
	case 'B':
	  printBasket (basket);
	  break;
	  
	case 'A':
	  addItem (inventory, basket);
	  break;
	  
	case 'C':
	  checkOut (basket);
	  break;
	  
	case 'X':  //'X' assigned by validateUserChoice for bad input
	  break;   //case 'X' just breaks out of switch, userChoice is not "!C"
	           //so we enter the "do" again until a valid action is selected.
	} 
    }while (userChoice != 'C');  //if userChoice is 'C' we checkout and quit.
  
}



//==========================================================================
//BEGIN INPUT INVENTORY FUNCTION
//uses ifstream object "inventoryFile to input the item's "price" and the 
//the item's "descript".  It takes these two variable values and creates
//an "Item" object.  The "Item" object is entered into a vector of "Items"
//named "inventory."  All items in file are inputted until "eof" is reached.
//==========================================================================
void
inputInvItem (ifstream& inventoryFile, vector <Item>& inventory)
{
  float price;
  string descript;
  
  cout << "\n\n";
  
  while (!inventoryFile.eof ())
    { 
      inventoryFile >> price;
      inventoryFile.ignore ();
      getline (inventoryFile, descript);
      Item A (price, descript);      
      inventory.push_back (A);
    }
}



//==========================================================================
//BEGIN PRINT INVENTORY FUNCTION============================================
//this function uses a reference to the vector "inventory" and prints out 
//the inventory to the monitor.  
//==========================================================================
void
printInventory (vector <Item>& inventory)
{
  cout << "\n\n";
  
  cout << right << "                    INVENTORY LIST\n";
  printHeader ();
  
  if (!inventory.empty ()) //if "inventory" vector is not empty print it out
    {
      for (int i = 0; i < static_cast <int> (inventory.size () - 1); i++)
	{
	  cout << setw (2) << left << i << " " << inventory[i] << endl;
	} 
    }
  else
    {
      cout << "Inventory input file is empty!\n";
    }
}



//==========================================================================
//BEGIN PRINT BASKET FUNCTION===============================================
//this function uses a reference to the "basket" vector and prints out the 
//contents of the "basket".  Reports if "basket" is empty also.
//==========================================================================
void
printBasket (vector <Item>& basket)
{
  cout << "                  BASKET CONTENTS                   \n";
  printHeader ();
  
  printVector (basket);
  
  if (basket.empty ())
    {
      cout << "\nYOUR BASKET IS EMPTY\n";
    }
}



//==========================================================================
//BEGIN ADD ITEM FUNCTION===================================================
//This function references "inventory" and "basket".  The function takes a 
//user chosen "inventory" item and places it in the "basket" vector as long
//as the item number chosen is a valid item number.  If item number chosen
//is not valid, function prints invalid message.
//==========================================================================
void
addItem (vector <Item>& inventory, vector <Item>& basket)
{
  int itemNumber = -99; 
  
  printInventory (inventory);
  
  cout << "\nPLEASE ENTER ITEM NUMBER TO ADD TO YOUR BASKET.\n";
  cin >> itemNumber;
  
  if (checkItemRange (itemNumber, inventory))
    {
      basket.push_back (inventory[itemNumber]);
    }
  else
    {
      cout << "\n\n!!!ITEM NUMBER CHOSEN INVALID!!!\n\n";
      cin.clear ();  //clears failbit back to good
      cin.ignore (); //ignores the bad input
    }
}



//==========================================================================
//BEGIN CHECKOUT FUNCTION===================================================
//This function references the vector "basket" and prints out the vectors 
//contents.  Then calls sumPrices.
//==========================================================================
void
checkOut (vector <Item>& basket)
{
  cout << right << setw (45) << "THANK YOU FOR YOUR PATRONAGE!\n";
  cout << right << setw (35) << "ORDER SUMMARY\n";
  
  printHeader ();
  printVector (basket);
  sumPrices (basket);
}



//==========================================================================
//BEGIN VALIDATE USER CHOICE FUNCTION=======================================
//This function uses a reference to "userChoice" from the "menuChoice" 
//function and validates it.  The valid choices are 'A', 'B', 'C', and 'I'.
//If choice is not valid, "userChoice" is set equal to 'X' for looping
//purposes in "menuChoice" function.
//==========================================================================
void
validateUserChoice (char& userChoice)
{
  if (userChoice == 'A')
    userChoice = userChoice;
  else if (userChoice == 'B')
    userChoice = userChoice;
  else if (userChoice == 'I')
    userChoice = userChoice;
  else if (userChoice == 'C')
    userChoice = userChoice;
  else
    {
      userChoice = 'X';
      cout << ".......INVALID MENU CHOICE........\n";
      cout << "CHOOSE FROM 'A', 'B', 'I', or 'C'.\n";
    }
}



//==========================================================================
//CHECK RANGE OF ITEM NUMBER FUNCTION=======================================
//This function checks to make sure that the user selects a proper inventory
//item number in the "addItem" function.  Valid Item numbers are from zero
//to the inventory's size minus one.
//==========================================================================
bool
checkItemRange (int& itemNumber, vector <Item>& inventory)
{
  return (itemNumber >= 0 
	  && itemNumber < static_cast <int> ((inventory.size () ) - 1));
}



//==========================================================================
//SUM PRICES FUNCTION BEGINS================================================
//This function uses a reference to the "basket" vector.  It takes all the 
//"Items" in the basket and sums up their prices while counting them and 
//prints out the number of items and their total cost.
//==========================================================================
void
sumPrices (vector <Item>& basket)
{
  float total = 0;  //initialize total cost of items to zero.

  for (int i = 0; i < static_cast <int> (basket.size ()); i++)
    {
      total += basket[i].getPrice ();
    }

  cout << "\n\nTOTAL ITEMS IN BASKET: " << basket.size () << endl;
  cout << "SUBTOTAL OF BASKET $" << total << ".\n\n\n";

  if (basket.empty ())
    {
    cout << "\n NOTHING IN BASKET TO CHECKOUT WITH!!!\n\n\n";
    }
}



//===========================================================================
//PROGRAM DESCRIPTION FUNCTION BEGINS========================================
//Prints out a description of the program
//===========================================================================
void
printProgDescription ()
{
  cout << "This program is a basic shopping program.  The program presents\n";
  cout << "the user with an inventory list and the user then makes menu choices.\n";
  cout << "The user must choose from printing out the inventory list, adding an item\n";
  cout << "to their basket, printing out the current contents of the basket, or\n";
  cout << "printing a receipt and checking out.\n";
}



//===========================================================================
//PRINT HEADER FUNCTION BEGINS===============================================
//Prints out a repetitive heading to different tables of inventory
//===========================================================================
void
printHeader ()
{
  cout << "======================================================\n";
  cout << "ITEM #          ITEM DESCRIPTION\n";
  cout << "======================================================\n";
}



//===========================================================================
//PRINT VECTOR FUNCTION BEGINS============================================
//this function is used to print out either the "basket" vector or the 
//"inventory" vector. "someVector" references the vector that the 
//programmer wants to print.  
//===========================================================================
void
printVector (const vector <Item>& someVector)
{
  
  //static cast is used on "someVector.size ()" because it returns
  //an "unsigned" value type.
  
  for (int j = 0; j < static_cast <int> (someVector.size ()); j++)
    {
      cout << setw (2) << left << j << " " << someVector[j] << endl;
    } 
}
