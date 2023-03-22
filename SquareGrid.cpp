#include <iostream>
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <string.h>


#define FIFO_SOLUTION   1

#if FIFO_SOLUTION
#include <unordered_set>
#include <queue>
#endif


using namespace std;

typedef struct SquareGridNode
{
#if FIFO_SOLUTION
    SquareGridNode(uint32_t ulResult, uint32_t ulCounterTogles) : ulResult(ulResult), ulCounterTogles(ulCounterTogles) {}
#else
    void*               nodeArray[9];
    void*               xFather;
    uint32_t            ulFatherIndex;
#endif
    uint32_t            ulResult;/* data */
    uint32_t            ulCounterTogles;   
}tSquareGridNode;

typedef struct SquareGridContext
{
    uint32_t *              pulTargetsArray;
    uint32_t                pulArraySize;
#if !FIFO_SOLUTION
    tSquareGridNode* xRunSquareGridNode;
#endif
}tSquareGridContext;

tSquareGridContext xContext = {
#if !FIFO_SOLUTION
                            .xRunSquareGridNode=NULL
#endif
};

#if !FIFO_SOLUTION
void SquareGrid_Init();
void SquareGrid_setArray(tSquareGridNode*    nodeArray[9]);
tSquareGridNode* SquareGrid_setNewNode(tSquareGridNode* xFather, uint32_t ulIndexInFather);
void SquareGrid_Free();
void SquareGrid_Run();
#endif
uint32_t SquareGrid_toggle(uint32_t ulGridStatus, uint32_t ulWhereTogle);


int main()
{
    uint32_t ulNumberOfProblems = 0, pulTargetsArray[2];
    cin>>ulNumberOfProblems;

    xContext.pulTargetsArray = (uint32_t*)malloc((size_t)ulNumberOfProblems*sizeof(uint32_t));
    xContext.pulArraySize = ulNumberOfProblems;
    //Loop to read the terminal and collect the problems that neet be solved
    for(uint32_t ulCounter = 0; ulCounter < ulNumberOfProblems; ulCounter++)
    {
        uint32_t ulNewTarget = 0;
        string strInput[3];
        cin>>strInput[2]>>strInput[1]>>strInput[0];
        string strConcat = strInput[2]+strInput[1]+strInput[0];
        char charArray[strConcat.length() + 1]; 
        strncpy(charArray, strConcat.c_str(),10); 
        for (int i = 0; i < 9; i++) if (charArray[i] == '*') ulNewTarget |= (1 << (8-i));
        xContext.pulTargetsArray[ulCounter] = ulNewTarget;
    }

    //Better solution, it's less complex solution, because it's using a FIFO to save the attempts, and make sure to not to do duplicated tries. Saving memory and processor 
#if FIFO_SOLUTION

    for(uint32_t ulCounter = 0; ulCounter < xContext.pulArraySize; ulCounter++)
    {
        bool bTargetFound = false;
        if (xContext.pulTargetsArray[ulCounter] == 0)
        {
            cout<<0<<endl;
            continue;
        }
        queue<SquareGridNode> queueRunSquareGridNode;
        unordered_set<uint32_t> tableKnownResults;
        queueRunSquareGridNode.push(SquareGridNode(xContext.pulTargetsArray[ulCounter], 0));
        while(!queueRunSquareGridNode.empty())
        {
            tSquareGridNode queueElement = queueRunSquareGridNode.front(); //Take the first in the FIFO
            queueRunSquareGridNode.pop(); //Remove from the FIFO
            if (tableKnownResults.find(queueElement.ulResult) != tableKnownResults.end()) continue; //If its a test already done, jump
            tableKnownResults.insert(queueElement.ulResult); //Other wise, register
            for (uint32_t ulCounterBit = 0; ulCounterBit < 9; ulCounterBit++)
            {
                uint32_t usNextResult = SquareGrid_toggle(queueElement.ulResult, ulCounterBit);
                if (usNextResult == 0) //It's a XOR logic starting from the target value, so, if it's zero, the target was reached
                {
                    cout<<(queueElement.ulCounterTogles+1)<<endl;
                    bTargetFound = true;
                    break;
                }
                if (tableKnownResults.find(usNextResult) == tableKnownResults.end()) //If it's not present in the hash table, so it's a new path and need be saved
                {
                    queueRunSquareGridNode.push(SquareGridNode(usNextResult, queueElement.ulCounterTogles+1)); 
                } 
            }
            if (bTargetFound) break;
        }
    }
//It was my first solution, it's using "binary tree", and dont check repetitve tries. It's no so good, but works.
#else
    SquareGrid_Init();
    SquareGrid_Run();
#endif
}

uint32_t SquareGrid_toggle(uint32_t ulGridStatus, uint32_t ulWhereTogle)
{
    switch (ulWhereTogle)
    {
        case 0:
            ulGridStatus ^= 1 << 0;
            ulGridStatus ^= 1 << 1;
            ulGridStatus ^= 1 << 3;
            break;

        case 1:
            ulGridStatus ^= 1 << 0;
            ulGridStatus ^= 1 << 1;
            ulGridStatus ^= 1 << 2;
            ulGridStatus ^= 1 << 4;
            break;

        case 2:
            ulGridStatus ^= 1 << 1;
            ulGridStatus ^= 1 << 2;
            ulGridStatus ^= 1 << 5;
            break;

        case 3:
            ulGridStatus ^= 1 << 0;
            ulGridStatus ^= 1 << 3;
            ulGridStatus ^= 1 << 4;
            ulGridStatus ^= 1 << 6;
            break;

        case 4:
            ulGridStatus ^= 1 << 1;
            ulGridStatus ^= 1 << 3;
            ulGridStatus ^= 1 << 4;
            ulGridStatus ^= 1 << 5;
            ulGridStatus ^= 1 << 7;
            break;

        case 5:
            ulGridStatus ^= 1 << 2;
            ulGridStatus ^= 1 << 4;
            ulGridStatus ^= 1 << 5;
            ulGridStatus ^= 1 << 8;
            break;

        case 6:
            ulGridStatus ^= 1 << 3;
            ulGridStatus ^= 1 << 6;
            ulGridStatus ^= 1 << 7;
            break;

        case 7:
            ulGridStatus ^= 1 << 4;
            ulGridStatus ^= 1 << 6;
            ulGridStatus ^= 1 << 7;
            ulGridStatus ^= 1 << 8;
            break;

        default :
            ulGridStatus ^= 1 << 5;
            ulGridStatus ^= 1 << 7;
            ulGridStatus ^= 1 << 8;
            break;
    }
    return ulGridStatus;
}


#if !FIFO_SOLUTION

tSquareGridNode* SquareGrid_setNewNode(tSquareGridNode* xFather, uint32_t ulIndexInFather)
{
    tSquareGridNode* newNode = (tSquareGridNode*)malloc(sizeof(tSquareGridNode));
    newNode->ulResult = 0;
    newNode->ulCounterTogles = 0;
    newNode->xFather = xFather;
    newNode->ulFatherIndex = ulIndexInFather;
    SquareGrid_setArray((SquareGridNode**)newNode->nodeArray);
    return newNode;
}

void SquareGrid_Run()
{
    uint32_t ulCouterTarget = 0;

    while (ulCouterTarget < xContext.pulArraySize)
    {
        tSquareGridNode* xNode = xContext.xRunSquareGridNode;
        while (xNode->nodeArray[0] != NULL)
        {
            xNode = (tSquareGridNode*)xNode->nodeArray[0];
        }
        if(xNode->xFather)
        {
            xNode = (tSquareGridNode*)xNode->xFather;
        }
        else
        {
            for(uint32_t ulCounter = 0; ulCounter < 9; ulCounter++)
            {
                tSquareGridNode* newNode = SquareGrid_setNewNode(xNode,ulCounter);
                xNode->nodeArray[ulCounter] = newNode;
                newNode->ulResult = SquareGrid_toggle(xNode->ulResult,ulCounter);
                newNode->ulCounterTogles = xNode->ulCounterTogles+1;
                newNode->ulFatherIndex = ulCounter;  

                if(newNode->ulResult == xContext.pulTargetsArray[ulCouterTarget])
                {
                    cout<<newNode->ulCounterTogles<<endl;
                    ulCouterTarget++;
                    SquareGrid_Free();
                    xNode = NULL;
                    break;               
                }
            }
            xNode = NULL; //Restart
        }
        while(xNode)
        {
            for(uint32_t ulCounterSon = 0; ulCounterSon < 9; ulCounterSon++)
            {
                tSquareGridNode* xNodeSon = (tSquareGridNode*)xNode->nodeArray[ulCounterSon];
                for(uint32_t ulCounter = 0; ulCounter < 9; ulCounter++)
                {
                    tSquareGridNode* newNode = SquareGrid_setNewNode(xNodeSon,ulCounter);
                    xNodeSon->nodeArray[ulCounter] = newNode;
                    newNode->ulResult = SquareGrid_toggle(xNodeSon->ulResult,ulCounter);
                    newNode->ulCounterTogles = xNodeSon->ulCounterTogles+1;
                    newNode->ulFatherIndex = ulCounter;  

                    if(newNode->ulResult == xContext.pulTargetsArray[ulCouterTarget])
                    {
                        cout<<newNode->ulCounterTogles<<endl;
                        ulCouterTarget++;
                        SquareGrid_Free();
                        xNode = NULL; 
                        ulCounterSon = 9;
                        ulCounter = 9;       
                    }
                }
            }
            if(xNode == NULL) break;
            uint32_t ulCurrentIndex = xNode->ulFatherIndex;
            if(ulCurrentIndex < 8)
            {
                if(xNode->xFather == NULL) xNode = NULL;
                else
                {
                    tSquareGridNode* xFather = (tSquareGridNode*)xNode->xFather;
                    xNode = (tSquareGridNode*)xFather->nodeArray[ulCurrentIndex+1];
                }
            }
            else
            {
                tSquareGridNode* xFather = NULL;
                while (ulCurrentIndex == 8)
                {
                    xFather = (tSquareGridNode*)xNode->xFather;
                    xNode = xFather;
                    ulCurrentIndex = xFather->ulFatherIndex;
                }
                if(xNode->xFather == NULL) xNode = NULL; //End, let's create a new level
                else
                {
                    xFather = (tSquareGridNode*)xNode->xFather;
                    xNode = (tSquareGridNode*)xFather->nodeArray[ulCurrentIndex+1];
                }
            }
            
        }
    }
    
}


void SquareGrid_Free()
{
    while (1)
    {
        tSquareGridNode* xNode = xContext.xRunSquareGridNode;
        while (xNode->nodeArray[0] != NULL)
        {
            xNode = (tSquareGridNode*)xNode->nodeArray[0];
        }
        if(xNode->xFather)
        {
            xNode = (tSquareGridNode*)xNode->xFather;
        }
        else
        {
            //First element...
            return;
        }
        while(xNode)
        {
        
            for(uint32_t ulCounterSon = 0; ulCounterSon < 9; ulCounterSon++)
            {
                tSquareGridNode* xNodeSon = (tSquareGridNode*)xNode->nodeArray[ulCounterSon];
                free(xNodeSon);
                xNode->nodeArray[ulCounterSon] = NULL;
            }
            uint32_t ulCurrentIndex = xNode->ulFatherIndex;
            if(ulCurrentIndex < 8)
            {
                if(xNode->xFather == NULL) xNode = NULL;
                else
                {
                    tSquareGridNode* xFather = (tSquareGridNode*)xNode->xFather;
                    xNode = (tSquareGridNode*)xFather->nodeArray[ulCurrentIndex+1];
                }
            }
            else
            {
                tSquareGridNode* xFather = NULL;
                while (ulCurrentIndex == 8)
                {
                    xFather = (tSquareGridNode*)xNode->xFather;
                    xNode = xFather;
                    ulCurrentIndex = xFather->ulFatherIndex;
                }
                if(xNode->xFather == NULL) xNode = NULL; //End, let's create a new level
                else
                {
                    xFather = (tSquareGridNode*)xNode->xFather;
                    xNode = (tSquareGridNode*)xFather->nodeArray[ulCurrentIndex+1];
                }
            }
            
        }
    }
    
}

void SquareGrid_setArray(tSquareGridNode*    nodeArray[9])
{
    for(uint32_t ulCounter = 0; ulCounter < 9; ulCounter++)
    {
        nodeArray[ulCounter] = NULL;
    }
}

void SquareGrid_Init()
{
    if(xContext.xRunSquareGridNode == NULL)
    {
        xContext.xRunSquareGridNode = SquareGrid_setNewNode(NULL,0);
    }
}
#endif


