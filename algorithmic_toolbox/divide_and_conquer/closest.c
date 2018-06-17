/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Closest Points Problem
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>

typedef struct point
{
    double x;
    double y;
} point;

#define min(a, b) ((a) < (b) ? (a) : (b))
#define MAX_DIST UINT_MAX

double
minimal_distance(const point *, const point *);
const point *
middle_range(const point *, const point *, const point *, double,
             unsigned int *);
double
minimal_distance_naive(const point *, const point *);
double
distance(const point *, const point *);
void sort_by_x(point *, const point *);
int compare_by_x(const point *, const point *);
void sort_by_y(point *, const point *);
int compare_by_y(const point *, const point *);
void scan(point *, point *);
void print(const point *, const point *);
void stress_test(unsigned int);

int main()
{
#if defined(STRESS_TEST)
    stress_test(0);
#else
    unsigned long n;
    point *points;
    double dist;

    scanf("%lu", &n);
    points = malloc(n * sizeof(point));
    scan(&points[0], &points[n - 1]);
    sort_by_x(&points[0], &points[n - 1]);
    dist = minimal_distance(&points[0], &points[n - 1]);
    printf("%.6lf\n", dist);
    free(points);
    return 0;
#endif
}

/*
 * minimal_distance: finds the smallest distance between a pair of two points 
 * of the sequence *left <= ... <= *right.
 */
double
minimal_distance(const point *left, const point *right)
{
    const point *middle, *lower_middle, *upper_middle, *p1, *p2;
    double dist, dist_lt, dist_rt, dist_mid;
    unsigned int nel;

    if (right - left < 1)
        return MAX_DIST;
    if (right - left == 1)
        return distance(left, right);
    middle = left + (right - left) / 2;
    dist_lt = minimal_distance(left, middle);
    dist_rt = minimal_distance(middle + 1, right);
    dist = min(dist_lt, dist_rt);
    /* checks whether there exist points in the left and the right side such that 
    the distance between them is smaller than dist */
    lower_middle = middle_range(left, right, middle, dist, &nel);
    if (nel > 1)
    {
        upper_middle = lower_middle + nel - 1;
        sort_by_y((point *)lower_middle, (point *)upper_middle);
        p1 = lower_middle;
        while (p1 < upper_middle)
        {
            p2 = p1 + 1;
            while (p2 <= upper_middle && (p2 - p1) <= 7)
            {
                dist_mid = distance(p1, p2);
                if (dist_mid < dist)
                    dist = dist_mid;
                p2++;
            }
            p1++;
        }
        sort_by_x((point *)lower_middle, (point *)upper_middle);
    }
    return dist;
}



/*
 * middle_range: returns a pointer to the left endpoint of the sequence (middle->x - radius)
 * <= *middle_range <= ... <= (*middle_range + *nel - 1) <=  (middle->x + radius).
 */
const point *
middle_range(const point *left, const point *right, const point *middle, double radius,
             unsigned int *nel)
{
    const point *p;
    double lt_endpoint, rt_endpoint;

    lt_endpoint = middle->x - radius;
    rt_endpoint = middle->x + radius;
    while (middle > left)
        if ((middle - 1)->x >= lt_endpoint)
            middle--;
        else
            break;
    p = middle;
    while (p < right)
        if ((p + 1)->x <= rt_endpoint)
            p++;
        else
            break;
    *nel = p - middle + 1;
    return middle;
}

double
minimal_distance_naive(const point *left, const point *right)
{
    const point *p1, *p2;
    double dist, tmp;

    if (right - left < 1)
        return MAX_DIST;
    if (right - left == 1)
        return distance(left, right);
    dist = MAX_DIST;
    p1 = left;
    while (p1 <= right)
    {
        p2 = left;
        while (p2 <= right)
        {
            if (p1 != p2)
            {
                tmp = distance(p1, p2);
                if (tmp < dist)
                    dist = tmp;
            }
            p2++;
        }
        p1++;
    }
    return dist;
}

double
distance(const point *a, const point *b)
{
    return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
}

void sort_by_x(point *left, const point *right)
{
    qsort(left, right - left + 1, sizeof(point),
          (int (*)(const void *, const void *))compare_by_x);
}

int compare_by_x(const point *a, const point *b)
{
    if (a->x < b->x)
        return -1;
    else if (a->x == b->x)
        return 0;
    else
        return 1;
}

void sort_by_y(point *left, const point *right)
{
    qsort(left, right - left + 1, sizeof(point),
          (int (*)(const void *, const void *))compare_by_y);
}

int compare_by_y(const point *a, const point *b)
{
    if (a->y < b->y)
        return -1;
    else if (a->y == b->y)
        return 0;
    else
        return 1;
}

void scan(point *left, point *right)
{
    while (left <= right)
    {
        scanf("%lf %lf", &(left->x), &(left->y));
        left++;
    }
}

void print(const point *left, const point *right)
{
    while (left <= right)
    {
        printf("(%.0lf, %.0lf)\n", left->x, left->y);
        left++;
    }
}

#if defined(STRESS_TEST)
/*
 * stress_test: proves that the solution implemented with a naive solution.
 */
#define MAX_ITER 100000
#define MIN_SEQUENCE_SIZE 2   /* 1 */
#define MAX_SEQUENCE_SIZE 10  /* 100000 */
#define MIN_INTEGER_VALUE -10 /* 1 */
#define MAX_INTEGER_VALUE 10  /* 1000000000 */
void stress_test(unsigned int seed)
{
    unsigned int n;
    point *base;
    unsigned int iter, i, j;
    double r_dist, t_dist;

    srand(seed);
    iter = 0;
    while (iter < MAX_ITER)
    {
        printf("test %u\n", iter + 1);
        n = rand() % (MAX_SEQUENCE_SIZE - MIN_SEQUENCE_SIZE) + MIN_SEQUENCE_SIZE;
        base = malloc(n * sizeof(point));
        for (i = 0; i < n; i++)
        {
            base[i].x = rand() % (MAX_INTEGER_VALUE - MIN_INTEGER_VALUE) + MIN_INTEGER_VALUE;
            base[i].y = rand() % (MAX_INTEGER_VALUE - MIN_INTEGER_VALUE) + MIN_INTEGER_VALUE;
        }
        t_dist = minimal_distance_naive(&base[0], &base[n - 1]);
        sort_by_x(&base[0], &base[n - 1]);
        r_dist = minimal_distance(&base[0], &base[n - 1]);
        if (fabs(r_dist - t_dist) <= pow(10, -3))
        {
            printf("ok!\n");
            printf("result = %.6lf\n", r_dist);
            printf("test = %.6lf\n", t_dist);
        }
        else
        {
            printf("error!\n");
            print(&base[0], &base[n - 1]);
            printf("\nresult = %.6lf\n", r_dist);
            printf("test = %.6lf\n", t_dist);
            break;
        }
        free(base);
        iter++;
        putchar('\n');
    }
}
#endif