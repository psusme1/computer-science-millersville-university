//Shawn Englerth
//Csci 162
//complex.h

//prevent multiple inclusions of complex header file
#ifndef COMPLEX_H
#define COMPLEX_H

//time abstract data type definition
class Complex
{
public:
  Complex(double = 0, double = 0);

  void   setReal (double);
  void   setImaginary (double);
  double getReal ();
  double getImaginary ();
  void   addComplex (double, double);
  void   subComplex (double, double);
  void   printComplex ();

private:
  double real;       //represents real part of complex number
  double imaginary;  //represents imaginary part of complex number

}; // end class Complex

#endif
