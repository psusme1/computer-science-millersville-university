//Shawn Englerth
//Csci162
//complex.cc

#include "bank_account.h"

BankAccount::BankAccount (double money)
{
  balance = money;
}

void BankAccount::setBalance (double money)
{ 
  balance = money;
}

double BankAccount::retrieveBalance ()
{
  return (balance);
}

double BankAccount::deposit (double dep)
{
  balance += dep;
  return (balance);
}

double BankAccount::withdraw (double with)
{
  balance -= with;
  return (balance);
}

