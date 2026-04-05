// This program converts inches to centimeters
#include <iostream>
using namespace std;

// put function prototype here
void writeanswer(float, float);

int main()
{
    float centimeters, inches;

    cout << "This program converts inches to centimeters" << endl;
    cout << "Enter a number> ";
    cin >> inches;

    centimeters =  inches * 2.54;

    writeanswer(inches, centimeters);
	return 0;

} // end main


//  put function header here
void writeanswer(float inches, float centimeters)

{
    cout << inches << " inches is equivalent to " << centimeters; 
    cout << " centimeters" << endl;
}
