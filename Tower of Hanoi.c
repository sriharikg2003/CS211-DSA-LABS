/*
Author - Srihari K G
Branch - Computer Science and Engineering
Roll No- 210030035
INDIAN INSTITUTE OF TECHNOLOGY

*/


/*                TOWER        OF      HANOI        ASSIGNMENT         DSA     */


#include <stdlib.h>
#include <stdio.h>


struct stacks
{

    int temp, top;
    int *stackname;
};

int temp;

struct stacks a, b, c;

int isempty(int stack[], int *top, int size)            //checks if particular stack is empty
{
    if (*top == -1)
        return 1;
    else
        return 0;
}

int isfull(int stack[], int *top, int size)         //checks if particular stack is full
{
    if (*top == size - 1)
        return 1;

    else
        return 0;
}

void push(int stack[], int size, int *top, int val, char name, FILE *f)   //pushes the element to the stack
{
    int n;
    if (!isfull(stack, top, size))
    {
        (*top)++;
        stack[(*top)] = val;
        fprintf(f, "Push disk %d to Stack %c\n", val, name);
    }
    else
    {
        printf("Stack is full \n");  //stack overflow
    }
}

void pop(int stack[], int size, int *top, char name, FILE *f)    //deletes the element from stack
{
    if (!isempty(stack, top, size))
    {
        fprintf(f, "Pop disk %d from Stack %c\n", stack[(*top)], name);
        stack[(*top)] = -1;
        (*top)--;
    }
    else
    {
        printf("Stack is  empty\n");   //stack underflow
    }
}

int top(int stack[], int *top, int size)                //returns the data stored in the position stack
{
    if (!isempty(stack, top, size))
    {
        return stack[(*top)];
    }
}

void toh(int n, int size, int source[], int *source_top, char source_name, int aux[], int *aux_top, char aux_name, int dest[], int *dest_top, char dest_name, FILE *f)  //computes the tower of hanoi functionality
{
    if (n == 0)
    {
        return;
    }
    toh(n - 1, size, source, source_top, source_name, dest, dest_top, dest_name, aux, aux_top, aux_name, f);

    int k;
    k = top(source, source_top, size);
    pop(source, size, source_top, source_name, f);
    push(dest, size, dest_top, k, dest_name, f);

    toh(n - 1, size, aux, aux_top, aux_name, source, source_top, source_name, dest, dest_top, dest_name, f);
}

int main(int argument_from_command_line, char *array_of_command_line_arguments[])
{
    FILE *f;
    int n, size;
    if (argument_from_command_line != 2)
    {
        printf("\nEnter properly in arguments");
    }
    n = atoi(array_of_command_line_arguments[1]);
    f = fopen("toh.txt", "w");

    if (f == NULL)
    {
        printf("INVALID FILE");
    }

    a.top = -1;
    b.top = -1;
    c.top = -1;
    size = n;
    a.stackname = (int *)malloc(n * sizeof(int));           //allocation of memory space from heap memory
    b.stackname = (int *)malloc(n * sizeof(int));
    c.stackname = (int *)malloc(n * sizeof(int));
    int i;
    for (i = n; i > 0; i--)
    {

        push(a.stackname, size, &a.top, i, 'A', f);
    }
    // for (i=0;i<size;i++)
    // printf("A[%d] = %d B[%d] = %d C[%d] = %d \n",i,a.stackname[i],i,b.stackname[i],i,c.stackname[i]);
    toh(n, size, a.stackname, &a.top, 'A', b.stackname, &b.top, 'B', c.stackname, &c.top, 'C', f);

    fclose(f);          //closes the file

    //   for (i=0;i<size;i++)
    // printf("A[%d] = %d B[%d] = %d C[%d] = %d \n",i,a.stackname[i],i,b.stackname[i],i,c.stackname[i]);
}
