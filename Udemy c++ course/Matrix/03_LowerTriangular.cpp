/*
    if M[line, column] = 0, if(line < column)

    1 0 0 0
    1 1 0 0
    1 1 1 0
    1 1 1 1
*/ 

#include <iostream>

using namespace std;

class LowerTriangular
{
private:
    int *A;
    int n;
public:
    LowerTriangular(int arraySize);
    ~LowerTriangular();

    void Set(int i, int j, int x);
    int Get(int i, int j);
    void Display();
    int GetDimention(){return n;}
};

LowerTriangular::LowerTriangular(int arraySize)
{
    this->n = arraySize;
    this->A = new int[arraySize*(arraySize+1) /2];
}

LowerTriangular::~LowerTriangular()
{
    delete []A;
}

void LowerTriangular::Set(int i, int j, int x)
{
    if(i>=j)
        this->A[i*(i-1)/2+j-1] = x;
}

int LowerTriangular::Get(int i, int j)
{
    if(i >= j)
        return this->A[i*(i-1)/2+j-1];
    return 0;
}

void LowerTriangular::Display()
{
    int i, j;
    for(i=1; i<=this->n; i++)
    {
        for(j=1; j<=this->n; j++)
        {
            if(i>=j)
            {
                cout<<this->A[i*(i-1)/2+j-1]<<" ";
            }
            else cout<<"0 ";
        }
        cout<<endl;
    }
}

int main()
{
    LowerTriangular *m;
    int n,i,j,x;

    cout<<"Enter the dimention"<<endl;
    cin>>n;
    m = new LowerTriangular(n);

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