/*
Author Srihari K G
CSE
210030035
Hash Map
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int *a;
int sizeOfIndex;

typedef struct list
{
    char word[1000];
    struct list *next;
} list;

int findascii(char word[])
{
    int l;
    int sum = 0;
    for (l = 0; l < strlen(word); l++)
    {
        int val;
        val = word[l];
        sum = sum + val;
    }

    return sum;
}

void addword(char add[], list **a)
{
    if (*a == NULL)
    {
        list *head = malloc(sizeof(list));
        strcpy(head->word, add);
        head->next = NULL;
        *a = head;
      
    }
    else
    {

        list *temp = malloc(sizeof(list));
        strcpy(temp->word, add);
        temp->next = *a;
        *a = temp;
    }
}

char *sort(char str[])
{
    int i, l, j;
    char ch;
    l = strlen(str);
    for (i = 1; i < l; i++)
        for (j = 0; j < l - i; j++)
            if (str[j] > str[j + 1])
            {
                ch = str[j];
                str[j] = str[j + 1];
                str[j + 1] = ch;
            }
    return str;
}

void printanagram(FILE *ans, char word[], list **a)
{
    char w[100];

    list *temp = malloc(sizeof(list));

    temp = *a;
    strcpy(w, word);
int c=0;
    while (temp != NULL)
    {
        char dummy[100];
        strcpy(dummy, temp->word);

        if (strcmp(sort(w), sort(dummy)) == 0)
            {fprintf(ans, "%s ", temp->word);
            
            c=1;
            }
        temp = temp->next;
    }
    if(c==0)
    {
    fprintf(ans, "\n");
    }
    
    else
    {fseek(ans, -1, SEEK_CUR);
    fprintf(ans, "\n");
    }	
}	
int main(int argc, char *argv[])
{

    FILE *words, *ans, *query;

    int sizeOfIndex = atoi(argv[2]);
    words = fopen(argv[1], "r");
    query = fopen(argv[3], "r");
    ans = fopen("anagrams.txt", "w");

    list *a[sizeOfIndex];
    int i;

    for (i = 0; i < sizeOfIndex; i++)
    {

        a[i] = NULL; 
    }

    char ch[100];
    while (fscanf(words, "%s ", &ch) != EOF)
    {
        int num;
        num = findascii(ch);
        addword(ch, &a[num % sizeOfIndex]);
    }
    fclose(words);

    for (i = 0; i < 1000; i++)
    {
        list *temp = a[i];
        while (temp != NULL)
        {

            temp = temp->next;
        }
    }

    while (fscanf(query, "%s ", &ch) != EOF)
    {
        int num;
        num = findascii(ch);
        num = num % sizeOfIndex;
        printanagram(ans, ch, &a[num]);
    }
    fclose(query);
}
