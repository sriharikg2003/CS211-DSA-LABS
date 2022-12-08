/*

Author: Srihari K G
210030035
MST


*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct box
{
    int n1;
    int n2;
    int edgelength;

} box;

typedef struct dabba
{
    int data;
    int setdata;
    struct dabba *next;

} dabba;

// Function to interchange the the position of two elements
void interchange(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
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

int ctr;
FILE *ans;
int areset(int a, int b, dabba **darry, int vertnumber)
{

    ctr++;

    int i = 0;
    int c = 0;
    int n1, n2;
    if (a < b)
    {
        n1 = a;
        n2 = b;
    }
    else
    {
        n1 = b;
        n2 = a;
    }

    // n1 smaller than n2
    int i1, i2;
    i1 = -1;
    i2 = -1;
    for (i = 0; i < vertnumber; i++)
    {

        if (darry[i]->data == n1)
            i1 = i;

        if (darry[i]->data == n2)
            i2 = i;
    }
    // i1 smaller than i2

    if (darry[i1]->setdata == -1 && darry[i2]->setdata == -1)
    {

        darry[i1]->setdata = ctr;
        darry[i2]->setdata = ctr;
        return 0;
    }

    if (darry[i2]->setdata == -1 && darry[i1]->setdata != -1)
    {

        darry[i2]->setdata = ctr;
        int newctr = darry[i1]->setdata;
        for (i = 0; i < vertnumber; i++)
        {
            if (darry[i]->setdata == newctr)
                darry[i]->setdata = ctr;
        }
        return 0;
    }

    else if (darry[i1]->setdata == -1 && darry[i2]->setdata != -1)
    {

        darry[i1]->setdata = ctr;
        int newctr = darry[i2]->setdata;
        for (i = 0; i < vertnumber; i++)
        {
            if (darry[i]->setdata == newctr)
                darry[i]->setdata = ctr;
        }
        return 0;
    }

    else if ((darry[i1]->setdata >= 0 && darry[i2]->setdata >= 0) && (darry[i1]->setdata == darry[i2]->setdata))
    {

        return 1;
    }
    if ((darry[i1]->setdata >= 0 && darry[i2]->setdata >= 0) && (darry[i1]->setdata != darry[i2]->setdata))
    {
        int newctr = darry[i2]->setdata;
        for (i = 0; i < vertnumber; i++)
        {
            if (darry[i]->setdata == newctr)
                darry[i]->setdata = ctr;
        }

        newctr = darry[i1]->setdata;
        for (i = 0; i < vertnumber; i++)
        {
            if (darry[i]->setdata == newctr)
                darry[i]->setdata = ctr;
        }

        return 0;
    }
}

int main(int argc, char *argv[])
{

    ctr = 0;
    int i;
    FILE *open = fopen(argv[1], "r");
    ans = fopen("mst.txt", "w");
    int num1, num2, num3;
    int count = 0;
    while (fscanf(open, "%d %d %d", &num1, &num2, &num3) != EOF)
    {
        count++;
    }

    rewind(open);
    dabba *darry[2 * count];

    // array with sorted edges and n1 and n2
    box *dummyarray[count];

    // edges array
    box *edgefamily[count];
    int* edgearray= malloc(count*sizeof(int));

    for (i = 0; i < count; i++)
    {
        edgefamily[i] = (box *)malloc(sizeof(box));
    }
    i = 0;

    // n
    while (fscanf(open, "%d %d %d", &num1, &num2, &num3) != EOF)
    {
        edgefamily[i]->n1 = num1;
        edgefamily[i]->n2 = num2;
        edgefamily[i]->edgelength = num3;
        edgearray[i] = num3;

        i++;
    }

    // sort edges
    // printf("sat\n");
    heapSort(edgearray, count);
    // printf("end \n");

    // n2
    int j = 0;

    // printf("strated edge corr\n");
    for (i = 0; i < count; i++)
    {
        dummyarray[i] = (box *)malloc(sizeof(box));
        dummyarray[i]->edgelength = edgearray[i];

        for (j = 0; j < count; j++)
        {
            if (edgefamily[j]->edgelength == dummyarray[i]->edgelength)
            {
                dummyarray[i]->n1 = edgefamily[j]->n1;
                dummyarray[i]->n2 = edgefamily[j]->n2;
                break;
            }
        }
    }
    // printf("endede edge corr\n");

    // n
    // int vertex[2 * count];
    // for (i = 0; i < 2 * count; i++)
    // {
    //     vertex[i] = -1;
    // }
    // i = 0;

    int *vertex = malloc(2 * count * sizeof(int));
    for (i = 0; i < 2 * count; i++)
    {
        vertex[i] = -1;
    }
    i = 0;
    // printf("CEATED ARRAY BIG");
    // n
    while (i < count)
    {
        vertex[i] = edgefamily[i]->n1;
        vertex[i + count] = edgefamily[i]->n2;
        i++;
    }

    // printf("start second  hep 2 \n");

    heapSort(vertex, 2 * count);

    // printf("end  second hep 2 \n");

    // free(edgefamily);

    //     dabba *darry[2* count];
    // printf("CREATE ARRAY\n");
    // n
    for (i = 0; i < 2 * count; i++)
    {

        darry[i] = (dabba *)malloc(sizeof(dabba));
        darry[i]->data = -1;
        darry[i]->next = NULL;
        darry[i]->setdata = -1;
    }

    i = 0;

    // n2
    for (j = 0; j < 2 * count;)
    {
        darry[i]->data = vertex[j];
        i++;
        while (vertex[j] == vertex[j + 1])
        {
            j++;
        }
        j++;
    }

    // printf("vertex array hep 2 \n");

    int vertnumber = i;
    for (i = vertnumber; i < 2 * count; i++)
    {
        darry[i] = NULL;
    }
    for (i = 0; i < count; i++)
    {
        int d = areset(dummyarray[i]->n1, dummyarray[i]->n2, darry, vertnumber);

        if (d == 0)
        {
            // printf( "%d %d %d\n", dummyarray[i]->n1, dummyarray[i]->n2, dummyarray[i]->edgelength);

            fprintf(ans, "%d %d %d\n", dummyarray[i]->n1, dummyarray[i]->n2, dummyarray[i]->edgelength);
        }
    }
}
