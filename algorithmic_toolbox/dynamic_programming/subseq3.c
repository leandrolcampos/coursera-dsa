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
 *   Solution for Longest Common Subsequence of Three Sequences Problem
 * 
 * ----------------------------------------------------------------------- */

#include <stdio.h>

/* maximum sequence size */
#define SEQMAX 100

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
 * max3: returns the maximum of three values of the same or compatible types.
 */
#define max3(x, y, z) max((typeof(x))max(x, y), z)

/*
 * lcslen3: computes the length of a longest common subsequence of three 
 * sequences xs, ys and zs with n, m and l elements, respectively.
 */
unsigned short lcslen3(const int *xs, const int *ys, const int *zs,
                       unsigned short n, unsigned short m, unsigned short l)
{
    unsigned short d[SEQMAX+1][SEQMAX+1][SEQMAX+1] = { 0 };
    unsigned int i, j, k;

    for (k = 1; k <= l; k++)
        for (j = 1; j <= m; j++)
            for (i = 1; i <= n; i++) {
                if (xs[i-1] == ys[j-1] && xs[i-1] == zs[k-1]) {
                    d[i][j][k] = d[i-1][j-1][k-1] + 1;
                } else {
                    d[i][j][k] = max3(d[i-1][j][k],
                                      d[i][j-1][k],
                                      d[i][j][k-1]);
                }
            }
    return d[n][m][l];
}

int main()
{
    int xs[SEQMAX], ys[SEQMAX], zs[SEQMAX];
    unsigned short n, m, l;
    unsigned short i;

    scanf("%hu", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &xs[i]);
    scanf("%hu", &m);
    for (i = 0; i < m; i++)
        scanf("%d", &ys[i]);
    scanf("%hu", &l);
    for (i = 0; i < l; i++)
        scanf("%d", &zs[i]);
    printf("%hu\n", lcslen3(xs, ys, zs, n, m, l));
    return 0;
}