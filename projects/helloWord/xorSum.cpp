/*
 Organize the array taking the greater values of each MSB, and filter/update the less elements with the same MSB using the XOR operating with the greater. 
 After do it, does a XOR operation with all elements in the resulted array.
 It guarantes the uses of the MSB from the greaters values
*/

#include<iostream>
#include <cmath>

using namespace std;
 
#define MAX_BIT_POSITION 59 //To the proposed limited value, the MSB possible is the bit position 59

uint64_t fnc_uiCalculate_XorSum(uint64_t ullElementArray[], uint32_t uiArrySize);

int main()
{
    int32_t iNumberOfElements = 0;

    cin >> iNumberOfElements;
    if((iNumberOfElements<1)||(iNumberOfElements>100000)) return -1;
    uint64_t ullElements[iNumberOfElements];
    
    for(uint32_t uiElementsCounter = 0; uiElementsCounter < iNumberOfElements; ++uiElementsCounter)
    {
        int64_t llValue = 0;
        cin >> llValue;
        if((llValue<1)||(llValue>pow(10,18))) return -1;
        ullElements[uiElementsCounter] = (uint64_t)llValue;
    }

    uint64_t ullResult = fnc_uiCalculate_XorSum(ullElements, iNumberOfElements);    
    cout << ullResult<<endl;
    return 0;
}

uint64_t fnc_uiCalculate_XorSum(uint64_t ullElementArray[], uint32_t uiArrySize)
{

    int32_t iElementIndex = 0;
 
    /*Let's look for each bit, and do the operation to each element in the array that have this bit set*/
    for (int32_t iCounterBitPositon = MAX_BIT_POSITION; iCounterBitPositon >= 0; iCounterBitPositon--)
    {
        /*
            Let's look for the max value with the MSB, and try to organize the array putting the greaters values firt.
        */
        uint64_t uiGreaterElement = 0;
        uint32_t uiGreaterElementIndex = iElementIndex;
        /* To the bit position defined by the iCounterBitPositon, letÂ´s look for the greater element in the array that has this bit as MSB*/
        for (uint32_t uiCounterElement = iElementIndex; uiCounterElement < uiArrySize; uiCounterElement++)
        {
            /*
                If an element with the iCounterBitPositon set is found, check if it's greater than any other found before. 
                If yes, save its value to the uiGreaterElement and its index to uiGreaterElementIndex
            */
            if ( (ullElementArray[uiCounterElement] & (1 << iCounterBitPositon)) != 0
                     && ullElementArray[uiCounterElement] > uiGreaterElement )
                uiGreaterElement = ullElementArray[uiCounterElement], uiGreaterElementIndex = uiCounterElement;
        }
    
        //If a element was found containing the iCounterBitPosition as its MSB, save it and do the operations
        if (uiGreaterElement != 0){

            //Exchange the values between the first analized element array and the one that has the greater value with MSB being iCounterBitPositon.
            swap(ullElementArray[iElementIndex], ullElementArray[uiGreaterElementIndex]);

            //Now, the greater value with the MSB being iCounterBitPositon is saved at the iElementIndex. Ordering a new greater value in the array from the greater to the less.

            //Pass by all element arrays checking if it has the iCounterBitPositon setted and, if yes, does a XOR operation with the uiGreaterElement and save the new value    
            for (int uiCounterElement=0; uiCounterElement<uiArrySize; uiCounterElement++)
            {
                if (uiCounterElement != iElementIndex &&
                (ullElementArray[uiCounterElement] & (1 << iCounterBitPositon)) != 0)
                    ullElementArray[uiCounterElement] = ullElementArray[uiCounterElement] ^ uiGreaterElement;
            }
            //Go to the next element of array
            iElementIndex++;
        }

    }
    /*
        All the elements were organized in the array from the greater value with greater MSB to the less, and a XOR between values that have common MSB was done.
        So, now, let's do a XOR between all resulted values to find a final result.
    */
    uint64_t uiRestul = 0;
    for (int uiCounterElement=0; uiCounterElement<uiArrySize; uiCounterElement++)
        uiRestul ^= ullElementArray[uiCounterElement];
    return uiRestul;
}