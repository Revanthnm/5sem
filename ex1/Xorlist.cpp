#include<stdio.h>
#include<stdlib.h>
#include <inttypes.h>

struct Node{
    int data;
    struct Node* nptr;
};

struct Node *head1 = NULL;
struct Node *head2 = NULL;

struct Node* XOR (struct Node *a, struct Node *b)
{
    return (struct Node*) ((uintptr_t) (a) ^ (uintptr_t) (b));
}

void insert_begin(int data)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = data;
    temp->nptr = head1;
    if(head1!=NULL){
        head1->nptr = XOR(temp,head1->nptr);
    }
    head1 = temp;
}

void insert_end(int data)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = data;
    if(head2 == NULL)
    {
        temp->nptr = head2;
        head2 = temp;
        return;
    }
    struct Node *curr = head2,*prev = 0,*next;
    while(curr!=NULL){
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

    while (curr != NULL)
    {
        printf ("%d ", curr->data);
        next = XOR(prev, curr->nptr);
        prev = curr;
        curr = next;
    }
    printf("\n");
}

void delete_begin(struct Node *head){
    if(head==NULL || head->nptr==NULL){
        head = NULL;
        return;
    }
	struct Node *curr = head, *next = head->nptr;
	next->nptr = XOR(next->nptr,head);
	free(head);
	head = next;
    printList(head);
}

void delete_end(struct Node *head){
    if(head==NULL || head->nptr==NULL){
        head = NULL;
        return;
    }
    struct Node *prev = NULL, *curr = head, *next;
    while(curr->nptr!=prev)
	{
		next = XOR(curr->nptr,prev);
		prev = curr;
		curr = next;
	}
	prev->nptr = XOR(prev->nptr,curr);
	free(curr);
    printList(head);
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
    delete_begin(head1);
    delete_end(head1);
    return (0);
}

