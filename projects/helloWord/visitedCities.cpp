#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

typedef struct visitedCities
{
    /* data */
    vector<string>strCitiesArray;
    uint32_t uiArrayLength;
} typeVisitedCities;


int main() {
    // Write C++ code here
    unsigned int uiNumberTests = 0;
    
    cin >> uiNumberTests;
    typeVisitedCities tVisitedCitiesArray[uiNumberTests];
    
    for(uint8_t ucCount=0; ucCount < uiNumberTests; ucCount++){
        cin>>tVisitedCitiesArray[ucCount].uiArrayLength;
        for(uint32_t uiCountWords = 0; uiCountWords < tVisitedCitiesArray[ucCount].uiArrayLength; uiCountWords++){
            string strRead;
            cin >> strRead;
            tVisitedCitiesArray[ucCount].strCitiesArray.push_back(strRead);
        }
    }

    for(uint8_t ucCount=0; ucCount < uiNumberTests; ucCount++){
        uint32_t uiRepeatedCities = 0;
        for(uint8_t uiCountWords = 0; uiCountWords < tVisitedCitiesArray[ucCount].uiArrayLength; uiCountWords++){
            uint32_t uiOcurrencies = 1;
            string strCityToCheck = tVisitedCitiesArray[ucCount].strCitiesArray[uiCountWords];
            for(uint32_t uiChecking=(uiCountWords+1); uiChecking<tVisitedCitiesArray[ucCount].uiArrayLength; uiChecking++){
                string strNextCity = tVisitedCitiesArray[ucCount].strCitiesArray[uiChecking];
                if(strCityToCheck == strNextCity){
                    uiOcurrencies++;
                }
            }
            if(uiOcurrencies>1) uiRepeatedCities++;      
        }
        cout<<(tVisitedCitiesArray[ucCount].uiArrayLength - uiRepeatedCities)<<endl;
    }

    return 0;
}
