/*
    fib(n) =    0   1   1   2   3   5   8   13  ...
        n  =    0   1   2   3   4   5   6   7     

*/


#include <stdio.h>

int fib(int n){

    int t0= 0, t1 =1, s=0, i;

    if(n<=1) return n;

    for(i=2; i<=n; i++){
        s= t0+t1;
        t0=t1;
        t1 = s;
    }

    return s;
}

int F[10];
int mfib(int n) {

    if(n<=1){
        F[n]=n;
        return n;
    }
    else{
        if(F[n-2]==-1) F[n-2] = mfib(n-2);
        if(F[n-1]==-1) F[n-1] = mfib(n-1);

        F[n] =F[n-2] +F[n-1];
        return F[n];
    }

}

int main(){

    int i;
    for(i=0; i<=10; i++) F[i]=-1;

    printf("fib: %d \n", fib(7));
    printf("mfib: %d \n", mfib(7));
    return 0;
}