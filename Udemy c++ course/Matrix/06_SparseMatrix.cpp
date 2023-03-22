#include <iostream>

using namespace std;

class  Element
{
    private:

    public:
    int iLine;
    int iColumn;
    int iValue;
};

class SparseMatrix
{
    private:
    int iDimentionLines;
    int iDimentionColumns;
    int iNonZeroElementsQtt;

    Element *xElementsArray;

    public:    
    SparseMatrix(int iRows, int iColumns, int iNZElemens)
    {
        this->iDimentionLines = iRows;
        this->iDimentionColumns = iColumns;
        this->iNonZeroElementsQtt = iNZElemens;

        xElementsArray = new Element[this->iNonZeroElementsQtt];
    }

    ~SparseMatrix()
    {
        delete [] xElementsArray;
    }

    SparseMatrix operator+(SparseMatrix &s);

    friend istream & operator>>(istream &is, SparseMatrix &s);
    friend ostream & operator<<(ostream &os, SparseMatrix &s);


};

istream & operator>>(istream &is, SparseMatrix &s)
{
    cout<<"Enter the non-zero elements:"<<endl;
    for(int iCounter = 0 ; iCounter < s.iNonZeroElementsQtt; iCounter++)
    {
        cin>>s.xElementsArray[iCounter].iLine>>s.xElementsArray[iCounter].iColumn>>s.xElementsArray[iCounter].iValue;
    }

    return is;
}

ostream & operator<<(ostream &os, SparseMatrix &s)
{
    int iLine, iColumn, iElement = 0;

    for(iLine = 0; iLine < s.iDimentionLines; iLine++)
    {
        for(iColumn = 0; iColumn < s.iDimentionColumns; iColumn++)
        {
            if(iLine == s.xElementsArray[iElement].iLine && iColumn == s.xElementsArray[iElement].iColumn)
                cout<<s.xElementsArray[iElement++].iValue<<" ";
            
            else
                cout<<"0 ";
        }
        cout<<endl;
    }
    return os;
}

SparseMatrix SparseMatrix::operator+(SparseMatrix &s)
{
    int iElementS1 = 0, iElementS2 = 0, iElementSum = 0;
    if((iDimentionLines != s.iDimentionLines) || (iDimentionColumns != s.iDimentionColumns))
        return SparseMatrix(0,0,0);
    
    SparseMatrix *sum = new SparseMatrix(iDimentionLines,iDimentionColumns,(iNonZeroElementsQtt+s.iNonZeroElementsQtt));

    while ( (iElementS1 < iNonZeroElementsQtt) && (iElementS2 < s.iNonZeroElementsQtt) )
    {
        if(xElementsArray[iElementS1].iLine < s.xElementsArray[iElementS2].iLine)
            sum->xElementsArray[iElementSum++] = xElementsArray[iElementS1++];
        
        else if(xElementsArray[iElementS1].iLine > s.xElementsArray[iElementS2].iLine)
            sum->xElementsArray[iElementSum++] = s.xElementsArray[iElementS2++];
        
        else //If lines are equal... compare the columns
        {
            if(xElementsArray[iElementS1].iColumn < s.xElementsArray[iElementS2].iColumn)
                sum->xElementsArray[iElementSum++] = xElementsArray[iElementS1++];
        
            else if(xElementsArray[iElementS1].iColumn > s.xElementsArray[iElementS2].iColumn)
                sum->xElementsArray[iElementSum++] = s.xElementsArray[iElementS2++];
            
            else //If the columns are even equal... so the result is the sum!
            {
                sum->xElementsArray[iElementSum] = xElementsArray[iElementS1];
                sum->xElementsArray[iElementSum++].iValue = xElementsArray[iElementS1++].iValue + s.xElementsArray[iElementS2++].iValue;
            }
        }
    }
    for(; iElementS1 < iNonZeroElementsQtt; iElementS1++) sum->xElementsArray[iElementSum++]=xElementsArray[iElementS1];
    for(; iElementS2 < s.iNonZeroElementsQtt; iElementS2++) sum->xElementsArray[iElementSum++]=s.xElementsArray[iElementS2];

    sum->iDimentionLines =  iDimentionLines;
    sum->iDimentionColumns = iDimentionColumns;

    sum->iNonZeroElementsQtt = iElementSum;

    return *sum;

}


int main()
{
    SparseMatrix s1(5,5,5);
    SparseMatrix s2(5,5,5);

    cin>>s1;
    cin>>s2;

    cout<<"First Matrix:"<<endl;
    cout<<s1;
    cout<<"Secound Matrix:"<<endl;
    cout<<s2;

    SparseMatrix sum = s1+s2; // SparseMatrix operator+(SparseMatrix &s); Aqui a instrução quanto a como proceder com uma operação de + foi passada! :)
    cout<<"Resulting Matrix:"<<endl<<sum;

    return 0;
}