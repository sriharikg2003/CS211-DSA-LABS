/*
Author : Srihari  K G
Roll Number : 210030035
Indian Institute of Technology Dharwad
Computer Science and Engineering
*/


#include <stdlib.h>

#include <stdio.h>

void mergeLeftRight(int left[], int left_Index, int right[], int right_Index, int array_name[],FILE  *write_file);

void mergesort(int array_name[], int n,FILE  *write_file);



int main(int argc, char *argv[])

{

    FILE *read_file;  //read file

    FILE  *write_file;   //write file

    read_file = fopen(argv[1], "r");   // reading input file
 
    write_file = fopen("mergesort.txt", "w");  //creating output file

    int Number_of_elements = 0;

    int num;


    while (fscanf(read_file, "%d", &num) != EOF) 
    {
        Number_of_elements++;
    }

    rewind(read_file);

    int *array_name;


    array_name = (int *)malloc(Number_of_elements * sizeof(int));   //dynamically allocating memory for array

    int i = 0;

    while (fscanf(read_file, "%d", &num) != EOF)
    {

        array_name[i] = num;
        i++;
    }

    rewind(read_file);    // brings back the file pointer to the initial poition

    mergesort(array_name, Number_of_elements,write_file);  //calls mergesort function

    for (i = 0; i < Number_of_elements; i++)
        fprintf(write_file, "%d\n", array_name[i]);  //writing the sorted array into file
   
    fclose(write_file);
  //closing files
    fclose(read_file);
}




void mergesort(int array_name[], int n,FILE  *write_file)  // divides the array recursively into 2 parts and calls to merge them
{

    int var;
    if (n == 1)
        return;

    int left[n / 2], right[n - n / 2];

    for (var = 0; var < n / 2; var++)
        left[var] = array_name[var];

    for (var = 0; var < n - n / 2; var++)
        right[var] = array_name[var + n / 2];

    mergesort(left, n / 2,write_file);

    mergesort(right, n - n / 2,write_file);

    mergeLeftRight(left, n / 2, right, n - n / 2, array_name,write_file);
}


void mergeLeftRight(int left[], int left_Index, int right[], int right_Index, int array_name[],FILE  *write_file) //merges the left and right array
{
    int counter;
  
    int left_Variable = 0, right_Variable = 0;
   
    for (counter = 0; counter < right_Index + left_Index  ; counter++)
    {
        if ( right_Variable < right_Index  && left_Variable < left_Index )
        {
            if (left[left_Variable] < right[right_Variable])
            {
                array_name[counter] = left[left_Variable];

                left_Variable = left_Variable + 1;
            }
            else
            {
                array_name[counter] = right[right_Variable];


                right_Variable = right_Variable + 1;
            }
        }
        else if (left_Variable < left_Index)
        {
            array_name[counter] = left[left_Variable];

            left_Variable = left_Variable + 1;
        }
        else
        {
            array_name[counter] = right[right_Variable];

            right_Variable = right_Variable + 1;
        }
    }
}

