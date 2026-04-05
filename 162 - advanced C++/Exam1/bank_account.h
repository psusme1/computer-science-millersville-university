//Shawn Englerth
//Csci 162
//BankAccount header file

//prevent multiple inclusions of BankAccount header file
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

//BankAccount abstract data type definition
class BankAccount
{
public:
  BankAccount (double = 100.53);
  void setBalance (double);
  double retrieveBalance ();
  double deposit (double);
  double withdraw (double);

private:
  double balance;
}; // end class BankAccount

#endif



