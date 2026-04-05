#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

int 
main ()
{
  srand ( time (0) );

  int dice1 = 0;
  int dice2 = 0;
  int lastTime = 0;

  for (int i = 0; i < 10000000; i++)
  {
	  dice1 = 1 + (rand () % 6);
	  dice2 = 1 + (rand () % 6);

	  if (dice1 + dice2 == 12)
	  {
        cout << "On roll number " << i << ", boxcars were rolled." << endl;
		cout << "The last time boxcars were rolled was on roll number " << lastTime << "." << endl << endl;
	  }

	  lastTime = i;
  }
  
  cout << endl << endl;
  return (0);

}
