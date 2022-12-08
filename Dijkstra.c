/*
Author : Srihar K G
Dijkstra
210030035
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int vertexnumber;

int Head = -1, Tail = -1;

typedef struct vertex
{
    int n1;
    int n2;
    int edge;
    int pred;
    int dist;
    struct vertex *next;

} vertex;

typedef struct minivertex
{
    int numb;
    int distance;
    int predc;
    int status;
    struct minivertex *next;

} minivertex;
int *Queue;
int QueueSize;
vertex *hash;
void interchange(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int index(int n, minivertex *a[])
{
    int p;
    for (p = 0; p < vertexnumber; p++)
    {
        if (a[p]->numb == n)
        {
            return p;
            break;
        }
    }
}
void makeheap(int heaparray[], int n, int i)
{

    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heaparray[left] > heaparray[largest])
        largest = left;

    if (right < n && heaparray[right] > heaparray[largest])
        largest = right;

    if (largest != i)
    {
        interchange(&heaparray[i], &heaparray[largest]);
        makeheap(heaparray, n, largest);
    }
}
void heapSort(int heaparray[], int n)
{

    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        makeheap(heaparray, n, i);

    for (i = n - 1; i >= 0; i--)
    {
        interchange(&heaparray[0], &heaparray[i]);

        makeheap(heaparray, i, 0);
    }
}

void addvertex(int num1, int num2, int num3, vertex *hash[])
{
    int k;
    vertex *node1 = (vertex *)malloc(sizeof(vertex));
    node1->n1 = num1;
    node1->n2 = num2;
    node1->edge = num3;
    node1->next = NULL;
    vertex *temp;
    for (k = 0; k < vertexnumber; k++)
    {

        if (hash[k]->n1 == num1)
        {
            temp = hash[k];
            break;
        }
    }
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = node1;
}

int minimum(minivertex *hai[])
{
    int i, min;
    min = 999999;
    int pos = -1;
    for (i = 0; i < vertexnumber; i++)
    {
        if (hai[i]->status == 1)
        {
            if (hai[i]->distance < min)
            {
                min = hai[i]->distance;
                pos = i;
            }
        }
    }
    // printf("IN MIN %d\n", pos);
    return pos;
}
int main(int argc, char *argv[])
{
    FILE *open = fopen(argv[1], "r");
    FILE *ans = fopen("dijkstra.txt", "w");
    int source = atoi(argv[2]);
    int num1, num2, num3;
    int count = 0;
    while (fscanf(open, "%d %d %d", &num1, &num2, &num3) != EOF)
    {
        count++;
    }
    rewind(open);
    int *dummyvertices = malloc(2 * count * sizeof(int));
    int i = 0;
    for (i = 0; i < 2 * count; i++)
        dummyvertices[i] = -1;
    i = 0;
    while (fscanf(open, "%d %d %d", &num1, &num2, &num3) != EOF)
    {

        if (i == 0)
        {
            dummyvertices[0] = num1;
            dummyvertices[1] = num2;

            i = 2;
        }
        int j = 0;
        int present = 0;

        for (j = 0; j < i; j++)
        {
            if (dummyvertices[j] == num1)
            {
                present = 1;
                break;
            }
            else
            {
                present = 0;
            }
        }
        if (present == 0)
        {
            dummyvertices[i] = num1;
            i++;
        }

        present = 0;
        for (j = 0; j < i; j++)
        {
            if (dummyvertices[j] == num2)
            {
                present = 1;
                break;
            }
            else
            {
                present = 0;
            }
        }
        if (present == 0)
        {
            dummyvertices[i] = num2;
            i++;
        }
    }
    rewind(open);

    vertexnumber = i;
    // printf("%d ",vertexnumber);
    int *vertices = malloc(vertexnumber * sizeof(int));
    for (i = 0; i < vertexnumber; i++)
    {
        vertices[i] = dummyvertices[i];
    }
    heapSort(vertices, vertexnumber);
    vertex *hash[vertexnumber];
    minivertex *listofvertices[vertexnumber];

    for (i = 0; i < vertexnumber; i++)
    {
        hash[i] = (vertex *)malloc(sizeof(vertex));
        hash[i]->n1 = vertices[i];
        hash[i]->n2 = -1;
        hash[i]->edge = -1;
        hash[i]->next = NULL;
        hash[i]->pred = -1;
        hash[i]->dist = 999999;
        if (hash[i]->n1 == source)
        {
            hash[i]->dist = 0;
        }

        listofvertices[i] = (minivertex *)malloc(sizeof(minivertex));
        listofvertices[i]->numb = vertices[i];
        listofvertices[i]->distance = 999999;
        listofvertices[i]->predc = -1;
        listofvertices[i]->status = 1;

        if (listofvertices[i]->numb == source)
        {
            listofvertices[i]->distance = 0;
        }
    }
    rewind(open);
    //  printf("%d ",listofvertices[index(source,listofvertices)]->numb);
    while (fscanf(open, "%d %d %d", &num1, &num2, &num3) != EOF)
    {

        addvertex(num1, num2, num3, hash);
    }

    int check = 0;
    int dummy = source;

    while (listofvertices[minimum(listofvertices)]->distance < 999999 && listofvertices[minimum(listofvertices)]->status == 1)
    {
        // printf("%d %d\n", listofvertices[minimum(listofvertices)]->distance, listofvertices[minimum(listofvertices)]->numb);
        int u, v;
        int dummy = listofvertices[minimum(listofvertices)]->numb;
        // if (check != 0)
        // {
        // dummy = source;
        listofvertices[index(source, listofvertices)]->status = 0;
        // }

        vertex *temp;
        for (i = 0; i < vertexnumber; i++)
        {
            if (hash[i]->n1 == dummy)
            {
                temp = hash[i];
                u = index(hash[i]->n1, listofvertices);
                break;
            }
        }
        // status = 1 => present in queue
        temp = temp->next;
        while (temp != NULL)
        {

            v = index(temp->n2, listofvertices);

            if (listofvertices[v]->status == 1)
            {
                if (listofvertices[v]->distance > listofvertices[u]->distance + temp->edge)
                {
                    listofvertices[v]->distance = listofvertices[u]->distance + temp->edge;
                }
            }
            temp = temp->next;
        }
        listofvertices[index(dummy, listofvertices)]->status = 0;
        // check = 1;
    }
    int j;

    //////////////dummmmmy
    int *col1 = malloc(count * sizeof(int));
    int *col2 = malloc(count * sizeof(int));
    for (i = 0; i < count; i++)
    {
        col1[i] = -1;
        col2[i] = -1;
    }
    i = 0;
    rewind(open);
    while (fscanf(open, "%d %d %d", &num1, &num2, &num3) != EOF)
    {
        if (i == 0)
        {
            col1[0] = num1;
            i = 1;
            // printf("in 1 %d\n", i);
        }
        else
        {
            int j = 0;
            int present = 0;

            for (j = 0; j < i; j++)
            {
                if (col1[j] == num1)
                {
                    present = 1;
                    break;
                }
                else
                {
                    present = 0;
                }
            }
            if (present == 0)
            {
                col1[i] = num1;

                i++;
            }
        }
    }
    int col1llen = i;
    // printf("%d\n", i);

    rewind(open);
    i = 0;
    j = 0;
    int present;
    while (fscanf(open, "%d %d %d", &num1, &num2, &num3) != EOF)
    {

        if (i == 0)
        {
            for (j = 0; j < col1llen; j++)
            {
                if (col1[j] == num2)
                {
                    present = 1;
                    break;
                }
                else
                {
                    present = 0;
                }
            }
            if (present == 0)
            {
                col2[i] = num2;
                i++;
            }
        }

        else
        {
            present = 0;
            for (j = 0; j < col1llen; j++)
            {
                if (col1[j] == num2)
                {
                    present = 1;
                    break;
                }
                else
                {
                    present = 0;
                }
            }
            if (present == 0)
            {

                for (j = 0; j < vertexnumber; j++)
                {
                    if (col2[j] == num2)
                    {
                        present = 1;
                        break;
                    }
                    else
                    {
                        present = 0;
                    }
                }
                if (present == 0)
                {
                    col2[i] = num2;
                    i++;
                }
            }
        }
    }
    int col2llen = i;
    rewind(open);
    for (j = 0; j < vertexnumber; j++)
    {

        if (listofvertices[j]->distance != 999999)
            fprintf(ans, "%d %d\n", listofvertices[j]->numb, listofvertices[j]->distance);

        else
            fprintf(ans, "%d %d\n", listofvertices[j]->numb, -1);
    }
}