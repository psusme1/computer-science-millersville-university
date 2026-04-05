//Shawn Englerth
//May 30, 2003
//Csci 162
//Dr. Zoppetti
//This program will create a matrix of size 22 x 22 and 
//will eventually be used to perform a wordsearch.


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

//do a wordsearch reading puzzle from puzzle file
void wordSearch (ifstream & puzzleFile);

//initializes all puzzle cells to the character '='
void initializePuzzle (char puzzle[maxSize][maxSize], int maxSize);

//fills the puzzle with characters from actual puzzle file
void fillPuzzle (ifstream & puzzleFile, char puzzle[maxSize][maxSize], int rows, int cols);

//prints out the puzzle with border to output
void printPuzzle (const char puzzle[maxSize][maxSize], int r, int c);

//checks to make sure rows and cols are greater than 1 and less than maxRowsCols
void checkRange (int rows, int cols);

//searches for possible matches in puzzle matrix
void searchForWord (const char puzzle[maxSize][maxSize], const char word[]);

//prints where a word could be found
bool foundAt (const char puzzle[maxSize][maxSize], const char word[], int, int);

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
      exit(4);
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
  initializePuzzle (puzzle, maxSize);
  fillPuzzle (puzzleFile, puzzle, rows, cols);
  printPuzzle (puzzle, rows, cols);
    
  //input words one at a time and check puzzle to see if they are found
  //word from word file that is searched for in puzzle
  string word;

  //begin inputting words and searching for them
  cout << "Words to Search For..." << endl << endl;

  while (cout << endl << "Word ? ", getline(cin, word) )
    {
      searchForWord (puzzle, word.c_str ());
    }
}

//===============================================================================
//WORD SEARCH FUNCTION ENDS


//INITIALIZATION FUNCTION BEGINS 
//===============================================================================
//initializes all blocks of the word search to the character '='

void
initializePuzzle (char puzzle[maxSize][maxSize], int maxSize)
{
  for (int i = 0; i < maxSize; i++)         //"i" = counter for "rows"
    {
      for (int j = 0; j < maxSize; j++)     //"j" = counter for "cols"
        {
          puzzle[i][j] = '=';               //sets each puzzle cell to equal sign
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

  for (int a = 0; a < r; a++)           //"r" refers to input "rows"
    {                                        //"a" = counter for rows  
      for (int b = 0; b < c; b++)       //"c" refers to input "cols"
        {                                    //"b" = counter for columns
          cout << puzzle[a+1][b+1] << " ";       //prints contents of puzzle cell
        }
      cout << endl;                          //starts new row of output
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
  
  for (int k = 0; k < r; k++)        //"r" refers to file input "rows"
    {                                //"k" = counter for rows
      for (int l = 0; l < c; l++)    //"c" refers to file input "cols"
        {                            //"l" = counter for columns
          puzzleFile >> ch;          //reads in one character from puzzle file                 
          puzzle[k+1][l+1] = ch;     //starts at first nonborder cell and sets cell 
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
  int found = 0;
  
  cout << word << endl;
  
  for (int i = 0; i < maxSize; i++)
     {
       for (int j = 0; j < maxSize; j++)
         {         
           if (foundAt(puzzle, word, i, j))
             {
               found++;  
             }
         }
     }
  
  if (found == 0)
    cout << word << " Not Found in Puzzle!!!" << endl;  
}

//===============================================================================
//SEARCH FOR WORD FUNCTION ENDS


//FOUND AT FUNCTION BEGINS
//===============================================================================
//determines whether or not a word could start at given location

bool
foundAt (const char puzzle[maxSize][maxSize], const char word[], int i, int j)
{
  if (word[0] == puzzle[i][j])
    {
      cout << word << " could start at " << i << "," << j << endl;
      return (true);
    }
  
  else 
    return (false);
}
 
//===============================================================================
//FUNCTION FOUND AT ENDS
