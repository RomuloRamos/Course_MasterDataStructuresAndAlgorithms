#include <iostream>

using namespace std;

//Scope Definition
template<class T>
class Arithmetic
{
private:
    T a;
    T b;

public:
    Arithmetic(T a, T b);
    T add();
    T sub();
};

//scope resolution
template<class T>
Arithmetic<T>::Arithmetic(T a, T b)
{
    this->a = a;
    this->b = b;
}

template<class T>
T Arithmetic<T>::add()
{
    T c;
    c = a + b;
    return c;
}

template<class T>
T Arithmetic<T>::sub()
{
    T c;
    c = a - b;
    return c;
}


int main()
{
    Arithmetic<int> ar1(50,53);
    Arithmetic<char> ar2(50,53);
    cout<<"Add1: "<<ar1.add()<<endl; //Aqui, como o tipo é int, o valor numerico será printado
    cout<<"Add2: "<<ar2.add()<<endl; //Aqui, como o tipo é char, uma letra será printada
    return 0;
}