/*
Combination Formula
nCr = Number of combinations possible, without combinations repeated, independent of the order.

nCr = n!/r!(n-r)! ; n = Total Number of elemements; r = Number of elements in the groups;

*/

#include <stdio.h>


int fact(int n)
{
    if(n ==0 ) return 1;

    return fact(n-1)*n;
}


int nCr(int n, int r){

    int num, den;

    num = fact(n);
    den = fact(r) * fact(n-r);

    return num/den;
}

int main(){

    printf("Possible groups: %d\n", nCr(4,2));
    return 0;
}