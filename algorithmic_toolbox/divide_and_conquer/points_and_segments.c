/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Organizing a Lottery Problem
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct point
{
    long value;
    unsigned int position;
    unsigned int segments;
} point;

typedef struct segment
{
    long left;
    long right;
} segment;

int compare_by_value(const point *, const point *);
int compare_by_position(const point *, const point *);
void sort_by_value(point *, point *);
void sort_by_position(point *, point *);
int contain(const segment *, const point *);
void
count(const segment *, const segment *, point *, point *);

int main()
{
    unsigned int s; /* number of segments */
    unsigned int p; /* number of points */
    segment *first_s, *current_s, *last_s;
    point *first_p, *current_p, *last_p;
    unsigned int position;

    scanf("%u", &s);
    scanf("%u", &p);
    current_s = first_s = malloc(s * sizeof(segment));
    last_s = first_s + s - 1;
    while (current_s <= last_s)
    {
        scanf("%ld", &(current_s->left));
        scanf("%ld", &(current_s->right));
        current_s++;
    }
    current_p = first_p = malloc(p * sizeof(point));
    last_p = first_p + p - 1;
    position = 0;
    while (current_p <= last_p)
    {
        scanf("%ld", &(current_p->value));
        current_p->position = position++;
        current_p++;
    }
    sort_by_value(first_p, last_p);
    count(first_s, last_s, first_p, last_p);
    sort_by_position(first_p, last_p);
    current_p = first_p;
    while (current_p <= last_p)
    {
        printf("%u ", current_p->segments);
        current_p++;
    }
    putchar('\n');
    free(first_s);
    free(first_p);
    return 0;
}

/*
 * count: counts how many segments of the sequence *left_s <= ... <= *right_s contains 
 * each point of the sequence *left_p <= ... <= *right_p.
 */
void
count(const segment *left_s, const segment *right_s, point *left_p, point *right_p)
{
    point *p1, *p2;

    p1 = left_p;
    while (p1 <= right_p)
    {
        p1->segments = 0;
        p1++;
    }
    while (left_s <= right_s)
    {
        p1 = bsearch(left_s, left_p, right_p - left_p + 1, sizeof(point),
                     (int (*)(const void *, const void *))contain);
        if (p1 != NULL)
        {
            p1->segments++;
            p2 = p1;
            while (--p2 >= left_p)
            {
                if (contain(left_s, p2) == 0)
                    p2->segments++;
                else
                    break;
            }
            p2 = p1;
            while (++p2 <= right_p)
            {
                if (contain(left_s, p2) == 0)
                    p2->segments++;
                else
                    break;
            }
        }
        left_s++;
    }
}

/*
 * contain: checks if segment *s contains the point *p.
 */
int contain(const segment *s, const point *p)
{
    if (p->value < s->left)
        return 1;
    else if (p->value > s->right)
        return -1;
    else
        return 0;
}

/*
 * sort_by_value: sorts the sequence *left <= ... <= *right by the value of each point.
 */
void sort_by_value(point *left, point *right)
{
    qsort(left, right - left + 1, sizeof(point),
          (int (*)(const void *, const void *))compare_by_value);
}

/*
 * sort_by_position: sorts the sequence *left <= ... <= *right by the position of each point.
 */
void sort_by_position(point *left, point *right)
{
    qsort(left, right - left + 1, sizeof(point),
          (int (*)(const void *, const void *))compare_by_position);
}

/*
 * compare_by_value: compares two points by their values.
 */
int compare_by_value(const point *p1, const point *p2)
{
    if (p1->value < p2->value)
        return -1;
    else if (p1->value == p2->value)
        return 0;
    else
        return 1;
}

/*
 * compare_by_position: compares two points by their positions.
 */
int compare_by_position(const point *p1, const point *p2)
{
    if (p1->position < p2->position)
        return -1;
    else if (p1->position == p2->position)
        return 0;
    else
        return 1;
}