#include <iostream>
#include <stdio.h>  
#include <math.h>

using namespace std;

#define COORD_MAX     1000

typedef struct coordinate
{
    bool bUsed;
    int32_t lValue[COORD_MAX];
}tCoordinate;

typedef struct SingleCoordinate
{
    int32_t lValue_X;
    int32_t lValue_Y;
}tSingleCoordinate;

typedef struct treePotential
{
    uint32_t ulQuantity;
    uint32_t ulTime;
}tTreePotential;


static tCoordinate xCoordinates_FromX[COORD_MAX];
static tCoordinate xCoordinates_FromY[COORD_MAX];

static tTreePotential xTrees[COORD_MAX][COORD_MAX];

double Distance_TwoPoint(int32_t lX1, int32_t lY1, int32_t lX2, int32_t lY2)
{
    if((lX1>=0) && (lY1>=0) && (lX2>=0) && (lY2>=0))
    {
        double ulCat1 = (double) abs(lX1-lX2);
        double ulCat2 = (double) abs(lY1-lY2);

        if(ulCat1 == 0) return ulCat2;
        if(ulCat2 == 0) return ulCat1;

        double hypotenuse = hypot(ulCat1,ulCat2);

        return hypotenuse;
    }
    return -1;
}

int main()
{
    double dFenceSize = 0, dDistance = 0;
    tSingleCoordinate xInitialPoint;
    tSingleCoordinate xGreater_XY;
    tSingleCoordinate xGreater_YX;
    tSingleCoordinate xLessY_GreatX;

    for(uint32_t ulCounter = 0; ulCounter < COORD_MAX; ulCounter++)
    {
        xCoordinates_FromX[ulCounter].bUsed =  false;
        xCoordinates_FromY[ulCounter].bUsed =  false;
    }
    uint32_t ulTreeGreatSize = 0, ulTreeGreatTime = 0;
    uint32_t ulNumberOfTrees = 0, ulNumberOfCoordinates = 0;
    scanf("%d %d", &ulNumberOfTrees, &ulNumberOfCoordinates);
    for(uint32_t ulCounter = 0; ulCounter < ulNumberOfTrees; ulCounter++)
    {
        uint32_t ulMeters, ulTime;
        scanf("%d %d", &ulMeters, &ulTime);
        xTrees[ulMeters][ulTime].ulQuantity++;
        if(ulMeters > ulTreeGreatSize) ulTreeGreatSize = ulMeters;
        if(ulTime > ulTreeGreatTime) ulTreeGreatTime = ulTime;
    }
    for(uint32_t ulCounter = 0; ulCounter < ulNumberOfCoordinates; ulCounter++)
    {
        uint32_t ulValue_X = 0, ulValue_Y = 0;
        scanf("%d %d", &ulValue_X, &ulValue_Y);
        xCoordinates_FromX[ulValue_X].bUsed = true;
        xCoordinates_FromX[ulValue_X].lValue[ulValue_Y] = 1; 

        xCoordinates_FromY[ulValue_Y].bUsed = true; 
        xCoordinates_FromY[ulValue_Y].lValue[ulValue_X] = 1;
    }

    int32_t lX1 = -1, lY1 = -1, lX2 = -1, lY2 = -1, lInitialX = -1, lInitialY = -1;
    //Search the less x and its less y - Initial Point
    for(uint32_t ulCounter = 0; ulCounter < COORD_MAX; ulCounter++)
    {
        if(xCoordinates_FromX[ulCounter].bUsed)
        {
            for(uint32_t ulCounterY = 0; ulCounterY < COORD_MAX; ulCounterY++)
            {
                if(xCoordinates_FromX[ulCounter].lValue[ulCounterY] == 1)
                {
                    lX1 = ulCounter;
                    lY1 = ulCounterY;
                    xInitialPoint.lValue_X = ulCounter;
                    xInitialPoint.lValue_Y = ulCounterY;
                    break;
                }
            }
            break;  
        
        }
    }

    bool bFound = false;
    //Search greater X,Y
    for(uint32_t ulCounterX = (COORD_MAX-1); ulCounterX >= 0; ulCounterX--)
    {
        if(xCoordinates_FromX[ulCounterX].bUsed) //Found greater X
        {
            for(uint32_t ulCounterY = (COORD_MAX-1); ulCounterY >= 0; ulCounterY--)
            {
                if(xCoordinates_FromX[ulCounterX].lValue[ulCounterY] == 1)
                {
                    xGreater_XY.lValue_X = ulCounterX;
                    xGreater_XY.lValue_Y = ulCounterY;
                    bFound = true;
                }
                if(bFound) break;
            }            
        }
        if(bFound) break;
    }

    bFound = false;
    //Search greater  Y,X
    for(uint32_t ulCounterY = (COORD_MAX-1); ulCounterY >= 0; ulCounterY--)
    {
        if(xCoordinates_FromY[ulCounterY].bUsed) //Found greater X
        {
            for(uint32_t ulCounterX = (COORD_MAX-1); ulCounterX >= 0; ulCounterX--)
            {
                if(xCoordinates_FromY[ulCounterY].lValue[ulCounterX] == 1)
                {
                    xGreater_YX.lValue_X = ulCounterX;
                    xGreater_YX.lValue_Y = ulCounterY;
                    bFound = true;
                }
                if(bFound) break;
            }            
        }
        if(bFound) break;
    }

    //Search less Y, with greater X
    bFound = false;
    for(uint32_t ulCounterY = 0; ulCounterY <= xGreater_YX.lValue_Y; ulCounterY++)
    {
        for(uint32_t ulCounterX = xGreater_XY.lValue_X; ulCounterX >= xInitialPoint.lValue_X; ulCounterX--)
        {
            if(xCoordinates_FromY[ulCounterY].lValue[ulCounterX] == 1)
            {
                xLessY_GreatX.lValue_X = ulCounterX;
                xLessY_GreatX.lValue_Y = ulCounterY;
                bFound = true;
            }
            if(bFound) break;
        }
        if(bFound) break;
    }

    if(bFound) //Line slope is negative
    {
        lX1 = xInitialPoint.lValue_X;
        lY1 = xInitialPoint.lValue_Y;
        double dMidle = abs(((double)xInitialPoint.lValue_X - (double)xLessY_GreatX.lValue_X))/2;
        for(uint32_t ulCounterY = xLessY_GreatX.lValue_Y; ulCounterY < xInitialPoint.lValue_Y; ulCounterY++)
        {
            for(uint32_t ulCounterX = xInitialPoint.lValue_X; ulCounterX <= xLessY_GreatX.lValue_X; ulCounterX++)
            {
                if(xCoordinates_FromY[ulCounterY].lValue[ulCounterX] == 1)
                {
                    double dDistanceX = abs((int32_t)ulCounterX - xInitialPoint.lValue_X);
                    if(dDistanceX < dMidle)
                    {
                        lX2 = ulCounterX;
                        lY2 = ulCounterY;
                        dDistance = Distance_TwoPoint(lX1, lY1, lX2, lY2);
                        dFenceSize += dDistance;
                        lX1 = lX2;
                        lY1 = lY2;
                        break;
                    }
                }
            }
        }
    } 

    // Search for great X values limited by Y from greater XY
    for(uint32_t ulCounterY = lY1; ulCounterY <= xGreater_XY.lValue_Y; ulCounterY++)
    {
        for(uint32_t ulCounterX = xGreater_XY.lValue_X; ulCounterX >= lX1; ulCounterX--)
        {
            // if(ulCounterX < lX1) break;
            if((xCoordinates_FromY[ulCounterY].lValue[ulCounterX] == 1) && ((xInitialPoint.lValue_X != ulCounterX)||(xInitialPoint.lValue_Y != ulCounterY)))
            {
                lX2 = ulCounterX;
                lY2 = ulCounterY;
                dDistance = Distance_TwoPoint(lX1, lY1, lX2, lY2);
                dFenceSize += dDistance;
                lX1 = lX2;
                lY1 = lY2;
                break;
            }
        }
    }  

    if(xGreater_YX.lValue_Y > xGreater_XY.lValue_Y)
    {
        //De maior x até inicial amostrar do maior y de yx até zero vendo se y amostrado é maior que anterior
        double dMidle = abs((double)xGreater_XY.lValue_X - (double)xGreater_YX.lValue_X)/2;
        for(int32_t ulCounterX = (xGreater_XY.lValue_X-1); ulCounterX >= xGreater_YX.lValue_X; ulCounterX--)
        {
            if(xCoordinates_FromX[ulCounterX].bUsed) //Found greater X
            {
                for(int32_t ulCounterY = xGreater_YX.lValue_Y; ulCounterY >= lY1; ulCounterY--)
                {
                    // if(ulCounterY < lY1) break;
                    if(xCoordinates_FromX[ulCounterX].lValue[ulCounterY] == 1)
                    {
                        double dDistanceX = abs((int32_t)ulCounterX - xGreater_XY.lValue_X);
                        if(dDistanceX < dMidle)
                        {
                            lX2 = ulCounterX;
                            lY2 = ulCounterY;
                            dDistance = Distance_TwoPoint(lX1, lY1, lX2, lY2);
                            dFenceSize += dDistance;
                            lX1 = lX2;
                            lY1 = lY2;
                            break;
                        }
                        else if((ulCounterX == xGreater_YX.lValue_X) && (ulCounterY == xGreater_YX.lValue_Y))
                        {
                            lX2 = ulCounterX;
                            lY2 = ulCounterY;
                            dDistance = Distance_TwoPoint(lX1, lY1, lX2, lY2);
                            dFenceSize += dDistance;
                            lX1 = lX2;
                            lY1 = lY2;
                            break;
                        }
                    }
                }
            }
        }

    }
    

    uint32_t ulInicialX = lX1+1;
    for(uint32_t ulCounterX = lX1; ulCounterX >= xInitialPoint.lValue_X; ulCounterX--)
    {
        if(ulCounterX == xInitialPoint.lValue_X)
        {
            lX2 = xInitialPoint.lValue_X;
            lY2 = xInitialPoint.lValue_Y;
            dDistance = Distance_TwoPoint(lX1, lY1, lX2, lY2);
            dFenceSize += dDistance;
            break;
        }
        for(uint32_t ulCounterY = xGreater_YX.lValue_Y; ulCounterY >= xInitialPoint.lValue_Y; ulCounterY--)
        {
            if(xCoordinates_FromX[ulCounterX].lValue[ulCounterY] == 1 && ((ulCounterX != lX1)||(ulCounterY != lY1)))
            {
                double dMidle = abs((double)lX1 - (double)xInitialPoint.lValue_X)/2;
                double dDistanceX = abs((int32_t)ulCounterX - xInitialPoint.lValue_X);
                if(dDistanceX >= dMidle)
                {
                    lX2 = ulCounterX;
                    lY2 = ulCounterY;
                    dDistance = Distance_TwoPoint(lX1, lY1, lX2, lY2);
                    dFenceSize += dDistance;
                    lX1 = lX2;
                    lY1 = lY2;
                    if(ulCounterX != xInitialPoint.lValue_X)break;
                }
            }
        }
    }  

    uint32_t ulLessTime = 0xFFFFFFFF;   
    uint32_t ulLessTimeMoreOne = 0;
    uint32_t ulSizeSum = 0;
    uint32_t ulTimeSum = 0;
    uint32_t ulIndexTree1 = 0, ulIndexTree2 = 0;
    for(uint32_t ulCounterTrees = ulTreeGreatSize; ulCounterTrees > 0; ulCounterTrees--)
    { 
        for(uint32_t ulCounterTimes = 1; ulCounterTimes <= ulTreeGreatTime; ulCounterTimes++)
        {
            if(xTrees[ulCounterTrees][ulCounterTimes].ulQuantity>0)
            {
                if(ulCounterTrees >= dFenceSize)
                {
                    if(ulLessTime > xTrees[ulCounterTrees][ulCounterTimes].ulTime)
                    {
                        ulLessTime = ulCounterTimes;
                        break;
                    }                    
                }
                break;
            }
        }
    }
    for(uint32_t ulCounterTimes = 1; ulCounterTimes < ulLessTime; ulCounterTimes++)
    { 
        if((ulTimeSum + ulCounterTimes) > ulLessTime) break;
        for(uint32_t ulCounterTrees = ulTreeGreatTime; ulCounterTrees >= 1; ulCounterTrees--)
        {
            if((ulTimeSum + ulCounterTimes) > ulLessTime) break;
            if(xTrees[ulCounterTrees][ulCounterTimes].ulQuantity>0)
            {
                for(uint32_t ulQuant = 1; ulQuant<=xTrees[ulCounterTrees][ulCounterTimes].ulQuantity; ulQuant++)
                {
                    if((ulSizeSum + (ulQuant*ulCounterTrees))>= dFenceSize)
                    {
                        if((ulQuant*ulCounterTimes + ulTimeSum)< ulLessTime)
                        {
                            ulLessTime = (ulQuant*ulCounterTimes + ulTimeSum);
                            break;
                        }
                    }
                    // if((ulQuant*ulCounterTimes + ulTimeSum)< ulLessTime)
                    // {
                    //     ulLessTime = (ulQuant*ulCounterTimes + ulTimeSum);
                    //     break;
                    // }
                }
            }
        }
    }

    cout<<ulLessTime<<endl;
    return 0;
}