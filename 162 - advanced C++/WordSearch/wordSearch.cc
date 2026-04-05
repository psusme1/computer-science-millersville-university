//Shawn Englerth
//May 30, 2003
//Csci 162
//Dr. Zoppetti
//*********************************************************************************
//This program will create a matrix of size 22 x 22 and will read in an input file.
//The input file will contain the number of rows and columns for the matrix.  The
//file will also contain the characters used to fill the word search matrix.  The
//program then will search for each word and return the location and direction of
//each occurence of the word.
//*********************************************************************************


#include <iostream>		//for standard input and output
#include <fstream>		//for file Input/Output
#include <cstdlib>		//for exit
#include <string>

using namespace std;

//DECLARATIONS AND PROTOTYPES
//-------------------------------------------------------------------------------

//puzzle search area cannot exceed 20 rows high or 20 columns wide
const int maxRowsCols = 20;

//including border, puzzle cannot exceed maxRowsCols plus two characters high or wide
const int maxSize = (maxRowsCols + 2);

//the character that will aid in the comparison of strings 
const char borderChar = '=';

//will be used to aid in the determnination of the found words direction
const string compass[8] = {"NW","N","NE","E","SE", "S", "SW", "W"};

//do a wordsearch reading puzzle from puzzle file
void wordSearch (ifstream & puzzleFile);

//initializes all puzzle cells to the character borderChar
void initializePuzzle (char puzzle[maxSize][maxSize]);

//fills the puzzle with characters from actual puzzle file
void fillPuzzle (ifstream & puzzleFile, char puzzle[maxSize][maxSize], int rows, int cols);

//prints out the puzzle with border to output
void printPuzzle (const char puzzle[maxSize][maxSize], int r, int c);

//checks to make sure rows and cols are greater than 1 and less than maxRowsCols
void checkRange (int rows, int cols);

//searches for possible matches in puzzle matrix
void searchForWord (const char puzzle[maxSize][maxSize], const char word[]);

//determines if a word could start at current coordinates
bool foundInPuzzle (const char puzzle[maxSize][maxSize], const char word[]);

//uses row and column coordinates and determines if a word has been found
int foundAt (const char puzzle[maxSize][maxSize], const char word[], int, int);

//determines if a word has been matched in a given direction
bool wordHereThisWay (const char puzzle[maxSize][maxSize], const char word[], int u, int v, int dR, int dC);

//converts value to an integer 0 through 8 that is used with compass function
int convertToSubscript (int deltR, int deltC);

//-------------------------------------------------------------------------------



//MAIN FUNCTION BEGINS
//===============================================================================

int
main (int argc, char *argv[])
{
  if (argc != 2)
    {
      cerr << "Usage: " << argv[0] << " puzzleFileName." << endl;
      //argv[0] is command name
      exit (4);
    }

  //open puzzle file for reading
  ifstream puzzleFile (argv[1]);

  //was open successful
  if (puzzleFile.fail ())
    {
      cerr << "Cannot open " << argv[1] << endl;
      exit (4);
    }

  //clears outputs screen for readability
  for (int i = 0; i < 35; i++)
    cout << endl;

  //begin wordsearch
  wordSearch (puzzleFile);

  puzzleFile.close ();

  cout << "\nExecution complete!" << endl;
  return (0);
}

//===============================================================================
//MAIN FUNCTION ENDS


//WORD SEARCH FUNCTION BEGINS
//===============================================================================
//do a word search reading puzzle from puzzleFile

void
wordSearch (ifstream & puzzleFile)
{
  int rows;  //variable for rows in wordsearch puzzle
  int cols;  //variable for columns in wordsearch puzzle

  puzzleFile >> rows;  //inputs number of rows in puzzle from file
  puzzleFile >> cols;  //inputs number of cols in puzzle from file

  //check row/col input for range validity
  checkRange (rows, cols);

  //defines a character puzzle grid with width and height of maxSize
  char puzzle[maxSize][maxSize];

  //begin initilizating, filling, and printing of wordsearch puzzle
  initializePuzzle (puzzle);
  fillPuzzle (puzzleFile, puzzle, rows, cols);
  printPuzzle (puzzle, rows, cols);

  //input words one at a time and check puzzle to see if they are found
  string word;  //word from word file that is searched for in puzzle

  //begin inputting words and searching for them
  cout << "Words to Search For..." << endl << endl;

  while (getline (cin, word))
    {
      cout << "Word ? ";      
      searchForWord (puzzle, word.c_str ());
    }
}

//===============================================================================
//WORD SEARCH FUNCTION ENDS


//INITIALIZATION FUNCTION BEGINS
//===============================================================================
//initializes all blocks of the word search to the character '='

void
initializePuzzle (char puzzle[maxSize][maxSize])
{
  for (int i = 0; i < maxSize; i++)         //"i" = counter for "rows"
    {
      for (int j = 0; j < maxSize; j++)     //"j" = counter for "cols"
        {
          puzzle[i][j] = borderChar;        //sets each puzzle cell to equal sign
        }
    }
}

//===============================================================================
//INITIALIZATION FUNCTION ENDS


//PRINT PUZZLE FUNCTION BEGINS
//===============================================================================
//prints the puzzle to standard output

void
printPuzzle (const char puzzle[maxSize][maxSize], int r, int c)
{
  cout << "The Word Search Puzzle Looks Like This..." << endl << endl;

  for (int a = 1; a <= r; a++)                 //"r" refers to input "rows"
    {                                          //"a" = counter for rows
      for (int b = 1; b <= c; b++)             //"c" refers to input "cols"
        {                                      //"b" = counter for columns
          cout << puzzle[a][b] << " ";         //prints contents of puzzle cell
        }
      cout << endl;                            //starts new row of output
    }
  
  cout << endl << endl;

}

//===============================================================================
//PRINT PUZZLE FUNCTION ENDS


//FILL PUZZLE FUNCTION BEGINS
//===============================================================================
//fills the puzzle with characters from the puzzle file

void
fillPuzzle (ifstream & puzzleFile, char puzzle[maxSize][maxSize], int r, int c)
{
  char ch;                           //"ch" = input character from puzzle file
  
  for (int k = 1; k <= r; k++)       //"r" refers to file input "rows"
    {                                //"k" = counter for rows
      for (int l = 1; l <= c; l++)   //"c" refers to file input "cols"
        {                            //"l" = counter for columns
          puzzleFile >> ch;          //reads in one character from puzzle file
          puzzle[k][l] = ch;         //starts at first nonborder cell and sets cell 
        }                            //equal to ch's value
    }
}

//===============================================================================
// FILL PUZZLE FUNCTION ENDS


//RANGE CHECK FOR ROWS/COLS BEGINS
//===============================================================================
//function checks that row and col are > 1 and < maxRowsCols

void
checkRange (int rows, int cols)
{

  if (rows > 20 || rows < 1)
    {
      cerr << "\nRow size, " << rows << ", is out of Range. Must be 1 to " << maxRowsCols << "." << endl;
      exit (4);
    }

  if (cols > 20 || cols < 1)
    {
      cerr << "\nColumn size, " << cols << ", is out of Range. Must be 1 to " << maxRowsCols << "." << endl;
      exit (4);
    }
}

//===============================================================================
//RANGE CHECK FOR ROW/COL ENDS


//SEARCH FOR WORD FUNCTION BEGINS
//===============================================================================

void
searchForWord (const char puzzle[maxSize][maxSize], const char word[])
{
  cout << word << endl;
  if (!foundInPuzzle (puzzle, word))
    {
      cout <<  word << " Not Found in Puzzle!" << endl;
    }

}

//===============================================================================
//SEARCH FOR WORD FUNCTION ENDS


//FOUND IN PUZZLE FUNCTION BEGINS
//===============================================================================
//determines whether or not a word could start at given location

bool
foundInPuzzle (const char puzzle[maxSize][maxSize], const char word[])
{
  int timesFound = 0;

  for (int m = 1; puzzle[m][1] != borderChar; m++)
    {
      for (int n = 1; puzzle[m][n] != borderChar; n++)
        {
          if (foundAt (puzzle, word, m, n) != 0)  
            timesFound++;                          //if a word is found when foundAt
        }                                          //returns, then we increment
    }                                              //timesFound.  it does not matter  
                                                   //what the final value of timesFound
  if (timesFound > 0)                              //turns out to be, as long as it is  
    return (true);                                 //either 0 or greater than 1.
  else
    return (false);

}

//===============================================================================
//FOUND IN PUZZLE FUNCTION ENDS


//FOUND AT FUNCTION BEGINS
//===============================================================================
//takes a row and column coordinate and determines if a word has been found

int
foundAt (const char puzzle[maxSize][maxSize], const char word[], int p, int q)
{
  int numWordsFound = 0;

  if (word[0] == puzzle[p][q])
    {
      for (int deltaR = -1; deltaR <= 1; deltaR++)
        {
          for (int deltaC = -1; deltaC <= 1; deltaC++)
            {
              if (deltaR == 0 && deltaC == 0)
                continue;
              else if (wordHereThisWay (puzzle, word, p, q, deltaR, deltaC))
                  {
                    int subscript = convertToSubscript (deltaR, deltaC);
                    cout << word << " found at " << p << "," << q << " in direction " << compass[subscript] << "." << endl;
                    numWordsFound++;
                  }
            }
        }
    }
  
  return (numWordsFound);
}

//===============================================================================
//FOUND AT FUNCTION ENDS


//WORD HERE THIS WAY BEGINS
//===============================================================================
//checks to see if word is found in puzzle

bool
wordHereThisWay (const char puzzle[maxSize][maxSize], const char word[], int u, int v, int dR, int dC)
{

int i;

  for (i = 0; (word[i] != '\0') && (word[i] == puzzle[u][v]); i++)
    {
      u += dR;            //this code is used to continually compare the next character
      v += dC;            //in a supplied direction.  dR represents the change in row
    }                     //increment and dC represents the change in column increment

  if (word[i] == '\0')    //if the word matched in the puzzle, the first character that 
    {                     //would not have matched would have been the NULL character.
      return (true);      //Therefor, words[i] should equal the NULL character.  
    }

  else                    //If the word[i] value is not the NULL character
    return (false);
    
}

//===============================================================================
//WORD HERE THIS WAY FUNCTION ENDS


//CONVERT TO SUBSCRIPT BEGINS HERE
//===============================================================================
//takes two integers representing a direction and returns one integer to be used
//to retrieve a string direction from array compass.

int 
convertToSubscript (int deltR, int deltC)
{
  if (deltR == 1)
    { 
      if (deltC == -1)
        return (6);          //6 = SouthWest (1,-1)
      else if (deltC == 0)
        return (5);          //5 = South (1, 0)
      else
        return (4);          //4 = SouthEast (1, 1)
    }

  if (deltR == 0)
    {
      if (deltC == -1)         
        return (7);          //7 = West (0, -1)
      else                   
        return (3);          //3 = East (0, 1)
    }
  
  if (deltC == -1)
    return (0);              //0 = NorthWest (-1, -1)
  else if (deltC == 0)
    return (1);              //1 = North (-1, 0)
  else
    return (2);              //2 = NorthEast (-1, 1) 

}

//===============================================================================
//CONVERT TO SUBSCRIPT ENDS
