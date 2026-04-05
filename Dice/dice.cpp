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
  int totalTimes = 0;
  int elapsed = 0;
  int totalElapsed = 0;
  int average;
  int totalRolls = 0;
  int max = 0;
  int min = 999;
  char BREAK;

  for (int i = 0; i < 1000; i++)
  {
	  dice1 = 1 + (rand () % 6);
	  dice2 = 1 + (rand () % 6);
	  

	  if (dice1 + dice2 == 7)
	  {
		elapsed = i - lastTime;
		if (elapsed > max)
			max = elapsed;
		if (elapsed < min)
			min = elapsed;

	    totalTimes++;
        cout << "On roll number " << i << ", 7 was rolled." << endl;
		cout << "The last time a 7 was rolled was on roll number " << lastTime << "." << endl;
		cout << elapsed << " hands have elapsed since the last 7." << endl << endl;
		totalElapsed += elapsed;
	    lastTime = i;
      }
	  totalRolls = i;
  }
  if (totalTimes > 0)
      average = totalRolls / totalTimes;
  cout << "\n\n\nThe average number of rolls between 7's = " << average << endl << endl;
  cout << "total rolls = " << totalRolls << endl;
  cout << "total elapsed = " << totalElapsed << "." << endl;
  cout << "MAX rolls between 7's = " << max << endl;
  cout << "MIN rolls between 7's = " << min << endl;
  cout << endl << endl;

  //cin >> BREAK;
  return (0);
}
