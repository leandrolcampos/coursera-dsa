#include <stdio.h>
#include <string.h>

/* maximum string size */
#define STRMAX 100

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
#define _cmp_once(x, y, op) ({  \
		typeof(x) _x = (x);     \
		typeof(y) _y = (y);     \
		_cmp(_x, _y, op); })

/* 
 * min: returns the minimum of two values of the same or compatible types.
 */
#define min(x, y) _cmp(x, y, <)

/* 
 * min: returns the minimum of three values of the same or compatible types.
 */
#define min3(x, y, z) min((typeof(x))min(x, y), z)

/*
 * editdist: computes the edit distance between two strings.
 */
unsigned short editdist(const char *cs, const char *ct)
{
    static unsigned short d[STRMAX+1][STRMAX+1];
    unsigned short n, m;
    unsigned short i, j;

    n = strlen(cs);
    m = strlen(ct);
    for (i = 0; i <= n; i++)
        d[i][0] = i;
    for (j = 1; j <= m; j++)
        d[0][j] = j;
    for (j = 1; j <= m; j++)
        for (i = 1; i <= n; i++) {
            if (cs[i-1] == ct[j-1])
                d[i][j] = min3(d[i][j-1] + 1, d[i-1][j] + 1, d[i-1][j-1]);
            else
                d[i][j] = min3(d[i][j-1] + 1, d[i-1][j] + 1, d[i-1][j-1] + 1);
        }
    return d[n][m];
}

int main()
{
    char s[STRMAX+1], t[STRMAX+1];

    scanf("%s", s);
    scanf("%s", t);
    printf("%hu\n", editdist(s, t));
    return 0;
}