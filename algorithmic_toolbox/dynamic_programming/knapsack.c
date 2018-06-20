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
 *   Solution for Maximum Amount of Gold Problem
 * 
 * ----------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

#define LIM_MAX 10000   /* maximum limit value */
#define NEL_MAX 300     /* maximum number of elements */

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
 * maxwgt: returns the maximum weight of gold that fits into a knapsack of
 * capacity lim.
 */
unsigned int maxwgt(unsigned int *wgts, unsigned int nel, unsigned int lim)
{
    static unsigned int val[LIM_MAX + 1][NEL_MAX + 1] = { 0 };
    unsigned int i, w;
    unsigned int wgt, tmp;
    
    for (i = 1; i <= nel; i++)
        for (w = 1; w <= lim; w++) {
            val[w][i] = val[w][i - 1];
            if ((wgt = wgts[i - 1]) <= w) {
                tmp = val[w - wgt][i - 1] + wgt;
                val[w][i] = max(tmp, val[w][i]);
            }
        }
    return val[lim][nel];
}

int main()
{
    unsigned int lim, nel, wgts[NEL_MAX];
    unsigned int i;

    scanf("%u %u", &lim, &nel);
    for (i = 0; i < nel; i++)
        scanf("%u", &wgts[i]);
    printf("%u\n", maxwgt(wgts, nel, lim));
    return 0;
}