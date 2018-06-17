/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Improving Quick Sort Problem
 */

#include <stdlib.h>
#include <stdio.h>

void 
quick_sort(unsigned int *, unsigned int *);
void
partition(unsigned int *, unsigned int *, unsigned int **, unsigned int **);
void
swap(unsigned int *, unsigned int *);
void
print(unsigned int *, unsigned int *);

int
main()
{
    unsigned int n;
    unsigned int *base;
    unsigned int i;

    srand(0);
    scanf("%u", &n);
    base = malloc(n * sizeof(unsigned int));
    for (i = 0; i < n; i++)
        scanf("%u", &base[i]);
    quick_sort(&base[0], &base[n - 1]);
    print(&base[0], &base[n - 1]);
    return 0;
}

/*
 * quick_sort: sorts the sequence of integers *left, ..., *right in a non-decreasing order.
 */
void 
quick_sort(unsigned int *left, unsigned int *right)
{
    unsigned long k;
    unsigned int *last_smaller, *first_larger;

    if (left >= right)
        return;
    k = (unsigned long)rand() % (right - left);
    swap(left, left + k);
    partition(left, right, &last_smaller, &first_larger);
    quick_sort(left, last_smaller);
    quick_sort(first_larger, right);
}

/*
 * partition: partitions the sequence *left, ..., *right into three parts: < *left,
 * = *left, and > *left. And it returns, through *last_smaller and *first_larger, 
 * the address of the last integer of the first part and the address of the first 
 * integer of the third part.
 */
void
partition(unsigned int *left, unsigned int *right, unsigned int **last_smaller, 
          unsigned int **first_larger)
{
    unsigned int *current_element;

    *last_smaller = *first_larger = current_element = left;
    while (++current_element <= right)
    {
        if (*current_element < *left)
        {
            ++(*last_smaller);
            ++(*first_larger);
            swap(*first_larger, current_element);
            swap(*last_smaller, *first_larger);
        }
        else if(*current_element == *left)
        {
            ++(*first_larger);
            swap(*first_larger, current_element);
        }
    }
    swap(left, *last_smaller);
    --(*last_smaller);
    ++(*first_larger);
}

/*
 * swap: swaps the value of n1 and n2.
 */
void
swap(unsigned int *n1, unsigned int *n2)
{
    unsigned int tmp;

    tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}

/*
 * print: prints the sequence of integers *left, ..., *right.
 */
void
print(unsigned int *left, unsigned int *right)
{
    while (left <= right)
        printf("%u ", *left++);
    putchar('\n');
}