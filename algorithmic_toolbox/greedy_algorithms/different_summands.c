/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Maximum Number of Prizes Problem
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

unsigned int quadratic(double, double, double, double *, double *);
unsigned int optimal_summands(unsigned int);
void print_summands(unsigned int, unsigned int);

int main()
{
    unsigned int total, k;

    scanf("%u", &total);
    k = optimal_summands(total);
    printf("%u\n", k);
    print_summands(total, k);
    return 0;
}

/*
 * quadratic: solve the equation ax^2 + bx + c = 0. If there is no solution, the function 
 * returns 0. If there is only one solution, the function returns 1 and stores the solution
 * in x1. If there is two solutions, the function returns 2 and stores the solutions in x1
 * and x2, where x1 > x2.
 */
unsigned int quadratic(double a, double b, double c, double *x1, double *x2)
{
    double d, y, _x1, _x2;

    d = b * b - 4 * a * c;
    if (d < 0.0)
        return 0;
    y = sqrt(d);
    if (b < 0.0)
        _x1 = (y - b) / (2.0 * a);
    else
        _x1 = -(y + b) / (2.0 * a);
    if (d == 0)
    {
        *x1 = *x2 = _x1;
        return 1;
    }
    _x2 = c / (_x1 * a);
    *x1 = max(_x1, _x2);
    *x2 = min(_x1, _x2);
    return 2;
}

/*
 * optimal_summands: find the largest integer k such that 1 + 2 + ... + k <= total.
 */
unsigned int optimal_summands(unsigned int total)
{
    double x1, x2;
    unsigned int nroots;

    nroots = quadratic(1.0, 1.0, -2.0 * total, &x1, &x2);
    if (nroots == 0)
    {
        printf("error: there is no solution\n");
        return 0;
    }
    return (unsigned int)x1;
}

/*
 * print_summands: print the numbers 1, ..., (nsummands - 1) and (total - s), where
 * s = 1 + ... + (nsummands - 1).
 */
void print_summands(unsigned int total, unsigned int nsummands)
{
    unsigned int i;

    for (i = 1; i < nsummands; i++)
        printf("%u ", i), total -= i;
    printf("%u\n", total);
}