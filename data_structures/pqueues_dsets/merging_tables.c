/* ----------------------------------------------------------------------- *
 * 
 *   Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 *   Data Structures and Algorithms Specialization,
 *   by University of California, San Diego, 
 *   and National Research University Higher School of Economics
 * 
 *   Course 2: Data Structures
 * 
 *   Solution for Merging Tables Problem
 * 
 * ----------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

#define uint unsigned int

typedef struct Tables Tables;
struct Tables {
    uint *parent;
    uint *nrow;
};

/*
 * make_table: creates the i-th table in tbl and registers the number of rows 
 * in it.
 */
inline void make_table(Tables *tbl, uint i, uint nrow)
{
    tbl->parent[i] = i;
    tbl->nrow[i] = nrow;
}

/*
 * find: finds the destination of the i-th table in tbl and compresses the 
 * path between them.
 */
uint find(Tables *tbl, uint i)
{
    uint j;

    if ((j = tbl->parent[i]) != i)
        j = tbl->parent[i] = find(tbl, j);
    return j;
}

/*
 * merge: if the destination of i is different of the destination of j in tbl, 
 * copies all the rows from the first table to the second table, then clears 
 * the first table and, instead of real data, puts a symbolic link to the 
 * second table into it. Returns the maximum of the sizes of all tables in tbl 
 * after the merge operation, where pmax is the maximum value before this 
 * operation.
 */
uint merge(Tables *tbl, uint i, uint j, uint pmax)
{
    uint i_id, j_id, temp;

    i_id = find(tbl, i);
    j_id = find(tbl, j);
    if (i_id == j_id)
        return pmax;
    tbl->parent[j_id] = i_id;
    temp = tbl->nrow[i_id] += tbl->nrow[j_id];
    tbl->nrow[j_id] = 0;
    return (temp > pmax) ? temp : pmax;
}

int main()
{
    uint n, m;
    uint i;
    uint nrow, pmax;
    uint d, s;
    Tables tbl;

    scanf("%u %u", &n, &m);
    if ((tbl.parent = malloc(n * sizeof(*tbl.parent))) == NULL) {
        printf("malloc failed\n");
        exit(1);
    }
    if ((tbl.nrow = malloc(n * sizeof(*tbl.nrow))) == NULL) {
        printf("malloc failed\n");
        exit(1);
    }
    pmax = 0;
    for (i = 0; i < n; i++) {
        scanf("%u", &nrow);
        make_table(&tbl, i, nrow);
        pmax = (nrow > pmax) ? nrow : pmax;
    }
    for (i = 0; i < m; i++) {
        scanf("%u %u", &d, &s);
        pmax = merge(&tbl, d - 1, s - 1, pmax);
        printf("%u\n", pmax);
    }
    free(tbl.parent);
    free(tbl.nrow);
    return 0;
}