//Author     Shawn Englerth
//Assignment Weather
//Source     weather.cpp
//Date       April 15, 2003
//this program will report information about temperatures and rainfall for given data



#include <iostream>
#include <iomanip>
using namespace std;

//----------------------------------------------------------------------------------
//PROTOTYPES
//----------------------------------------------------------------------------------
  void inputData(double, double, double&, double&, int&, double&, double&, double&);
  void outputData(double, double, double, int, int, double, double, double);

//----------------------------------------------------------------------------------
//BEGIN MAIN FUNCTION
//----------------------------------------------------------------------------------
  int main()

  {

//--------------------------
//MAIN VARIABLE DECLARATIONS
//--------------------------

    double temp;           //daily temp. recorded in deg. F at noon to nearest tenth degree.
    double rain;           //daily rainfall amount in inches to nearest tenth of an inch.
    int days = 0;          //days of data. 
    int rainDays = 0;      //number of rainy days in period.
    double maxTemp = -999; //highest recorded temp in period to nearest tenth degree.
    double minTemp = 1000; //lowest recorded temp in period to nearest tenth degree.
    double avgTemp = 0;    //average temp recorded in period to nearest tenth degree.
    double sumRain = 0;    //total rainfall for period to nearest tenth of an inch.
    double sumTemp = 0;    //total temperatures for n days.
  
//-------------------------
//INPUT DATA LOOP
//-------------------------

    while(cin >> temp && cin >> rain) //READS IN DATA FROM DATA FILE
      {
           days++;
           if(rain > 0) //RAINY DAY COUNTER
             {
               rainDays++;
             } 
           inputData(rain, temp, sumRain, sumTemp, days, avgTemp, minTemp, maxTemp);
                    //SENDS TEMP. AND RAIN DATA TO INPUTDATA FUNCTION              
      }  

//--------------------------
//OUTPUT DATA FUNCTION
//--------------------------

    if (days > 0)
     outputData(rain, temp, sumRain, rainDays, days, avgTemp, minTemp, maxTemp);
                   //SENDS DATA PROCESSED BY INPUT FUNCT. TO OUTPUTDATA FUNCTION FOR
                   //ONLY IF THERE IS ONE DAYS WORTH OF DATA.


//-----------------------------------------------------------
//EMPTY DATA FILE MESSAGE.  PRINTS OUT IF DATA FILE IS EMPTY.
//-----------------------------------------------------------

    else     
       {cout << endl << endl << endl;
        cout << "The Data File is empty!!!" << endl;
        cout << endl << endl << endl;
       }

  return 0;

} 
//----------------------------------------------------------------------------------
//END MAIN FUNCTION
//----------------------------------------------------------------------------------


//-------------------------
//START inputData FUNCTION
//-------------------------

void inputData(double rain, double temp, double& sumRain, double& sumTemp, int& days, 
double& avgTemp, double& minTemp, double& maxTemp)
 {
  sumRain += rain;
  sumTemp += temp;
  avgTemp = sumTemp / days; 
  double newTemp;

  newTemp = temp;  //INITIALIZES TEMP TO NEWTEMP FOR MIN TEMP MAX TEMP TESTS

  if(newTemp < minTemp)   //TESTS FOR MINIMUM TEMPERATURE
      { 
        minTemp = newTemp;
      }
  if(newTemp > maxTemp)   //TESTS FOR MAXIMUM TEMPERATURE
      {
        maxTemp = newTemp;
      } 
 }


//-------------------------
//START outputData FUNCTION
//-------------------------

void outputData(double rain, double temp, double sumRain, int rainDays, int days, double 
avgTemp, double minTemp, double maxTemp)
 {
    cout << endl << endl << endl;
    cout << "Days Reported = " << days  << endl;
    cout << "Min Temp = " << fixed << showpoint << setprecision(1) << minTemp << endl;
    cout << "Max Temp = " << fixed << showpoint << setprecision(1) << maxTemp << endl;
    cout << "Avg. Temp. = " << fixed << showpoint << setprecision(1) << avgTemp << endl;
    cout << "Total Rain = " << fixed << showpoint << setprecision(1) << sumRain << endl;  
    cout << "Rainy Days = " << rainDays << endl;
    cout << endl << endl << endl;
 }


//-------------------------------------------------------------------------------------
//END PROGRAM 
//-------------------------------------------------------------------------------------

