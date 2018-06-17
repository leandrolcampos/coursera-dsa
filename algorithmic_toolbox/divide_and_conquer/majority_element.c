/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Majority Element Problem
 */

#include <stdio.h>
#include <stdlib.h>

const unsigned int *
majority_element_naive(const unsigned int *, const unsigned int *);
const unsigned int *
majority_element(const unsigned int *, const unsigned int *, unsigned int *);
unsigned int 
count(const unsigned int *, const unsigned int *, const unsigned int *);

int main()
{
    unsigned int n;
    unsigned int *base;
    unsigned int i;
    unsigned int frequency;

    scanf("%u", &n);
    base = malloc(n * sizeof(unsigned int));
    for (i = 0; i < n; i++)
        scanf("%u", &base[i]);
    frequency = 0;
    if (majority_element(&base[0], &base[n - 1], &frequency) == NULL)
        printf("%u\n", 0);
    else
        printf("%u\n", 1);
    free(base);
    return 0;
}

/*
 * majority_element_naive: checks whether the sequence of n elements *left, ..., *right 
 * contains an element that appears more than n/2 times. If it contains, the function will 
 * return a pointer to an instance of this element. Otherwise, the function will return NULL.
 */
const unsigned int *
majority_element_naive(const unsigned int *left, const unsigned int *right)
{
    unsigned int *current_element;
    unsigned int frequency;

    current_element = (unsigned int *)left;
    while (current_element <= right)
    {
        frequency = count(current_element, left, right);
        if (frequency > (right - left + 1) / 2)
            return current_element;
        current_element++;
    }
    return NULL;
}

/*
 * majority_element: checks whether the sequence of n elements *left, ..., *right contains 
 * an element that appears more than n/2 times. If it contains, the function will return 
 * a pointer to an instance of this element and store in *frequency the number of times that 
 * this element appears. Otherwise, the function will return NULL and store 0 in *frequency.
 */
const unsigned int *
majority_element(const unsigned int *left, const unsigned int *right, unsigned int *frequency)
{
    const unsigned int *mid;
    unsigned int frequency1, frequency2;
    const unsigned int *el1, *el2;

    *frequency = 0;
    if (left > right)
        return NULL;
    else if (left == right)
    {
        *frequency = 1;
        return left;
    }
    else
    {
        mid = left + (right - left) / 2;
        el1 = majority_element(left, mid, &frequency1);
        if (el1 != NULL)
            *frequency = frequency1 + count(el1, mid + 1, right);
        if (*frequency > (right - left + 1) / 2)
            return el1;
        el2 = majority_element(mid + 1, right, &frequency2);
        if (el2 != NULL)
            *frequency = frequency2 + count(el2, left, mid);
        if (*frequency > (right - left + 1) / 2)
            return el2;
        *frequency = 0;
        return NULL;
    }
}

/*
 * count: returns the number of times that *el appears in the sequence of n elements *left, 
 * ..., *right. 
 */
unsigned int 
count(const unsigned int *el, const unsigned int *left, const unsigned int *right)
{
    unsigned int *current_element;
    unsigned int count;

    current_element = (unsigned int *)left;
    count = 0;
    while (current_element <= right)
        if (*el == *current_element++)
            count++;
    return count;
}