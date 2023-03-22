#include <iostream>

using namespace std;

static uint32_t ulValuesArray[10][2];
#define SPEED           0
#define TIMEELAPSED     1


    // if((lNumberOfMeasures>=1) && ((lNumberOfMeasures<=10)))
    // {
    //     for(uint32_t ulCounter=0; ulCounter<lNumberOfMeasures; ulCounter++)
    //     {   
    //         uint32_t ulSpeed = 0, ulTimeElpsed = 0;
    //         cin>>ulSpeed>>ulTimeElpsed;
    //         if((ulSpeed>=1) && (ulSpeed<=90) && (ulTimeElpsed>=1) && (ulTimeElpsed<=12))
    //         {
    //             ulValuesArray[ulCounter][SPEED];
    //         }
    //     }
    // }

int main()
{

    int32_t     lNumberOfMeasures = 0;
    uint32_t    ulAverage = 0, ulTimeElapsed = 0, ulLastTime = 0, ulSpeed = 0;
    //while(ulNumberOfMeasures != -1)
    while(lNumberOfMeasures != -1)
    {
        cin>>lNumberOfMeasures;
        if((lNumberOfMeasures>=1) && ((lNumberOfMeasures<=10)))
        {
            ulAverage = 0, ulTimeElapsed = 0, ulLastTime = 0, ulSpeed = 0;
            for(uint32_t ulCounter=0; ulCounter<lNumberOfMeasures; ulCounter++)
            {   
                cin>>ulSpeed>>ulTimeElapsed;
                if((ulSpeed>=1) && (ulSpeed<=90) && (ulTimeElapsed>=1) && (ulTimeElapsed<=12))
                {
                    ulAverage += (ulSpeed * ( ulTimeElapsed-ulLastTime ));
                    ulLastTime = ulTimeElapsed;
                }
            }
            cout<<ulAverage<<" miles"<<endl;
        }
    }    

 }