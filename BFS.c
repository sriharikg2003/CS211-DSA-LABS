/*
Author Srihari K G
CSE
2100300
Graph Search
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// // color code
// white -1
// grey 0
// black 1

int *color = NULL;

typedef struct vertex
{
    int value;
    struct vertex *next;

} vertex;
int Head = -1, Tail = -1;
int *Queue;
int QueueSize;

void addvertex(int num1, int num2, vertex *hash[])
{
    vertex *node1 = (vertex *)malloc(sizeof(vertex));
    node1->value = num1;
    node1->next = NULL;
    vertex *node2 = (vertex *)malloc(sizeof(vertex));
    node2->value = num2;
    node2->next = NULL;

    if (hash[num1]->next == NULL)
    {
        hash[num1]->next = node2;
    }
    else
    {

        vertex *temp = hash[num1];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node2;
    }

    if (hash[num2]->next == NULL)
    {
        hash[num2]->next = node1;
    }
    else
    {

        vertex *temp = hash[num2];

        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node1;
    }
}

int is_full()
{
    if (Tail == QueueSize - 1)
        return 1;
    else
        return 0;
}

int is_empty()
{
    if ((Head == -1) && (Tail == -1))
    {
        return 1;
    }
    else
        return 0;
}

void Enqueue(int d)
{
    int number_element;

    if (!is_full())
    {
        number_element = d;
        Tail++;
        Queue[Tail] = number_element;

        if (Head == -1)
            Head++;
    }
    else
    {
        return;
    }
}

int Dequeue()
{
    if (!is_empty())
    {
        int num = Queue[Head];
        int i;
        for (i = 0; i < Tail; i++)
        {
            Queue[i] = Queue[i + 1];
        }
        Queue[Tail] = -1;
        if (Tail == 0)
        {
            Tail = -1;
            Head = -1;
        }
        else
            Tail--;
        return num;
    }
    else
    {
        return;
    }
}

int main(int argc, char *argv[])
{
    int i;
    FILE *open = fopen(argv[1], "r");
    FILE *ans = fopen("sd.txt", "w");
    int num1, num2;
    int vertices = 0;
    int edges = 0;
    int c = 0;

    fscanf(open, "%d %d", &num1, &num2);
    vertices = num1;
    edges = num2;
    vertex *hash[vertices];
    for (i = 0; i < vertices; i++)
    {
        hash[i] = (vertex *)malloc(sizeof(vertex));
        hash[i]->value = i;
        hash[i]->next = NULL;
    }

    while (fscanf(open, "%d %d", &num1, &num2) != EOF)
    {
        int d = num1;
        int e = num2;
        addvertex(d, e, hash);
    }
    QueueSize = vertices;
    Queue = (int *)malloc(QueueSize * sizeof(int));

    int color[vertices];
    int distance[vertices];

    color[0] = 0;
    distance[0] = 0;

    for (i = 1; i < vertices; i++)
    {
        color[i] = -1;
        distance[i] = -1;
    }

  

    Enqueue(hash[0]->value);
    while (!is_empty())
    {
        int u = Dequeue();
        vertex *temp;
        temp = hash[u];
        while (temp != NULL)
        {
            if (color[temp->value] == -1)
            {
                color[temp->value] = 0;
                distance[temp->value] = distance[u] + 1;
                Enqueue(temp->value);
            }
            temp = temp->next;
        }
        color[u] = 1;
    }
    for(i=0;i<vertices;i++)
    fprintf(ans,"%d\n",distance[i]);
}