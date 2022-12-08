/*
Author : Srihari K G
Computer Science and Engineering
IIT Dharwad

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// stack begins
typedef struct node_stack
{
    int data;
    struct node_stack *next;
} node_stack;

node_stack *temp_stack, *currentnode_stack, *headnode_stack = NULL;
int len_stack = 0;

void traversal_stack(FILE *sta)
{

    if (len_stack == 0)
        fprintf(sta, "\n");
    else
    {

        int k;
        for (k = 0; k < len_stack; k++)
        {
            int j = 0;
            node_stack *traversal_stack;
            for (traversal_stack = headnode_stack; j < len_stack - k - 1; j++)
            {
                traversal_stack = traversal_stack->next;
            }
            fprintf(sta, "%d ", traversal_stack->data);
        }
        fprintf(sta, "\n");
    }
}

void push(int n, int max, FILE *sta)
{
    if (len_stack < max)
    {

        if (len_stack == 0)
        {
            node_stack *newnode_stack;
            newnode_stack = (node_stack *)malloc(sizeof(node_stack));

            headnode_stack = newnode_stack;
            headnode_stack->data = n;
            headnode_stack->next = NULL;
            fprintf(sta, "pushed %d\n", headnode_stack->data);

            len_stack++;
        }
        else
        {
            node_stack *temp_stack = headnode_stack;
            node_stack *newnode_stack;
            newnode_stack = (node_stack *)malloc(sizeof(node_stack));
            newnode_stack->next = NULL;
            newnode_stack->data = n;
            int i;
            for (i = 0; i < len_stack - 1; i++)
            {
                temp_stack = temp_stack->next;
            }
            temp_stack->next = newnode_stack;
            len_stack++;
            fprintf(sta, "pushed %d\n", temp_stack->next->data);
        }
    }

    else
        fprintf(sta, "overflow\n");
}

void pop(int y, FILE *sta)
{
    node_stack *delnode;
    int n;

    if (len_stack <= 0)
        fprintf(sta, "underflow\n");
    else
    {
        len_stack--;

        delnode = headnode_stack;
        node_stack *temp_stack = headnode_stack;

        if (headnode_stack->next == NULL)
        {
            n = headnode_stack->data;
            headnode_stack = NULL;
            fprintf(sta, "popped %d\n", n);
        }

        else
        {
            while (delnode->next != NULL)
            {
                temp_stack = delnode;
                delnode = delnode->next;
            }
            n = delnode->data;
            temp_stack->next = NULL;
            fprintf(sta, "popped %d\n", n);
        }
    }
}

void findstack_stack(int n, FILE *sta)
{
    node_stack *findstack_stacknode;
    for (findstack_stacknode = headnode_stack; findstack_stacknode != NULL;)
    {
        if (findstack_stacknode->data == n)
        {
            fprintf(sta, "found %d\n", n);
            break;
        }
        findstack_stacknode = findstack_stacknode->next;
    }
    if (findstack_stacknode == NULL)
        fprintf(sta, "not found %d\n", n);
}

// queue begins

typedef struct node_queue
{
    int data;
    struct node_queue *next;
} node_queue;
node_queue *head_queue = NULL, *tail;
int len_queue = 0;

void create(int max)
{
    node_queue *newnode = malloc(sizeof(node_queue));
    node_queue *temp;
    newnode->data = -452;
    int i;
    head_queue = newnode;

    for (i = 1; i <= max; i++)
    {

        node_queue *news = malloc(sizeof(node_queue));
        news->data = -452;

        if (i == 1)
        {
            head_queue->next = news;
            temp = news;
            // printf("\n%d", i);
        }

        else if (i > 1 && i < max)
        {
            temp->next = news;
            temp = news;
            // printf("\n%d", i);
        }

        else if (i == max)
        {
            temp->next = head_queue;
            // printf("\n%d", i);
        }
    }
}

void enqueue(int n, int max, FILE *que)
{
    if (len_queue >= 0 && len_queue < max)
    {
        if (len_queue == 0)
        {
            head_queue->data = n;
            fprintf(que, "enqueued %d\n", head_queue->data);
            len_queue++;
        }

        else
        {
            node_queue *cur = head_queue;
            int i;
            for (i = 0; i < len_queue; i++)
            {
                cur = cur->next;
            }
            cur->data = n;
            fprintf(que, "enqueued %d\n", cur->data);
            len_queue++;
        }
    }

    else if (len_queue >= max)
        fprintf(que, "overflow\n");
}

void traversal_queue(FILE *que)
{
    int i;
    node_queue *temp = head_queue;
    if (len_queue == 0)
    {
        fprintf(que, "\n");
    }
    else
    {
        for (i = 0; i < len_queue; i++)
        {
            fprintf(que, "%d ", temp->data);
            temp = temp->next;
        }
        fprintf(que, "\n");
    }
}

void find_queue(int n, FILE *que)
{
    int i, c = 0;
    node_queue *temp = head_queue;

    for (i = 0; i < len_queue; i++)
    {
        if (temp->data == n)
        {
            c++;
            fprintf(que, "found %d\n", temp->data);
            break;
        }
        temp = temp->next;
    }

    if (c == 0)
    {
        fprintf(que, "not found %d\n", n);
    }
}

void dequeue(int d, FILE *que)
{

    if (len_queue != 0)
    {
        fprintf(que, "dequeued %d\n", head_queue->data);
        head_queue->data = -452;
        head_queue = head_queue->next;
        len_queue--;
    }
    else
        fprintf(que, "underflow\n", d);
}

// doble begins
typedef struct node_ddl
{
    struct node_ddl *prev;
    struct node_ddl *next;
    int data;
} node_ddl;

int len_ddl = 0;
node_ddl *temp, *delnode;
node_ddl *headnode_ddl = NULL;
void add_dll(int n, FILE *dll)
{
    node_ddl *currentnode_ddl = (node_ddl *)malloc(sizeof(node_ddl));

    if (len_ddl == 0)
    {
        currentnode_ddl->data = n;
        currentnode_ddl->prev = NULL;
        currentnode_ddl->next = NULL;
        headnode_ddl = currentnode_ddl;
        len_ddl++;
        fprintf(dll, "inserted %d\n", headnode_ddl->data);
    }

    else
    {
        currentnode_ddl->data = n;
        currentnode_ddl->next = headnode_ddl;
        headnode_ddl->prev = currentnode_ddl;
        currentnode_ddl->prev = NULL;
        headnode_ddl = currentnode_ddl;

        fprintf(dll, "inserted %d\n", headnode_ddl->data);
        len_ddl++;
    }
}

int find_dll(int n, FILE *dll)
{
    int i, c = 0;
    node_ddl *search = headnode_ddl;
    for (i = 0; i < len_ddl; i++)
    {
        if (search->data == n)
        {
            fprintf(dll, "found %d\n", search->data);
            c++;

            break;
        }

        search = search->next;
    }
    if (c == 0)
    {
        fprintf(dll, "not found %d\n", n);
    }
}

void traversal_dll(FILE *dll)
{
    if (len_ddl == 0)
        fprintf(dll, "\n");
    else
    {

        node_ddl *tempo = headnode_ddl;
        int i = 0;
        for (i = 0; i < len_ddl; i++)
        {
            fprintf(dll, "%d ", tempo->data);
            tempo = tempo->next;
        }
        fprintf(dll, "\n");
    }
}
void del_dll(int n, FILE *dll)

{

    if (len_ddl == 0)
        fprintf(dll, "cannot delete %d\n", n);

    else
    {

        int i, c = 0;
        node_ddl *search = headnode_ddl;
        for (i = 0; i < len_ddl; i++)
        {
            if (search->data == n)
            {
                len_ddl--;
                c++;
                fprintf(dll, "deleted %d\n", search->data);

                if (search->prev != NULL && search->next != NULL)
                {
                    search->prev->next = search->next;
                    search->next->prev = search->prev;
                    free(search);
                }

                else if (search->next == NULL)
                {
                    search->prev->next = NULL;
                    free(search);
                }

                else if (search == headnode_ddl)
                {

                    headnode_ddl = headnode_ddl->next;
                    free(search);
                }

                break;
            }

            search = search->next;
        }

        if (c == 0)
        {
            fprintf(dll, "cannot delete %d\n", n);
        }
    }
}

// main function

int main(int argc, char *argv[])
{
    int max = atoi(argv[2]);
    char line[100];
    ;
    FILE *open, *sta, *que, *dll;
    open = fopen(argv[1], "r");
    create(max);
    char str[50];
    sta = fopen("stack.txt", "w");
    que = fopen("queue.txt", "w");
    dll = fopen("dll.txt", "w");
    while (fgets(str, 50, open) != NULL)
    {
        int m = strlen(str);
        char op = str[0];
        char line[m];
        int k;

        for (k = 0; k < m; k++)
        {
            line[k] = str[k + 2];
        }
        int d = atoi(line);

        switch (op)
        {
        case '+':
            push(d, max, sta);
            enqueue(d, max, que);
            add_dll(d, dll);
            break;
        case '-':
            pop(d, sta);
            dequeue(d, que);
            del_dll(d, dll);
            break;
        case '!':
            traversal_stack(sta);
            traversal_queue(que);
            traversal_dll(dll);
            break;
        case '?':
            findstack_stack(d, sta);
            find_queue(d, que);
            find_dll(d, dll);
            break;
        }
    }
}
