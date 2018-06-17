/* --------------------------------------------------------------------------- *
 * 
 *   Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 *   Data Structures and Algorithms Specialization,
 *   by University of California, San Diego, 
 *   and National Research University Higher School of Economics
 * 
 *   Course 1: Algorithmic Toolbox
 * 
 *   Solution for Primitive Calculator Problem
 * 
 * -------------------------------------------------------------------------- */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_OPERATIONS 3 /* it is related to the enum operation */
#define MAX_VALUE 1000000
#define MAX_NUM_OPERATIONS UINT_MAX

enum operation {
    ADD_ONE = 1,
    MULT_BY_TWO = 2,
    MULT_BY_THREE = 3
};

static unsigned int nopers_tbl[MAX_VALUE + 1] = { 0 };
static unsigned int nopers_tbl_i = 1;

/* 
 * nopers: computes the minimum number of operations needed to obtain the number 
 * val starting from the number 1.
 */
unsigned int nopers(unsigned int val)
{
    unsigned int j, n;

    if (val <= nopers_tbl_i)
        return nopers_tbl[val];
    while (++nopers_tbl_i <= val) {
        n = nopers_tbl[nopers_tbl_i] = MAX_NUM_OPERATIONS;
        for (j = 1; j <= NUM_OPERATIONS; j++) {
            switch (j) {
            case ADD_ONE:
                n = nopers_tbl[nopers_tbl_i - 1] + 1;
                break;
            case MULT_BY_TWO:
                if (nopers_tbl_i % 2 == 0)
                    n = nopers_tbl[nopers_tbl_i / 2] + 1;
                break;
            case MULT_BY_THREE:
                if (nopers_tbl_i % 3 == 0)
                    n = nopers_tbl[nopers_tbl_i / 3] + 1;
            }
            if (n < nopers_tbl[nopers_tbl_i])
                nopers_tbl[nopers_tbl_i] = n;
        }
    }
    return nopers_tbl[val];
}

/* 
 * outval: prints the minimum operations needed to obtain the number val 
 * starting from the number 1.
 */
void outval(unsigned int val)
{
    if (val < 1) {
        return;
    }
    if (val % 3 == 0 && nopers_tbl[val] == nopers_tbl[val / 3] + 1) {
        outval(val / 3);
        printf("%u ", val);
    } else if (val % 2 == 0 && nopers_tbl[val] == nopers_tbl[val / 2] + 1) {
        outval(val / 2);
        printf("%u ", val);
    } else {
        outval(val - 1);
        printf("%u ", val);
    }
}

int main()
{
    unsigned int n, value;

    scanf("%u", &value);
    n = nopers(value);
    printf("%u\n", n);
    outval(value);
    putchar('\n');
    return 0;
}