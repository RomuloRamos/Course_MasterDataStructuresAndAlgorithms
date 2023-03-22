#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
}*first = NULL, *secound = NULL, *third = NULL;


void create(int A[], int n)
{
    int i;
    struct Node *t, *last;

    first=(struct Node *) malloc(sizeof(struct Node));
    first->data =A[0];
    first->next =NULL;

    last = first;

    for (i = 1; i < n; i++)
    {
        t = (struct Node*) malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
    
}

void create2(int A[], int n)
{
    int i;
    struct Node *t, *last;

    secound=(struct Node *) malloc(sizeof(struct Node));
    secound->data =A[0];
    secound->next =NULL;

    last = secound;

    for (i = 1; i < n; i++)
    {
        t = (struct Node*) malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
    
}

void display(struct Node *p)
{

    while (p!= NULL)
    {
        printf("%d ", p->data);
        p=p->next;
    }   
}

void RDisplay(struct Node *p)
{

    if(p!= NULL)
    {
        printf("%d ", p->data);
        RDisplay(p->next);
    }   
}

int count(struct Node *p)
{
    int l=0;
    while (p)
    {
        l++;
        p=p->next;
    }
    return l;
}

int RCount(struct Node *p)
{
    if(p)
    {
        return RCount(p->next)+1;
    }
    else return 0;
}

int sum(struct Node *p)
{
    int s=0;
    while (p!= NULL)
    {
        s+=p->data;
        p=p->next;
    }
    return s;   
}

int RSum(struct Node *p)
{
    
    if(p== NULL)
    {
        return 0;
    }
    else
        return RSum(p->next)+p->data;   
}

int max(struct Node *p)
{
    int maxValue=INT_MIN;

    while (p)
    {
        if(p->data>maxValue)
            maxValue=p->data;
        
        p=p->next;
    }
    return maxValue;
    
}

int RMax(struct Node *p)
{
    int x=0;
    if(p==0)
        return INT_MIN;
    
    x=RMax(p->next);
    if(x>p->data)
        return x;
    else return p->data;
}

struct Node * LSearch(struct Node *p, int key)
{
    struct Node *q = NULL;

    while(p!=NULL)
    {
        if(key == p->data)
        {
            q->next = p->next;
            p->next = first;
            first = p;
            return p;
        }
        q=p;
        p=p->next;
    }
    return NULL;
}

void insert(struct Node *p, int index, int value){

    if(index < 0 || index > count(p))
        return;
    
    struct Node *t = (struct Node *) malloc(sizeof(struct Node));
    t->data = value; 

    if(index == 0)
    {
        t->next = first;
        first=t;
    }
    else
    {
        int i;
        for(i=0; i<index-1;i++)
            p=p->next;
        
        t->next = p->next;
        p->next = t;
    }

}

void SortedInsert(struct Node * p, int x)
{

    struct Node *t, *q = NULL;

    t = (struct Node*) malloc(sizeof(struct Node));
    t->data = x;
    t->next = NULL;

    if(first == NULL)
    {
        first=t;
    }     
    else
    {
        while (p && p->data < x)
        {
            q = p;
            p = p->next;
        }
        if(p == first)
        {
            t->next = first;
            first = t;
        }
        else
        {
            t->next = q->next;
            q->next = t;
        }
    }
}

int deleteElement(struct Node *p, int index)
{
    struct Node * q = NULL;
    int x=-1;

    if(index < 1 || index > count(p))
    {
        return -1;
    }

    if(index == 1)
    {
        q = first;
        x = first->data;
        first = first->next;
        free(q);
        return x;
    }
    else
    {
        for(int i = 0; i < index-1; i++)
        {
            q = p;
            p = p->next;
        }

        q->next = p->next;
        x = p->data;
        free(p);
        return x;
    }
}

int isSorted(struct Node *p)
{
    if(!p)
        return 0;
    int x = p->data;
    p = p->next;

    while (p!= NULL)
    {
        if(p->data < x)
            return 0;
        
        x = p->data;
        p = p->next;
    }

    return 1;
    
}

void Sorte(struct Node **p)
{
    struct Node *first = *p,*curr = first, *next = first->next, *last = first, *aux = NULL;  

    while (curr)
    {
        // display(first);
        // printf("\n");
        if((next) && curr->data >= next->data)
        {   
            
            if(curr->next == next)
            {
                if(curr->data == next->data)
                {   
                    last = next;
                    next = next->next;
                    continue;
                }
                curr->next = next->next;
            }
            last->next = next->next; //NULL
            next->next = curr;
            curr = next;
            if(aux)
                aux->next = curr;
            next = last->next;
        }
        else{
            if((next) && next->next)
            {
                last = next;
                next = next->next;
            }
            else //All elements were compared... change the comparator.
            {
                if(first->data > curr->data) 
                    first = curr; 
                last = curr; 
                aux = curr;
                curr = curr->next; 
                if(curr)
                    next = curr->next; 
            }
        }
    }
    
    *p = first;
    
}

//It only works to Sorted Lists
void RemoveDuplicate(struct Node*p)
{
    struct Node * q = p->next;

    while (q!=NULL)
    {
        if(p->data != q->data)
        {
            p=q;
            q=q->next;
        }
        else{
            p->next = q->next;
            free(q);
            q=p->next;
        }
    }
    
}

void Reverse1(struct Node * p)
{
    int *A, i=0;
    struct Node *q = p;
    A = (int*) malloc(sizeof(int)*count(p));

    while(q != NULL)
    {
        A[i] = q->data;
        q = q->next;
        i++;
    }
    q = p;
    i--;
    while (q != NULL)
    {
        q->data = A[i];
        q = q->next;
        i--;
    }
}

void Reverse2(struct Node * p)
{
    struct Node* q = NULL, *r = NULL;

    while (p != NULL)
    {
        r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
    first = q;

}

void Reverse3(struct Node * q, struct Node * p)
{
    if(p)
    {
        Reverse3(p, p->next);
        p->next = q;
    }
    else{
        first = q;
    }
}

void Concat(struct Node *p, struct Node *q)
{
    third = p;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = q;
    
}

void Merge(struct Node *p, struct Node *q)
{
    struct Node *last;
    if(p->data < q->data)
    {
        third = last = p;
        p=p->next;
        third->next = NULL;
    }
    else {
        third = last = q;
        q = q->next;
        third->next = NULL;
    }

    while (p && q)
    {
        if(p->data < q->data)
        {
            last->next = p;
            last = p;
            p=p->next;
            last->next = NULL;
        }
        else{
            last->next = q;
            last = q;
            q=q->next;
            last->next = NULL;
        }
    }
    if(p) last->next = p;
    if(q) last->next = q;

}

int main(int argc, char const *argv[])
{
    int A[]={3,5,5,7,10,15,8,12,20};
    int B[]={1, 2, 3, 4, 5, 6, 4};
    
    create(A, 9);

    printf("FIRST LIST - Length is %d\n", count(first));
    printf("FIRST LIST - Sum is %d\n", sum(first));
    printf("FIRST LIST - The max value is %d\n", max(first));
    printf("FIRST LIST - The max value with recursive method is %d\n", max(first));
    display(first);
    printf("\n");
    RDisplay(first);

    insert(first,8,100);
    insert(first,0,200);

    if(LSearch(first, 15)) //It will move the found value to the beginning of the list
    {
        printf("\nFIRST LIST - The value %d was found in the list!\n", 15);
        printf("FIRST LIST - Now, the list is: ");
        display(first);
    }
    else    printf("FIRST LIST - Value didn't found");

    printf("\nFIRST LIST - Inserting the value 9 in the Sorted way!\n");
    SortedInsert(first, 9);
    display(first);

    printf("\nFIRST LIST - Deleting the element at index 7\n");
    deleteElement(first, 7);
    display(first);


    if(isSorted(first))
    {
        printf("\nFIRST LIST - The list is sorted\n");
        display(first);
        printf("\nFIRST LIST - Removing the duplicated values\n");
        RemoveDuplicate(first);
        display(first);
    }
    else    printf("\nFIRST LIST - The list is Unsorted\n");   

    printf("\nFIRST LIST - Reversing the list:\n");
    Reverse1(first);
    display(first);

    printf("\nFIRST LIST - Reversing the list:\n");
    Reverse2(first);
    display(first);

    printf("\nFIRST LIST - Reversing the list:\n");
    Reverse3(NULL, first);
    display(first);

    printf("\nCreating the secound list:\n");
    create2(B,7);
    display(secound);

    Sorte(&first);
    Sorte(&secound);
    printf("\nMerging the lists:\n");
    Merge(first, secound);
    display(first);

    // printf("\nConcatenating the lists:\n");
    // Concat(first, secound);
    // display(first);

    printf("\nSorting the First List:\n");
    Sorte(&first);
    display(first);

    if(isSorted(first))
    {
        printf("\nFIRST LIST - The list is sorted\n");
        display(first);
        printf("\nFIRST LIST - Removing the duplicated values\n");
        RemoveDuplicate(first);
        display(first);
    }
    else    printf("\nFIRST LIST - The list is Unsorted\n");   

    return 0;
}
