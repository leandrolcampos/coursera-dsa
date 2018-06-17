/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Maximum Value of the Loot Problem
 */

#include <stdio.h>
#include <stdlib.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

typedef struct item
{
    unsigned int value;
    unsigned int weight;
} item;

int item_comparison(const item *, const item *);
double optimal_value(unsigned int, const item *, unsigned int);

int main()
{
    unsigned short n; /* number of items */ 
    unsigned int W; /* capacity */
    item *items;
    
    scanf("%hu %u", &n, &W);
    items = malloc(n * sizeof(item));
    for (unsigned short i = 0; i < n; i++)
        scanf("%u %u", &(items[i].value), &(items[i].weight));
    printf("%.4lf\n", optimal_value(W, items, n));
    free(items);
    return 0;
}

/*
 * item_comparison: return < 0 if the value per weight of item1 is less than the value per
 * weight of item2; 0 if is equal; and > 0 if is greater.
 */
int item_comparison(const item *item1, const item *item2)
{
    return (item1->value * item2->weight) - (item2->value * item1->weight);
}

/*
 * optimal_value: find the most valuable combination of items, where 1 <= nitems <= 10^3,
 * 0 <= capacity <= 2*10^6, 0 <= items[i].value <= 2*10^6, 0 <= items[i].weight <= 2*10^6,
 * and 0 <= i <= nitems - 1.
 */
double optimal_value(unsigned int capacity, const item *items, unsigned int nitems)
{
    const item *c_item;
    unsigned int weight;
    double total;

    qsort((void *)items, nitems, sizeof(item), 
          (int (*)(const void *, const void *))item_comparison);
    c_item = &items[nitems];
    total = 0.0;
    while (capacity && c_item-- - items)
    {
        weight = min(capacity, c_item->weight);
        total += (double)c_item->value / c_item->weight * weight;
        capacity -= weight;
    }
    return total;
}