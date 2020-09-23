#include<stdio.h>
#include<stdlib.h>
#include <inttypes.h>

struct Node{
    int data;
    struct Node* nptr;
};

struct Node *head1 = 0;
struct Node *head2 = 0;

struct Node* XOR (struct Node *a, struct Node *b)
{
    return (struct Node*) ((uintptr_t) (a) ^ (uintptr_t) (b));
}

void insert_begin(int data)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = data;
    temp->nptr = head1;
    if(head1!=0){
        head1->nptr = XOR(temp,head1->nptr);
    }
    head1 = temp;
}

void insert_end(int data)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = data;
    if(head2 == 0)
    {
        temp->nptr = head2;
        head2 = temp;
        return;
    }
    struct Node *curr = head2,*prev = 0,*next;
    while(curr!=0){
        next = XOR(prev,curr->nptr);
        prev = curr;
        curr = next;
    }
    temp->nptr = prev;
    prev->nptr = XOR(prev->nptr,temp);
}

void printList (struct Node *head)
{
    struct Node *curr = head;
    struct Node *prev = 0;
    struct Node *next;

    printf("list: ");

    while (curr != 0)
    {
        printf ("%d ", curr->data);
        next = XOR(prev, curr->nptr);
        prev = curr;
        curr = next;
    }
}

int main ()
{
    int item;
    printf("\nenter elements to insert at front: (-1 to terminate)\n");
    while(1){
        scanf("%d",&item);
        if(item==-1)
            break;
        insert_begin(item);
    }
    printList (head1);

    printf("\n\nenter elements to insert at end: (-1 to terminate)\n");
    while(1){
        scanf("%d",&item);
        if(item==-1)
            break;
        insert_end(item);
    }
    printList (head2);
    return (0);
}
