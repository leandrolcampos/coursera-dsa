/* ----------------------------------------------------------------------- *
 * 
 *   Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 *   Data Structures and Algorithms Specialization,
 *   by University of California, San Diego, 
 *   and National Research University Higher School of Economics
 * 
 *   Course 1: Algorithmic Toolbox
 * 
 *   Solution for Partitioning Souvenirs Problem
 * 
 * ----------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

/* maximum number of elements */
#define NEL_MAX 20

/* number of partitions */
#define NPART 3

/* maximum limit value */
#define LIM_MAX ((20 * 30) / NPART)

/* the keyword typeof is not available in programs compiled with -std */
#define typeof __typeof__

/* 
 * _cmp: compares two values of the same or compatible types.
 */
#define _cmp(x, y, op) ((x) op (y) ? (x) : (y))

/* 
 * _cmp_once: compares two values of the same or compatible types
 * avoiding multiple evaluations of the arguments.
 */
#define _cmp_once(x, y, op) ({      \
		typeof(x) _x = (x);         \
		typeof(y) _y = (y);         \
		_cmp(_x, _y, op); })

/* 
 * max: returns the maximum of two values of the same or compatible types.
 */
#define max(x, y) _cmp_once(x, y, >)

/*
 * partition3: returns 1 if it is possible to partition vals[0], ..., 
 * vals[nel-1] into three subsets with equal sums, and 0 otherwise.
 */
int partition3(unsigned int *vals, unsigned int nel)
{
    static unsigned int tbl[LIM_MAX + 1][NEL_MAX + 1][NPART + 1] = { 0 };
    unsigned int i, v, j;
    unsigned int sum, lim, val, tmp;
    
    sum = 0;
    for (i = 0; i < nel; i++)
        sum += vals[i];
    if (sum % NPART != 0)
        return 0;
    lim = sum / NPART;
    for (j = 1; j <= NPART; j++)
        for (i = 1; i <= nel; i++)
            for (v = 1; v <= lim; v++) {
                tbl[v][i][j] = tbl[v][i - 1][j];
                if ((val = vals[i - 1]) <= v) {
                    tmp = tbl[v - val][i - 1][j] + val - (tbl[v][i][j-1] 
                          - tbl[v][i][j - 1]);
                    tbl[v][i][j] = max(tmp, tbl[v][i][j]);
                }
            }
    for (j = 1; j <= NPART; j++)
        if (tbl[lim][nel][j] != lim)
            return 0;
    return 1;
}

int main()
{
    unsigned int nel, vals[NEL_MAX];
    unsigned int i;

    scanf("%u", &nel);
    for (i = 0; i < nel; i++)
        scanf("%u", &vals[i]);
    printf("%u\n", partition3(vals, nel));
    return 0;
}