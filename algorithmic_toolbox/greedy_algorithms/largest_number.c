/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Maximum Salary Problem
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS_PER_INT 4 /* 1 <= i <= 1000 for all integers i */
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef char *string;

void largest_number(const string *, unsigned char, string);

int main()
{
    unsigned short n; /* number of integers */
    string number, *numbers;
    unsigned int i;

    scanf("%hu", &n);
    number = malloc((n * MAX_DIGITS_PER_INT + 1) * sizeof(char));
    numbers = malloc(n * sizeof(string));
    for (i = 0; i < n; i++)
    {
        numbers[i] = malloc((MAX_DIGITS_PER_INT + 1) * sizeof(char));
        scanf("%s", numbers[i]);
    }
    largest_number(numbers, n, number);
    printf("%s\n", number);
    for (i = 0; i < n; i++)
    {
        free(numbers[i]); /* free the memory of each string in the array */
    }
    free(numbers); /* free the memory of the array */
    free(number);
    return 0;
}

/*
 * string_comparison: return -1 if s1 + s2 < s2 + s1; 0 if s1 + s2 == s2 + s1; and 1 if s1 + s2 >
 * s2 + s1. The operation str1 + str2 concatenates str1 and str2.
 */
int string_comparison(const string *s1, const string *s2)
{
    char str1[MAX_DIGITS_PER_INT * 2 + 1], str2[MAX_DIGITS_PER_INT * 2 + 1];

    strcpy(str1, *s1);
    strcat(str1, *s2);
    strcpy(str2, *s2);
    strcat(str2, *s1);
    return strcmp(str1, str2);
}

/*
 * largest_number: find the largest number that can be composed out of numbers[0], ..., numbers[nel - 1].
 * Number must point to memory block large enough to store the function return.
 */
void largest_number(const string *numbers, unsigned char nel, string number)
{
    string current_number;

    qsort((void *)numbers, nel, sizeof(string),
          (int (*)(const void *, const void *))string_comparison);
    numbers = &numbers[nel];
    while (nel--)
    {
        current_number = *--numbers;
        while (*current_number)
            *number++ = *current_number++;
    }
    *number = '\0';
}