/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Binary Search Problem
 */

#include <stdio.h>
#include <stdlib.h>

long binary_search(unsigned int *, unsigned int, unsigned int, unsigned int);

int main()
{
    unsigned int i;
    unsigned int n, k;
    unsigned int *base, *keys;

    scanf("%u", &n);
    base = malloc(n * sizeof(unsigned int));
    for (i = 0; i < n; i++)
        scanf("%u", &base[i]);
    scanf("%u", &k);
    keys = malloc(k * sizeof(unsigned int));
    for (i = 0; i < k; i++)
        scanf("%u", &keys[i]);
    for (i = 0; i < k; i++)
        printf("%d ", binary_search(base, 0, n - 1, keys[i]));
    putchar('\n');
    free(base);
    free(keys);
    return 0;
}

/*
 * binary_search: returns an index _low <= j <= _high such that base[j] == key or −1 if 
 * there is no such index.
 */
long binary_search(unsigned int *base,
                   unsigned int _low, unsigned int _high, unsigned int key)
{
    long low, mid, high;

    low = _low;
    high = _high;
    while (low <= high)
    {
        mid = (high + low) / 2;
        if (key == base[mid])
            return mid;
        else if (key < base[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}