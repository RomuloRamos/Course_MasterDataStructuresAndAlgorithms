#include <stdio.h>
#include <stdlib.h>

struct  Element
{
    int iLine;
    int iColumn;
    int iValue;
};

struct SparseMatrix
{
    int iDimentionLines;
    int iDimentionColumns;
    int iNonZeroElementsQtt;

    struct Element *strc_ElementsArray;
    
};

void create(struct SparseMatrix *s)
{
    printf("Enter the dimentions:");
    scanf("%d%d", &s->iDimentionLines, &s->iDimentionColumns);

    printf("Enter the number of non-zero elements:");
    scanf("%d", &s->iNonZeroElementsQtt);

    s->strc_ElementsArray = (struct Element*) malloc(s->iNonZeroElementsQtt * sizeof(struct Element));

    printf("Enter the non-zero elements:");
    for(int iCounter = 0 ; iCounter < s->iNonZeroElementsQtt; iCounter++)
    {
        scanf("%d%d%d", &s->strc_ElementsArray[iCounter].iLine, &s->strc_ElementsArray[iCounter].iColumn, &s->strc_ElementsArray[iCounter].iValue);
    }
}

void display(struct SparseMatrix s)
{
    int iLine, iColumn, iElement = 0;

    for(iLine = 0; iLine < s.iDimentionLines; iLine++)
    {
        for(iColumn = 0; iColumn < s.iDimentionColumns; iColumn++)
        {
            if(iLine == s.strc_ElementsArray[iElement].iLine && iColumn == s.strc_ElementsArray[iElement].iColumn)
                printf("%d ", s.strc_ElementsArray[iElement++].iValue);
            
            else
                printf("0 ");
        }
        printf("\n");
    }
}

struct SparseMatrix * add(struct SparseMatrix *s1, struct SparseMatrix *s2)
{
    struct SparseMatrix *sum;

    sum = (struct SparseMatrix*) malloc(sizeof(struct SparseMatrix));

    sum->strc_ElementsArray  = (struct Element*) malloc(( s1->iNonZeroElementsQtt+ s2->iNonZeroElementsQtt ) * sizeof(struct Element));
    
    int iElementS1 = 0, iElementS2 = 0, iElementSum = 0;
    while ( (iElementS1 < s1->iNonZeroElementsQtt) && (iElementS2 < s2->iNonZeroElementsQtt) )
    {
        if(s1->strc_ElementsArray[iElementS1].iLine < s2->strc_ElementsArray[iElementS2].iLine)
            sum->strc_ElementsArray[iElementSum++] = s1->strc_ElementsArray[iElementS1++];
        
        else if(s1->strc_ElementsArray[iElementS1].iLine > s2->strc_ElementsArray[iElementS2].iLine)
            sum->strc_ElementsArray[iElementSum++] = s2->strc_ElementsArray[iElementS2++];
        
        else //If lines are equal... compare the columns
        {
            if(s1->strc_ElementsArray[iElementS1].iColumn < s2->strc_ElementsArray[iElementS2].iColumn)
                sum->strc_ElementsArray[iElementSum++] = s1->strc_ElementsArray[iElementS1++];
        
            else if(s1->strc_ElementsArray[iElementS1].iColumn > s2->strc_ElementsArray[iElementS2].iColumn)
                sum->strc_ElementsArray[iElementSum++] = s2->strc_ElementsArray[iElementS2++];
            
            else //If the columns are even equal... so the result is the sum!
            {
                sum->strc_ElementsArray[iElementSum] = s1->strc_ElementsArray[iElementS1];
                sum->strc_ElementsArray[iElementSum++].iValue = s1->strc_ElementsArray[iElementS1++].iValue + s2->strc_ElementsArray[iElementS2++].iValue;
            }
        }
    }
    for(; iElementS1 < s1->iNonZeroElementsQtt; iElementS1++) sum->strc_ElementsArray[iElementSum++]=s1->strc_ElementsArray[iElementS1];
    for(; iElementS2 < s2->iNonZeroElementsQtt; iElementS2++) sum->strc_ElementsArray[iElementSum++]=s2->strc_ElementsArray[iElementS2];

    sum->iDimentionLines =  s1->iDimentionLines;
    sum->iDimentionColumns = s1->iDimentionColumns;

    sum->iNonZeroElementsQtt = iElementSum;

    return sum;
}

int main()
{
    struct SparseMatrix s1, s2, *s3;

    create(&s1);
    create(&s2);
    printf("First Matrix\n");
    display(s1);
    printf("Secound Matrix:\n");
    display(s2);
    
    s3 = add(&s1, &s2);
    printf("Resulting Matrix:\n");
    display(*s3);
    return 0;
}