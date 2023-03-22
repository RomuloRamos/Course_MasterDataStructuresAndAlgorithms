#include <stdio.h>

void Permutation(char S[], int k)
{

    static char A[10] = {0};
    static char Res[10];

    int iCounter;
    if((S[k] == 0) && (Res[k] == 0))
    {
        printf("%s\n", Res);
    }
    else
    {
        for(iCounter = 0; S[iCounter] != 0; iCounter++)
        {
            if(A[iCounter] == 0)
            {
                Res[k] = S[iCounter];
                A[iCounter] = 1;
                Permutation(S, k+1);
                A[iCounter] = 0;
            }
        }
    }

}

int main()
{
    char S[] = "ABC";
    Permutation(S, 0);
    return 0;
}