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
  const int classSize = 25;
  void getGrades(string names[], int grades[], int& gradeCount);
  double avgGrades(int grades[], int gradeCount);
  void printTable(string names[], int grades[], int gradeCount, double&);
  void printLine(string[], int[], int);
  void printGrade(int grades[] , double, int);
  void titleBar();
  //void findLargest(int grades[], int);
  //void swap(int& , int&);
  //void sortNames(string names[], int grades[], int);
  //void sortScores(string names[], int grades[], int);

//---------------------
//BEGIN MAIN FUNCTION
//---------------------
  int main()
  {

  string names[classSize];    
  int grades[classSize], gradeCount;
  double average;

//---------------------
//CLEAR SCREEN 
//---------------------
    for(int i = 0; i < 50; i++)
       cout << endl;
        
//---------------------
//GET NAMES AND GRADES
//---------------------

    getGrades(names, grades, gradeCount);
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
        }
    cout << endl << endl;
    return 0;
  }

//-------------------------------------------------------------------------
//END MAIN FUNCTION
//-------------------------------------------------------------------------


//-----------------------
//GET GRADES FUNCTION
//-----------------------
  void getGrades(string names[], int grades[], int& gradeCount)
  {

    cout << endl;
    for(gradeCount = 0; gradeCount < classSize  && cin >> names[gradeCount] && cin >> 
       grades[gradeCount]; gradeCount++)
       {}
  }


//-----------------------
//CALCULATE AVG. FUNCTION
//-----------------------

  double avgGrades(int grades[], int gradeCount)
  {
   int total = 0;

   for(int i = 0; i < gradeCount; i++)
   {
     total += grades[i];
   }
   return double(total)/gradeCount;
  }


//----------------------
//PRINT TABLE FUNCTION
//----------------------

  void printTable(string names[], int grades[], int gradeCount, double& average)
  {
    
    titleBar();
    for(int i = 0; i < gradeCount; i++)
    {
     printLine(names, grades, i);
     printGrade(grades, average, i);
     cout << endl;
    }
  }


//-----------------------
//PRINT ONE LINE FUNCTION
//-----------------------

  void printLine(string name[], int grade[], int count)
  {
    cout << setw(12) << left << count+1 << setw(12) << left << name[count] << "   " << setw(5) << right << grade[count];
  }


//---------------------------
//PRINT GRADE REMARK FUNCTION
//---------------------------

  void printGrade(int grades[], double avg, int i)
  {
     if(grades[i] < (avg - 10)) 
       cout << left << "  UNSATISFACTORY";
     else if(grades[i] > (avg + 10)) 
       cout << left << "  OUTSTANDING";
     else //(grades[gradeCount] >= (avg - 10) && grades[gradeCount] <= (avg + 10))
       cout << left << "  SATISFACTORY";

  }

//-------------------------
//Table Header bar
//-------------------------

  void titleBar()
  {
     cout << "Student #   ID             SCORE  GRADE" << endl;
     cout << "-------------------------------------------------" << endl;
  }
