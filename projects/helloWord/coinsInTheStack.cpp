/*
The 2 players need play at the same time (round), so, if the coins quantity (sum of all stacks) is odd this condition won't be done. And the answer should be directly "no".

Test cases: 

Input:          |    Input:     | Input:                  | Input:                |                                                                                                                 
    3           |        3      |     4                   |     5                 |                                                                                                                
    1 4 3       |        1 1 1  |     4 5 3 2             |     4 5 3 2 6         |                                                                                                                            
Output:  Stack: |    Output:    | Output:   Stacks:       | Output:     Stacks:   |                                                                                                                                                          
    yes  1 4 3  |        no     |    2 4        4 5 3 2   |    4 5      4 5 3 2 6 |                                                                                                                                                            
    1 2  0 3 3  |               |    1 4        4 4 3 1   |    2 4      4 5 3 1 5 |                                                                                                                                                        
    2 3  0 2 2  |               |    1 2        3 4 3 0   |    3 5      4 4 3 0 5 |                                                                                                                                                        
    2 3  0 1 1  |               |    1 2        2 3 3 0   |    1 3      4 4 2 0 4 |                                                                                                                                                            
    2 3  0 0 0  |               |    1 3        1 2 3 0   |    2 3      3 4 1 0 4 |                                                                                                                                                        
                |               |    2 3        0 2 2 0   |    1 5      3 3 0 0 4 |                                                                                           
                |               |    2 3        0 1 1 0   |    1 2      2 3 0 0 3 |                                                       
                |               |               0 0 0 0   |    1 5      1 2 0 0 3 |                                                       
                |               |                         |    2 5      0 2 0 0 2 |                                          
                |               |                         |    2 5      0 1 0 0 1 |                                                             
                |               |                         |             0 0 0 0 0 |          

* Organize the input data 
* Does the sum of all values and check if its odd or even
- Implement the loop:
    * Function to detect the nonzero smaller stack and the greater
    * Decrement 1 from each one
    * Print the stack address that were decremented. 

*/

#include <iostream>
using namespace std;

class stacksOfCoins
{
    private:
        /* data */
        uint32_t *puiStacks = NULL;
        uint32_t uiNumberOfStacks = 0;
        uint32_t uiSumOfAllValues = 0;
        uint32_t uiSmallerStack = 0;
        uint32_t uiGreaterStack = 0;

        uint32_t uifncFindTheSmallerStack(){

            uint32_t uiReturn = 0;
            for(uint32_t uiCounter = 0; uiCounter < stacksOfCoins::uiNumberOfStacks; ++uiCounter){
                if(((stacksOfCoins::puiStacks[uiReturn] > stacksOfCoins::puiStacks[uiCounter]) || (stacksOfCoins::puiStacks[uiReturn] == 0)) && (stacksOfCoins::puiStacks[uiCounter] != 0)){
                    uiReturn = uiCounter;
                }
            }
            stacksOfCoins::uiSmallerStack = uiReturn;
            return uiReturn;
        }

        uint32_t uifncFindTheGreaterStack(){

            uint32_t uiReturn = 0;
            for(uint32_t uiCounter = 0; uiCounter < stacksOfCoins::uiNumberOfStacks; ++uiCounter){
                if((stacksOfCoins::puiStacks[uiReturn] < stacksOfCoins::puiStacks[uiCounter]) && (stacksOfCoins::uiSmallerStack != uiCounter)){
                    uiReturn = uiCounter;
                }
            }

            return uiReturn;
        }

    public:
        stacksOfCoins(uint32_t uiNumberOfStacks);
        ~stacksOfCoins();
        
        bool isInputValid()
        {
            if((stacksOfCoins::uiSumOfAllValues%2 == 0) && (stacksOfCoins::uiSumOfAllValues <= 1000)) cout<<"yes"<<endl; 
            else{
                cout<<"no"<<endl;
                return false;
            }
            return true;
        }

        bool inputStackValue(){
            stacksOfCoins::uiSumOfAllValues = 0;
            int32_t iValue = 0;
            bool bResult = true;
            for(uint32_t uiStackCounter = 0; uiStackCounter < stacksOfCoins::uiNumberOfStacks; ++uiStackCounter)
            {
                cin >> iValue;
                if(iValue < 0){
                    return false;
                }
                stacksOfCoins::puiStacks[uiStackCounter] = (uint32_t)iValue;
                stacksOfCoins::uiSumOfAllValues += (uint32_t)iValue;
            }
            return bResult;
        }

        void fncPlayTheGame(){
            for(uint32_t uiCounter = 0; uiCounter < (stacksOfCoins::uiSumOfAllValues/2); uiCounter++){
                uint32_t uiSmallerStack = stacksOfCoins::uifncFindTheSmallerStack();
                uint32_t uiGreaterStack = stacksOfCoins::uifncFindTheGreaterStack();
                --stacksOfCoins::puiStacks[uiSmallerStack];
                --stacksOfCoins::puiStacks[uiGreaterStack];
                if(uiSmallerStack < uiGreaterStack){
                    cout << (uiSmallerStack+1)<<" "<<(uiGreaterStack+1)<<endl;
                }
                else{
                    cout << (uiGreaterStack+1)<<" "<<(uiSmallerStack+1)<<endl;
                }
            }
        }
};

stacksOfCoins::stacksOfCoins(uint32_t uiNumberOfStacks)
{
    size_t szArray = sizeof(uint32_t)*uiNumberOfStacks;
    stacksOfCoins::puiStacks = (uint32_t*)malloc(szArray);
    if(puiStacks){
        stacksOfCoins::uiNumberOfStacks = uiNumberOfStacks;
    }
}

stacksOfCoins::~stacksOfCoins()
{
    free(puiStacks);
}

int main() {
    // Write C++ code here
    int32_t iNumberOfStacks = 0;
    
    cin >> iNumberOfStacks;
    if((iNumberOfStacks<2)||(iNumberOfStacks>50)){
        cout<<"no"<<endl;
        return 0;
    }
    stacksOfCoins objStacksOfCoins((uint32_t)iNumberOfStacks);
    if(!objStacksOfCoins.inputStackValue()){
        cout<<"no"<<endl;
        return 0;
    }
    if(objStacksOfCoins.isInputValid()){
        objStacksOfCoins.fncPlayTheGame();
    }
    return 0;
}
