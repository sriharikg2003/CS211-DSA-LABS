/*
Author - Srihari K G
Roll-Number - 210030035
Computer Science and Engineering
Indian Institute of Technology Dharwad
*/

#include <stdio.h>
#include <stdlib.h>
// #include <math.h>

int counter = 1;

int mypower(int i, int z); // user defined function to calculate power

void countingsort(int arrays[], int no_of_digits, int size_of_given_array)

{
    int z;

    int *digit_array = malloc(size_of_given_array * sizeof(int));

    for (z = 0; z < size_of_given_array; z++)
    {
        digit_array[z] = (arrays[z] / mypower(10, counter - 1)) % mypower(10, 1);
    }

    int digit_count[10];

    int var;
    for (var = 0; var < 10; var++)
        digit_count[var] = 0;

    for (z = 0; z < size_of_given_array; z++)
        digit_count[digit_array[z]] += 1;

    for (var = 1; var < 10; var++)
        digit_count[var] += digit_count[var - 1];

    int *auxi_array = malloc(size_of_given_array * sizeof(int));

    for (var = 0; var < size_of_given_array; var++)
        auxi_array[var] = -1;

    for (z = size_of_given_array - 1; z >= 0; z--)
    {
        auxi_array[digit_count[digit_array[z]] - 1] = arrays[z]; // temporary array
        digit_count[digit_array[z]]--;
    }

    for (z = 0; z < size_of_given_array; z++)
        arrays[z] = auxi_array[z];

    free(auxi_array);

    counter++; // associated with number of digits to calculate digit using modulus
}

void radixsort(int arrays[], int digit, int size_of_given_array)
{
    int i;
    for (i = 1; i <= digit; i++)
        countingsort(arrays, i, size_of_given_array);
}

int main(int argc, char *argv[])

{

    FILE *opened_file; // open read and write files
    FILE *write_files;

    int digit;

    digit = atoi(argv[2]);

    opened_file = fopen(argv[1], "r");

    write_files = fopen("radix.txt", "w");

    int size_of_given_array = 0;

    int num;
    while (fscanf(opened_file, "%d", &num) != EOF)
    {
        size_of_given_array++;
    }

    rewind(opened_file);

    int *arrays;
    arrays = (int *)malloc(size_of_given_array * sizeof(int)); // dynammic creation of array

    int i = 0;
    while (fscanf(opened_file, "%d", &num) != EOF)
    {

        arrays[i] = num;
        i++;
    }

    rewind(opened_file);

    radixsort(arrays, digit, size_of_given_array);

    for (i = 0; i < size_of_given_array; i++)
        fprintf(write_files, "%d\n", arrays[i]);

    free(arrays);

    fclose(opened_file); // closing files

    fclose(write_files);
}

int mypower(int base, int expo)
{
    if (expo == 0)
        return 1;

    else
        return base * mypower(base, expo - 1);
}