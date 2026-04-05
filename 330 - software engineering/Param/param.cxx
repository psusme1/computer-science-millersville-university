//Parameter assignment for CS 330 - Fall 2003
//Shawn Englerth
//November 25, 2003
//CSCI 330 
//Mrs. Katz

#include "/home/grader/katz330/labs/param/tvector.h"
#include "/home/grader/katz330/labs/param/tmatrix.h"

#include <iomanip>
#include <cmath>
#include <iostream>

 using namespace std;

//JENSEN MACRO DEFINITION
#define JENSEN(expression, index, last, answer) \
{\
   answer = 0;\
   for (index = 0; index < last; index++)\
     {\
	answer += expression;\
     }\
}

//PROTOTYPE DEFINITIONS
void read (tvector <double>& someVector); 
void read (tmatrix <double>& someMatrix);
void write (const tmatrix <double>& someMatrix);
void write (const tvector <double>& someVector);
double multiply (tvector <double>& vectorA, tvector <double>& vectorB);
tmatrix <double>& multiply (tmatrix <double>& matrixA, tmatrix <double>& matrixB);
double norm (tvector <double>& vector);


//MAIN FUNCTION BEGINS
//================================================================================
int main( )
{
  int j, k, l;
  double normVector1, normVector2, dotProduct;



  cin >> j >> k >> l; 
  
  tvector <double> vector1 (j);  //create tvectors with size of j
  tvector <double> vector2 (j);

  tmatrix <double> jkMatrix (j, k);
  tmatrix <double> klMatrix (k, l);
  tmatrix <double> matrixResult (j,l);

  //read in the two vectors by calling read function
  read (vector1);
  read (vector2);

  //read in the two matrices by calling read function
  read (jkMatrix);
  read (klMatrix);

  //calculate and print the results for the norm of of both vectors
  normVector1 = norm (vector1);
  normVector2 = norm (vector2);

  cout << endl;
  cout << "The norm of the vector1 = " ;
  cout << fixed << setprecision(2) << setw(8) << right << normVector1 <<  endl;
  cout << "The norm of the vector2 = " ;
  cout << fixed << setprecision(2) << setw(8) << right << normVector2 <<  endl;
  
  //print out vector1
  cout << "The contents of vector1 = ";
  write (vector1);
  cout << endl;
  //print out vector2
  cout << "The contents of vector2 = ";
  write (vector2);
  cout << endl;  
  
  //calculate the dot product of the two vectors and print the results
  dotProduct = multiply (vector1, vector2);
  
  cout << "The dot product of the two vectors = " << dotProduct << "." << endl;
  
  //calculate the dot product of the two matrices and print the results
  matrixResult = multiply (jkMatrix, klMatrix);
  
  cout << "The new matrix result = " << endl << endl;
  write (matrixResult);
  
  return (0);
}



//READ VECTOR FUNCTION BEGINS
//================================================================================
//fills the tvector with real number values
void read (tvector <double>& someVector)
{
  double real;
  const int uBound = someVector.size ();

  for (int i = 0; i < uBound; i++)
    {
      cin >> real;
      someVector[i] = real;
    }
}



//WRITE VECTOR FUNCTION BEGINS
//================================================================================
//prints out the contents of the tvector
void write (const tvector <double>& someVector)
{
  const int uBound = someVector.size ();
  for (int i = 0; i < uBound; i++)
    {
      cout << fixed << setprecision (2) << setw (8) << right << someVector[i];
    }
}



//READ MATRIX FUNCTION BEGINS
//================================================================================
//fills matrix with real number values
void read (tmatrix <double>& someMatrix)
{
  const int rows = someMatrix.numrows ();
  const int columns = someMatrix.numcols ();
  double input;
 
  for (int r = 0; r < rows; r++)
    {
      for (int c = 0; c < columns; c++)
	{
	  cin >> input;
	  someMatrix[r][c] = input;
	}
    }
}



//WRITE MATRIX FUNCTION BEGINS
//================================================================================
//print out the values of a matrix
void write (const tmatrix <double>& someMatrix)
{

  const int rows = someMatrix.numrows ();
  const int columns = someMatrix.numcols ();
  
 
  for (int r = 0; r < rows; r++)
    {
      for (int c = 0; c < columns; c++)
	{
	  cout << fixed << setprecision(2) << setw (8) << right << someMatrix[r][c];
	}
      cout << endl;
    }
}



//NORM FUNCTION BEGINS
//================================================================================
//calculates the norm of the vector by taking the each term, squaring them, then 
//adding up their sums and taking the squareroot of the total sum of those terms.
double norm (tvector <double>& vector)
{
  double answer;
  int index = 0;
  const int mySize = vector.size ();

  JENSEN(vector[index] * vector[index], index, mySize, answer);

  return (sqrt (answer));

}



//MULTIPLY VECTOR FUNCTION BEGINS
//================================================================================
//takes the like indices of two same size vectors and multiplies them together
double multiply (tvector <double>& vectorA, tvector <double>& vectorB)
{
  const int mySize = vectorA.size ();
  double answer;
  int index = 0;

      JENSEN(vectorA[index] * vectorB[index], index, mySize, answer);

      return (answer);
}



//MULTIPLY MATRICES FUNCTION BEGINS
//================================================================================
//indexes through the first vector rows while multiplying down the second matrices
//columns.  Matrix multiplication is performed.  Resulting matrix has size of the
//first matrices numrow by the size of second matrices numcols. 
tmatrix <double>& multiply (tmatrix <double>& matrixA, tmatrix <double>& matrixB)
{
 const int  c = matrixB.numcols (); // number of columns in matrixB
 const int  r = matrixA.numrows (); // number of rows in matrixA
 int index = 0, mySize = matrixA.numcols ();
 double answer; 
 tmatrix <double>& matrixResult = *(new tmatrix<double> (r,c));
  for (int rowCount = 0; rowCount < r; rowCount++)
    {
      for (int colCount = 0; colCount < c; colCount++)
	{
	  
	  JENSEN(matrixA[rowCount][index] * matrixB[index][colCount],index, mySize, answer);
	  matrixResult[rowCount][colCount] = answer;
	  
	}
    }

  return (matrixResult);
}
