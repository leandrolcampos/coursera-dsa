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
 *   Solution for Number of Inversions Problem
 * 
 * ----------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

/*
 * merge: merges the sequences base[0] <= ... <= base[mid-1] and base[mid] <= 
 * ... <= base[nel-1] into base[0] <= ... <= base[nel-1] and returns the 
 * number of inversions needed.
 */
unsigned long merge(unsigned int *base, unsigned int nel, unsigned int mid)
{
    unsigned int *buf, *bufp, *p, *q, *endp, *endq;
    unsigned long inv;

    bufp = buf = malloc(nel * sizeof(*base));
    p = base;
    q = base + mid;
    endp = base + (mid - 1);
    endq = base + (nel - 1);
    inv = 0;
    while (p <= endp && q <= endq) {
        if (*p <= *q) {
            *bufp++ = *p++;
        } else {
            *bufp++ = *q++;
            inv += endp - p + 1;
        }
    }
    while (p <= endp)
        *bufp++ = *p++;
    while (q <= endq)
        *bufp++ = *q++;
    bufp = buf;
    while (base <= endq)
        *base++ = *bufp++;
    free(buf);
    return inv;
}

/*
 * msort: sorts the sequence base[0], ..., base[nel-1] in a non-decreasing 
 * order and returns the number of inversions needed.
 */
unsigned long msort(unsigned int *base, unsigned int nel)
{
    unsigned int mid;
    unsigned long inv;

    if (nel == 1)
        return 0;
    mid = nel / 2;
    inv = msort(base, mid);
    inv += msort(base + mid, nel - mid);
    inv += merge(base, nel, mid);
    return inv;
}

/*
 * print: prints the sequence base[0], ..., base[nel-1].
 */
void print(const unsigned int *base, unsigned int nel)
{
    while (nel--)
        printf("%u ", *base++);
    putchar('\n');
}

int main()
{
    unsigned int nel;
    unsigned int *base;
    unsigned int i;
    unsigned long inv;

    scanf("%u", &nel);
    base = malloc(nel * sizeof(unsigned int));
    for (i = 0; i < nel; i++)
        scanf("%u", &base[i]);
    inv = msort(base, nel);
    printf("%lu\n", inv);
    free(base);
    return 0;
}