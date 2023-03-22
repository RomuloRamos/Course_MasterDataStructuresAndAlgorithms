/*
Tower of Hanoi


*/

#include <stdio.h>

void TOH(int n, int A, int B, int C)
{
    if(n > 0)
    {
        TOH(n-1, A, C, B);
        printf("(%d, %d)\n", A, C);
        TOH(n-1, B, A, C);
    }
}

void count(int n) 
{

    static int d = 1; 

    printf("%d", n); 

    printf("%d", d); 

    d++; 

    if (n > 1) count (n-1); 

    printf("%d", d);
}

int main(){

    // TOH(3, 1, 2, 3);
    // printf("%d\n", fun(5));
    count(3);
    return 0;
}