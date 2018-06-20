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
 *   Solution for Maximum Value of an Arithmetic Expression Problem
 * 
 * ----------------------------------------------------------------------- */

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* maximum number of digits in an expression */
#define N_MAX 14

/* maximum number of symbols in an expression */
#define EXPRSIZ_MAX (2 * N_MAX - 1)

/* the keyword typeof is not available in programs compiled with -std */
#define typeof __typeof__

/* 
 * _cmp: compares two values of the same or compatible types.
 */
#define _cmp(a, b, op) ((a) op (b) ? (a) : (b))

/* 
 * _cmp_once: compares two values of the same or compatible types
 * avoiding multiple evaluations of the arguments.
 */
#define _cmp_once(a, b, op) ({      \
		typeof(a) _a = (a);         \
		typeof(b) _b = (b);         \
		_cmp(_a, _b, op); })

/* 
 * min: returns the minimum of two values of the same or compatible types.
 */
#define min(a, b) _cmp_once(a, b, <)

/* 
 * min3: returns the minimum of three values of the same or compatible types.
 */
#define min3(a, b, c) min((typeof(a))min(a, b), c)

/* 
 * min5: returns the minimum of five values of the same or compatible types.
 */
#define min5(a, b, c, d, e) min((typeof(a))min3(a, b, c), (typeof(d))min(d, e))

/* 
 * max: returns the maximum of two values of the same or compatible types.
 */
#define max(x, y) _cmp_once(x, y, >)

/* 
 * max3: returns the maximum of three values of the same or compatible types.
 */
#define max3(x, y, z) max((typeof(x))max(x, y), z)

/* 
 * max5: returns the maximum of five values of the same or compatible types.
 */
#define max5(a, b, c, d, e) max((typeof(a))max3(a, b, c), (typeof(d))max(d, e))

/*
 * todigit: converts the char expr[idx] into a integer.
 */
long todigit(char *expr, unsigned int idx)
{
    char c;
    
    if (!isdigit(c = expr[idx])) {
        fprintf(stderr, "error: expr[%u] is not a digit\n", idx);
        exit(1);
    }
    return c - '0';
}

/*
 * eval: evaluates the expression x op y, where op can be one of the following
 * operations: +, - and *.
 */
long eval(long x, char op, long y)
{
        switch (op) {
        case '+':
            return x + y;
        case '-':
            return x - y;
        case '*':
            return x * y;
        default:
            fprintf(stderr, "the symbol %c is not an operator\n", op);
            exit(1);
        }
}

/*
 * maxval: returns the maximum value of an arithmetic expression expr, where 
 * expr[2n] and expr[2n-1] are a digit and an operation, respectively, for 
 * each 1 <= n <= N_MAX.
 */
long maxval(char *expr)
{
    static long m[EXPRSIZ_MAX][EXPRSIZ_MAX], M[EXPRSIZ_MAX][EXPRSIZ_MAX];
    unsigned int i, j, k, n, s;
    long a, b, c, d;

    n = (strlen(expr) + 1) / 2;
    for (i = 0; i < n; i++) {
        m[i][i] = todigit(expr, 2 * i);
        M[i][i] = todigit(expr, 2 * i);
    }
    for (s = 1; s < n; s++)
        for (i = 0; i < (n - s); i++) {
            j = i + s;
            m[i][j] = LONG_MAX;
            M[i][j] = LONG_MIN;
            for (k = i; k < j; k++) {
                a = eval(M[i][k], expr[2 * k + 1], M[k + 1][j]);
                b = eval(M[i][k], expr[2 * k + 1], m[k + 1][j]);
                c = eval(m[i][k], expr[2 * k + 1], M[k + 1][j]);
                d = eval(m[i][k], expr[2 * k + 1], m[k + 1][j]);
                m[i][j] = min5(a, b, c, d, m[i][j]);
                M[i][j] = max5(a, b, c, d, M[i][j]);
            }
        }
    return M[0][n-1];
}

int main()
{
    char expr[EXPRSIZ_MAX];

    scanf("%s", expr);
    printf("%ld\n", maxval(expr));
    return 0;
}