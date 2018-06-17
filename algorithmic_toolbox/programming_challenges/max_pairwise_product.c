/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Maximum Pairwise Product Problem
 */

#include <stdlib.h>
#include <stdio.h>

#define MAX_TEST_ITER 1000 // Number of random cases in the stress test (> 0)
#define MAX_N 200          // Maximum length of each sequence in the stress test (<= 2 * 10^5)
#define MIN_N 2            // Minimum length of each sequence in the stress test (>= 2)
#define MAX_A 200000       // Maximum value of each element of a sequence in the stress test (<= 2 * 10^5)
#define MIN_A 0            // Minimum value of each element of a sequence in the stress test (>= 0)

unsigned long max_pairwise_product(unsigned long *, unsigned long);
unsigned long fast_max_pairwise_product(unsigned long *, unsigned long);
void stress_test(unsigned int);

int main()
{
    unsigned long i, n, *u, *v;

    scanf("%lu", &n);
    u = v = (unsigned long *)malloc(n * sizeof(unsigned long));
    for (i = 0; i < n; i++)
        scanf("%lu", v++);
    printf("%lu\n", fast_max_pairwise_product(u, n));
    free(u);
    return 0;
}

// max_pairwise_product: calculate the maximum pairwise product v[i] * v[j],
// where i != j and i, j < n
unsigned long max_pairwise_product(unsigned long *v, unsigned long n)
{
    unsigned long max_product, product, *u, *w;

    max_product = 0lu;
    w = v + n;       // w = v[n]
    for (; --n; v++) // v[0], ..., v[n-2]
        for (u = v + 1; u < w; u++)
            if (max_product < (product = *v * *u))
                max_product = product;
    return max_product;
}

// fast_max_pairwise_product: calculate the maximum pairwise product v[i] * v[j],
// where i != j and i, j < n
unsigned long fast_max_pairwise_product(unsigned long *v, unsigned long n)
{
    unsigned long largest, second_largest;

    largest = second_largest = 0lu;
    for (; n--; v++)
        if (second_largest < *v)
        {
            if (largest < *v)
            {
                second_largest = largest;
                largest = *v;
            }
            else
                second_largest = *v;
        }
    return largest * second_largest;
}

// stress_test: compare the results of max_pairwise_product and fast_max_pairwise_product
// in MAX_TEST_ITER random cases
void stress_test(unsigned int seed)
{
    unsigned long i, m, n, *u, *v, result1, result2;

    srand(seed);
    u = (unsigned long *)malloc(MAX_N * sizeof(unsigned long));
    i = 0lu;
    while (i++ < MAX_TEST_ITER)
    {
        m = n = rand() % MAX_N + MIN_N;
        v = u;
        for (; n--; v++)
        {
            *v = rand() % MAX_A + MIN_A;
            printf("%lu ", *v);
        }
        putchar('\n');
        result1 = max_pairwise_product(u, m);
        result2 = fast_max_pairwise_product(u, m);
        printf("result1 = %lu, result2 = %lu\n", result1, result2);
        if (result1 != result2)
            break;
    }
    free(u);
}