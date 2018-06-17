/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Collecting Signatures Problem
 */

#include <stdio.h>
#include <stdlib.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

typedef struct interval
{
    unsigned int a;
    unsigned int b;
} interval;

int interval_comparison(const interval *, const interval *);
unsigned int intersection(interval, interval, interval *);
unsigned int optimal_points(const interval *, unsigned char, unsigned int *);

int main()
{
    unsigned char n; /* number of intervals */ 
    interval *intervals;
    unsigned int *points;
    unsigned int n_points;
    unsigned char i;
    
    scanf("%hhu", &n);
    intervals = malloc(n * sizeof(interval));
    points = malloc(n * sizeof(unsigned int));
    for (i = 0; i < n; i++)
        scanf("%u %u", &(intervals[i].a), &(intervals[i].b));
    n_points = optimal_points(intervals, n, points);
    printf("%u\n", n_points);
    for (i = 0; i < n_points; i++)
        printf("%u ", points[i]);
    printf("\n");
    free(intervals);
    free(points);
    return 0;
}

/*
 * interval_comparison: return -1 if the lower end of i is smaller than the lower end of j; 
 * 0 if they are equal; and 1 if it is larger.
 */
int interval_comparison(const interval *i, const interval *j)
{
    return i->a - j->a;
}

/*
 * intersection: return the intersection between the intervals i and j, assuming that the  
 * lower end of i is smaller than or equal to the lower end of j.
 */
unsigned int intersection(interval i, interval j, interval *k)
{
    if (i.b < j.a)
        return 0;
    k->a = j.a;
    k->b = min(i.b, j.b);
    return 1;
}

/*
 * optimal_points: find a set of integers, points, of the minimum size such that, for any interval [a, b],
 * there is a point x in points such that a <= x <= b. The return value of this function is the number of
 * points x. The size of the array points has to be enough to contain all points x.
 */
unsigned int optimal_points(const interval *intervals, unsigned char nintervals, unsigned int *points)
{
    const interval *current_interval, *next_interval, *last_interval;
    unsigned int n_points;
    interval k;

    qsort((void *)intervals, nintervals, sizeof(interval), 
          (int (*)(const void *, const void *))interval_comparison);
    current_interval = &intervals[0];
    next_interval = current_interval + 1;
    last_interval = &intervals[nintervals - 1];
    n_points = 0;
    while (current_interval <= last_interval)
    {
        k = *current_interval;
        while (next_interval <= last_interval && intersection(k, *next_interval, &k))
            next_interval++;
        current_interval = next_interval++;
        n_points++;
        *points++ = k.b;
    }
    return n_points;
}