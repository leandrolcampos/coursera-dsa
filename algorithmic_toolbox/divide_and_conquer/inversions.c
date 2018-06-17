/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Number of Inversions Problem
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h> /* it's needed because of memcpy */

#define NAIVE_SOLUTION

unsigned long long
merge_sort(const unsigned int *, const unsigned int *);
unsigned long long
merge(const unsigned int *, const unsigned int *, const unsigned int *);
void stress_test(unsigned int);

int main()
{
#ifdef STRESS_TEST
    stress_test(3);
#else
    unsigned int n;
    unsigned int *base;
    unsigned int i;
#if defined(NAIVE_SOLUTION)
    unsigned int j;
#endif
    unsigned long long inversions;

    scanf("%u", &n);
    base = malloc(n * sizeof(unsigned int));
    for (i = 0; i < n; i++)
        scanf("%u", &base[i]);
#if defined(NAIVE_SOLUTION)
    inversions = 0;
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            if (base[i] > base[j])
                inversions++;
#else
    inversions = merge_sort(&base[0], &base[n - 1]);
#endif
    printf("%llu\n", inversions);
    free(base);
#endif
    return 0;
}

/*
 * merge_sort: sorts the sequence of integers *left, ..., *right in a non-decreasing order
 * and returns the number of inversions needed to order the sequence.
 */
unsigned long long
merge_sort(const unsigned int *left, const unsigned int *right)
{
    const unsigned int *middle;
    unsigned long long inversion;

    inversion = 0;
    if (left < right)
    {
        middle = left + (right - left) / 2;
        inversion += merge_sort(left, middle);
        inversion += merge_sort(middle + 1, right);
        inversion += merge(left, middle, right);
    }
    return inversion;
}

/*
 * merge: merges two ordered sequences, *left <= ...<= *middle and *(middle + 1) <= ...<= *right, 
 * into another ordered sequence *left <= ...<= *right.
 */
unsigned long long
merge(const unsigned int *left, const unsigned int *middle, const unsigned int *right)
{
    unsigned long long inversions;
    unsigned int *lt, *mid, *rt;
    unsigned int *el;
    unsigned int tmp;

    inversions = 0;
    lt = (unsigned int *)left;
    mid = (unsigned int *)middle;
    rt = mid + 1;
    if (*mid == *rt)
        return 0;
    while (lt <= mid && rt <= right)
    {
        if (*lt <= *rt)
        {
            lt++;
        }
        else
        {
            inversions += rt - lt;
            tmp = *rt;
            memcpy(lt + 1, lt, (rt - lt) * sizeof(unsigned int));
            *lt = tmp;
            lt++, mid++, rt++;
        }
    }
    return inversions;
}

/*
 * stress_test: proves that the solution implemented with a naive solution.
 */
#define MAX_ITER 100
#define MIN_SEQUENCE_SIZE 1          /* 1 */
#define MAX_SEQUENCE_SIZE 100000     /* 100000 */
#define MIN_INTEGER_VALUE 1          /* 1 */
#define MAX_INTEGER_VALUE 1000000000 /* 1000000000 */
void stress_test(unsigned int seed)
{
    unsigned int n;
    unsigned int *base;
    unsigned int iter, i, j;
    unsigned long long r_inversions, t_inversions;

    srand(seed);
    iter = 0;
    while (iter < MAX_ITER)
    {
        printf("test %u\n", iter + 1);
        n = rand() % (MAX_SEQUENCE_SIZE - MIN_SEQUENCE_SIZE) + MIN_SEQUENCE_SIZE;
        base = malloc(n * sizeof(unsigned int));
        for (i = 0; i < n; i++)
            base[i] = rand() % (MAX_INTEGER_VALUE - MIN_INTEGER_VALUE) + MIN_INTEGER_VALUE;
        t_inversions = 0;
        for (i = 0; i < n; i++)
            for (j = i + 1; j < n; j++)
                if (base[i] > base[j])
                    t_inversions++;
        r_inversions = merge_sort(&base[0], &base[n - 1]);
        if (r_inversions == t_inversions)
        {
            printf("ok!\n");
            printf("result = %llu\n", r_inversions);
            printf("test = %llu\n", t_inversions);
        }
        else
        {
            printf("error!\n");
            for (i = 0; i < n; i++)
                printf("%u ", base[i]);
            printf("\nresult = %llu\n", r_inversions);
            printf("test = %llu\n", t_inversions);
            break;
        }
        free(base);
        iter++;
        putchar('\n');
    }
}