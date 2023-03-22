#include <stdio.h>
#include <stdlib.h>

struct Terms
{
    int coeff;
    int exp;
};

struct Poly
{
    int n;
    struct Terms *terms;
};

void create(struct Poly *p)
{
    int i;
    printf("Enter with the number of terms:");
    scanf("%d", &p->n);
    p->terms = (struct Terms*) malloc(p->n * sizeof(struct Terms));

    printf("Enter with the Terms: \n");
    for(i=0; i< p->n; i++)
        scanf("%d%d", &p->terms[i].coeff, &p->terms[i].exp);
}

void display(struct Poly p)
{
    int i;
    for(i=0; i<p.n; i++)
    {
        printf((p.terms[i].coeff>0?"+%dX%d":"%dX%d"),p.terms[i].coeff, p.terms[i].exp);
    }
    
    printf("\n");
}

struct Poly * add(struct Poly *p1, struct Poly *p2)
{
    struct Poly *sum;

    sum = (struct Poly*) malloc(sizeof(struct Poly));

    sum->terms  = (struct Terms*) malloc(( p1->n+ p2->n ) * sizeof(struct Terms));
    
    int iElementP1 = 0, iElementP2 = 0, iElementSum = 0;
    while ( (iElementP1 < p1->n) && (iElementP2 < p2->n) )
    {
        if(p1->terms[iElementP1].exp < p2->terms[iElementP2].exp)
            sum->terms[iElementSum++] = p1->terms[iElementP1++];
        
        else if(p1->terms[iElementP1].exp > p2->terms[iElementP2].exp)
            sum->terms[iElementSum++] = p2->terms[iElementP2++];
        
        else 
        {
            sum->terms[iElementSum].exp = p1->terms[iElementP1].exp;
            sum->terms[iElementSum++].coeff = p1->terms[iElementP1++].coeff + p2->terms[iElementP2++].coeff;
        }
    }
    for(; iElementP1 < p1->n; iElementP1++) sum->terms[iElementSum++]=p1->terms[iElementP1];
    for(; iElementP2 < p2->n; iElementP2++) sum->terms[iElementSum++]=p2->terms[iElementP2];

    sum->n = iElementSum;
    return sum;
}

int main(int argc, char const *argv[])
{
    struct Poly p1, p2, *p3;

    create(&p1);
    create(&p2);

    display(p1);
    display(p2);

    p3=add(&p1, &p2);
    display(*p3);
    return 0;
}
