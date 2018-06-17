/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Maximum Advertisement Revenue Problem
 */

#include <stdio.h>
#include <stdlib.h>

int intcmp(const int *, const int *);
long max_revenue(const int *, const int *, unsigned short, unsigned short);

int main()
{
    unsigned short n; /* number of ads and slots */ 
    int *ads, *slots;
    unsigned int i;
    
    scanf("%hu", &n);
    ads = malloc(n * sizeof(int));
    slots = malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        scanf("%d", &ads[i]);
    for (i = 0; i < n; i++)
        scanf("%d", &slots[i]);
    printf("%ld\n", max_revenue(ads, slots, n, n));
    free(ads);
    free(slots);
    return 0;
}

/*
 * intcmp: return < 0 if the a is less than b; 0 if a is equal to b;
 * and > 0 if a is greater than b.
 */
int intcmp(const int *a, const int *b)
{
    return *a - *b;
}

/*
 * max_revenue: calculate the maximum value of c[0] + ... + c[m - 1], where c[i] = ads[k] * slots[l],
 * -10^5 <= ads[k], slots[l] <= 10^5, 0 <= k < nads, 0 <= l < nslots, and 0 <= nads, nslots <= 10^3.
 */
long max_revenue(const int *ads, const int *slots, unsigned short nads, unsigned short nslots)
{
    long revenue;

    qsort((void *)ads, nads, sizeof(int),
          (int (*)(const void *, const void *))intcmp);
    qsort((void *)slots, nslots, sizeof(int),
          (int (*)(const void *, const void *))intcmp);
    revenue = 0;
    while (nads-- && nslots--)
        revenue += (long)*ads++ * *slots++;
    return revenue;
}