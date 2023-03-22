#include <iostream>

using namespace std;

class DiagonalMatrix
{
private:
    int *A;
    int n;
public:
    DiagonalMatrix()
    {
        n = 2;
        A = new int[2];
    }
    DiagonalMatrix(int n)
    {
        this->n = n;
        A = new int[n];
    }
    ~DiagonalMatrix()
    {
        delete []A;
    }
    void Set(int i, int j, int x);
    int Get(int i, int j);
    void Display();
};

void DiagonalMatrix::Set(int i, int j, int x)
{
    if(i==j)
        A[i-1]=x;
}

int DiagonalMatrix::Get(int i, int j)
{
    if(i==j)
        return A[i-1];
    return 0;
}

void DiagonalMatrix::Display()
{
    for(int i=0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if(i==j)
                cout<<A[i]<<" ";
            else
                cout<<"0 ";
        }
        cout<<endl;
    }
}

int main()
{
    DiagonalMatrix d(4);

    d.Set(1,1,5);
    d.Set(2,2,8);
    d.Set(3,3,9);
    d.Set(4,4,12);
    cout<<d.Get(2,2)<<endl;
    d.Display();
    return 0;
}