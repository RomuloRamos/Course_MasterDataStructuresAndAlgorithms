/*
    if M[line, column] = 0, if(line > column)

    1 1 1 1
    0 1 1 1
    0 0 1 1
    0 0 0 1
*/ 

#include <iostream>

using namespace std;

#define UPPERTRIANGULAR_ROW_MAJOR(LINE,COLUMN,ORDER) ( ((LINE-1)*ORDER - (LINE-2)*(LINE-1)/2) + (COLUMN-1) )  
#define UPPERTRIANGULAR_COLUMN_MAJOR(LINE,COLUMN,ORDER) ( (COLUMN*(COLUMN-1)/2) + (LINE-1) )

class UpperTriangular
{
private:
    int *A;
    int n;
public:
    UpperTriangular(int arraySize);
    ~UpperTriangular();

    void Set(int i, int j, int x);
    int Get(int i, int j);
    void Display();
    int GetDimention(){return n;}
};

UpperTriangular::UpperTriangular(int arraySize)
{
    this->n = arraySize;
    this->A = new int[arraySize*(arraySize+1) /2];
}

UpperTriangular::~UpperTriangular()
{
    delete []A;
}

void UpperTriangular::Set(int i, int j, int x)
{
    if(i<=j)
        this->A[UPPERTRIANGULAR_COLUMN_MAJOR(i,j, this->n)] = x;
}

int UpperTriangular::Get(int i, int j)
{
    if(i <= j)
        return this->A[UPPERTRIANGULAR_COLUMN_MAJOR(i,j, this->n)];
    return 0;
}

void UpperTriangular::Display()
{
    int i, j;
    for(i=1; i<=this->n; i++)
    {
        for(j=1; j<=this->n; j++)
        {
            if(i<=j)
            {
                cout<<this->A[UPPERTRIANGULAR_COLUMN_MAJOR(i,j, this->n)]<<" ";
            }
            else cout<<"0 ";
        }
        cout<<endl;
    }
}

int main()
{
    UpperTriangular *m;
    int n,i,j,x;

    cout<<"Enter the dimention"<<endl;
    cin>>n;
    m = new UpperTriangular(n);

    cout<<"Enter all elements"<<endl;

    for(i=1; i<=n; i++)
    {
            for(j=1; j<=n; j++)
            {
                cin>>x;
                m->Set(i,j,x);
            }
    }
    cout<<endl;
    m->Display();

    return 0;
}