// Shawn Englerth
// CSCI 161.01
// May 02, 2003
// Grader.cpp
/* This program uses a grade file to input names and grades of students.
   The program outputs the average grade and lists the students and their respective
   grade along with a performance remark.
*/ 
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//------------------
//DECLARATIONS
//------------------
  //maximum size of class that can be used with program
  const int classSize = 25;
  
  //function inputs student name and student grade into an array of size classSize 
  void getGrades(string names[], int grades[], int& gradeCount);

  //function totals grades and keeps a count of grades totaled and returns avg. grade
  double avgGrades(int grades[], int gradeCount);

  //function coordinate other functions to consturct an easy to read table.
  void printTable(string names[], int grades[], int gradeCount, double);
  void printTable2(string names[], int grades[], int gradeCount, double);

  //function prints out one line of table at a time.
  void printLine(string[], int[], int, int);

  //function compares each students grade and compares to avg. grade
  void printGrade(int grades[] , double, int);

  //function prints out a catergory bar across top of table
  void titleBar();

  //finds the largest value of an array
  int findLargestIndex(int grades[], int);
  int findLargestIndex(string names[], int);

  //swaps an element of the array to another position in the array
  void swap(int&, int&);

  //function sorts scores by using findLargestIndex function and the swap function
  void sortNames(string names[], int grades[], int gradeCount, double average);

  //function sorts names by using the findLargestIndex function and the swap funct.
  void sortScores(string names[], int grades[], int gradeCount, double average);

//=================================================================================
//BEGIN MAIN FUNCTION
//=================================================================================
  int main()
  {

  string names[classSize];            //used to store student names   
  int grades[classSize], gradeCount;  //used to store each students score
  double average;                     //stores avg. of all student scores

//---------------------
//CLEAR SCREEN  
//---------------------
//loop used to clear output screen before tables are printed out  

    for(int i = 0; i < 50; i++)  //function is used to clear other commands off of output screen.
       cout << endl;
        
//-----------------------------------------------------------------------
//CALL GET GRADES, PRINT TABLE, SORT GRADES, SORT NAMES FUNCTIONS  
//-----------------------------------------------------------------------

    getGrades(names, grades, gradeCount); //detects empty data file
      if (gradeCount == 0)
         cout << "FILE IS EMPTY.... NO STUDENTS TO PROCEESS" << endl << endl << endl;
      else if (gradeCount > classSize)
         cout << "WARNING...This program cannot handle file of this size!!!" << endl;   
      else
        {
         average = avgGrades(grades, gradeCount);
         cout << endl << "Records Processed = " << gradeCount << endl;
         cout << "Grade Average = " << average << endl << endl;
         printTable(names, grades, gradeCount, average);
         sortScores(names, grades, gradeCount, average);
         cout << "Sorted by scores" << endl;
         printTable(names, grades, gradeCount, average);
         sortNames(names, grades, gradeCount, average);
         cout << "Sorted by names" << endl;
         printTable2(names, grades, gradeCount, average);
        }
    cout << endl << endl;
    return 0;
  }

//==================================================================================
//END MAIN FUNCTION
//==================================================================================


//-----------------------
//GET GRADES FUNCTION
//-----------------------
//reads in one first name and one student score per line in data file while keeping a count

  void getGrades(string names[], int grades[], int& gradeCount)
  {

    cout << endl;
    for(gradeCount = 0; gradeCount < classSize  && cin >> names[gradeCount] && cin >> 
       grades[gradeCount]; gradeCount++)
       {}
  }


//----------------------------------------------
//CALCULATE AVG. FUNCTION
//----------------------------------------------
//sums up all scores and returns an average score

  double avgGrades(int grades[], int gradeCount)
  {
   int total = 0;

   for(int i = 0; i < gradeCount; i++)
   {
     total += grades[i];
   }
   return double(total)/gradeCount;
  }


//------------------------------------------
//PRINT TABLE FUNCTION
//------------------------------------------
//prints exactly one line of an output table

  void printTable(string names[], int grades[], int gradeCount, double average)
  {
    int INDEX = gradeCount;    //INDEX used to printout array from high indices to low indices
    titleBar();                //prints out the grade reports subject title bar
    for(int i = 0; i < gradeCount; i++)
    {
     INDEX--;
     printLine(names, grades, i, INDEX);
     printGrade(grades, average, INDEX);
     cout << endl;
    }
   cout << endl;
  }

void printTable2(string names[], int grades[], int gradeCount, double average)
 {
  int INDEX = -1;
  
  titleBar();
  for(int i = 0; i < gradeCount; i++)
    {
     INDEX++;
     printLine(names, grades, i, INDEX);
     printGrade(grades, average, INDEX);
     cout << endl;
    }
   cout << endl;
 }


//-----------------------------------
//PRINT ONE LINE FUNCTION
//-----------------------------------
//prints out one name, and one grade.

  void printLine(string name[], int grade[], int count, int INDEX)
  {
    cout << setw(12) << left << count+1 << setw(12) << left << name[INDEX] << "   " << setw(5) << right << grade[INDEX];
  }


//--------------------------------------------------------------------------
//PRINT GRADE REMARK FUNCTION
//--------------------------------------------------------------------------
//compares student grade to overall average and assigns a performance remark

  void printGrade(int grades[], double avg, int INDEX)
  {
     if(grades[INDEX] < (avg - 10)) 
       cout << left << "  UNSATISFACTORY";
     else if(grades[INDEX] > (avg + 10)) 
       cout << left << "  OUTSTANDING";
     else //(grades[gradeCount] >= (avg - 10) && grades[gradeCount] <= (avg + 10))
       cout << left << "  SATISFACTORY";

  }


//--------------------------------------------------
//Table Header bar
//--------------------------------------------------
//prints out the title bar for each table displayed.

  void titleBar()
  {
     cout << "Student #   ID             SCORE  GRADE" << endl;
     cout << "-------------------------------------------------" << endl;
  }

//-----------------------------------
//SORT SCORES FUNCTION
//-----------------------------------
//sorts grades from highest to lowest

void sortScores(string names[], int grades[], int gradeCount, double average)
 { 
  int index;  //holds the INDICE'S number in the array grades containing largest value
  
  
  for(int i = gradeCount; i > 1; i--)
   {
     index = findLargestIndex(grades, i);  //finds largest value in array grades
     swap(grades[index], grades[i-1]);    //swaps largest value to end of array
     swap(names[index], names[i-1]); //performs same swap to names array to keep data paired
   }
 
 }


//---------------------------------------------------------------
//SORT NAMES FUNCTION
//---------------------------------------------------------------
//sorts names alphabetically... works similar to sortScores above

void sortNames(string names[], int grades[], int gradeCount, double avergage)
 {
  int index;
  
  for(int i = gradeCount; i > 1; i--)
   {
     index = findLargestIndex(names, i);
     swap(names[index], names[i-1]);
     swap(grades[index], grades[i-1]);
   }
 }

//---------------------------
//FIND LARGEST INDEX FUNCTION
//---------------------------
//takes grades array and and counter i(gradeCount) and finds largest index
//in array grades and returns largeIndex value.  NOTE: This value represents
//the index number w/in the array that holds the largest value!!!


int findLargestIndex(int grades[], int i)
  
 {
  int largeIndex = 0; //used to compare
  int xi;  //used as counter in for loop
  
  for(xi = 0; xi < i; xi++)
   {
    if(grades[xi] > grades[largeIndex])
     {
      largeIndex = xi;
     }
   }
   return largeIndex;
 }


//----------------------------
//FIND LARGEST INDEX FOR NAMES
//----------------------------
//does same thing as other find largest function except this one is 
//performed on the names array

int findLargestIndex(string names[], int i)
 {
  int largeIndex = 0;
  int xi;

  for(xi = 0; xi < i; xi++)
   {
    if(names[xi] > names[largeIndex])
     {
      largeIndex = xi;
     }
    }
    return largeIndex;
  }

//-------------------------
//SWAP FUNCTION
//-------------------------
//swaps the index containing the largest value with the index specified 
//by a counter.  Index specified by counter will be at the end of or bottom
//of the array being sorted.  Counter is then decremented to keep from further
//processing of the largeIndex value.  This allows the sort to work properly.
  
void swap(int& x, int& y)
 {
  int temp = 0;
  
  temp = y;
  y = x;
  x = temp;
 
 }

