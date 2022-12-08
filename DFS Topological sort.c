/*
Author Srihari K G
CSE
2100300
Topological sort
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int time;
int *color, *init, *final;
typedef struct vertex
{
    int value;
    struct vertex *next;
} vertex;

typedef struct topo
{
    int value;
    struct topo *next;
} topo;

topo *lovely;
vertex *hash;
void addvertex(int num1, int num2, vertex *hash[])
{
    vertex *node1 = (vertex *)malloc(sizeof(vertex));
    node1->value = num2;
    node1->next = NULL;

    if (hash[num1]->next == NULL)
    {
        hash[num1]->next = node1;
    }
    else
    {
        vertex *temp = hash[num1];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node1;
    }
}
void addtolist(int u)
{
    topo *node1 = (topo *)malloc(sizeof(topo));
    node1->value = u;
    node1->next = NULL;
    if (lovely == NULL)
    {
        lovely = node1;
    }
    else
    {
        node1->next = lovely;
        lovely = node1;
    }
}
void dfsvisit(int u, vertex *hash[])
{
    time = time + 1;
    init[u] = time;
    color[u] = 1;

    vertex *temp = hash[u];
    if (hash[u]->next != NULL)
    {
        temp = temp->next;
        while (temp != NULL)
        {
            if (color[temp->value] == 0)
                dfsvisit(temp->value, hash);
            temp = temp->next;
        }
    }
    color[u] = 2;
    time = time + 1;
    final[u] = time;
    addtolist(u);
}

int main(int argc, char *argv[])
{
    int i;
    lovely = NULL;
    time = 0;
    FILE *open = fopen(argv[1], "r");
    FILE *ans = fopen("ts.txt", "w");
    int num1, num2;
    int vertices = 0;
    int edges = 0;
    fscanf(open, "%d %d", &num1, &num2);
    vertices = num1;
    edges = num2;
    color = malloc(sizeof(int) * vertices);
    init = malloc(sizeof(int) * vertices);
    final = malloc(sizeof(int) * vertices);
    for (i = 0; i < vertices; i++)
    {
        init[i] = -1;
        final[i] = -1;
        color[i] = 0;
    }
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

    for (i = 0; i < vertices; i++)
    {
        if (color[i] == 0)
        {
            dfsvisit(i, hash);
        }
    }
    topo *temp = lovely;
    while (temp->next != NULL)
    {
        fprintf(ans, "%d\n", temp->value);
        temp = temp->next;
    }
    fprintf(ans, "%d\n", temp->value);
}
