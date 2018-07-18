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
 *   Solution for Convert Array Into Heap Problem
 * 
 * ----------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

#define uint unsigned int

/* the keyword typeof is not available in programs compiled with -std */
#define typeof __typeof__

/* 
 * left_child: returns the index of the left child of index i.
 */
#define left_child(i) ({                                                       \
        typeof(i) _i = (i);                                                    \
        2 * _i + 1; })

/* 
 * right_child: returns the index of the right child of index i.
 */
#define right_child(i) ({                                                      \
        typeof(i) _i = (i);                                                    \
        2 * _i + 2; })

/* 
 * swap: exchanges arr[i] and arr[j].
 */
#define swap(arr, i, j) ({                                                     \
        typeof(arr) _arr = (arr);                                              \
        typeof(i) _i = (i);                                                    \
        typeof(j) _j = (j);                                                    \
        typeof(*arr) temp = _arr[_i];                                          \
        _arr[_i] = _arr[_j];                                                   \
        _arr[_j] = temp; })

uint *swap_i, *swap_j, nswap; /* register each swap */

/*
 * shift_down: executes the necessary swap operations to garantee that the 
 * array arr[i], ..., arr[nel-1] is a min-heap, where nel is the number of
 * elements in arr.
 */
void shift_down(uint *arr, uint nel, uint i)
{
    uint j; /* index of the minimum value: arr[i], arr[lt] and arr[rt] */
    uint lt, rt;

    j = i;
    lt = left_child(i);
    if ((lt < nel) && (arr[lt] < arr[j]))
        j = lt;
    rt = right_child(i);
    if ((rt < nel) && (arr[rt] < arr[j]))
        j = rt;
    if (i != j) {
        swap_i[nswap] = i;
        swap_j[nswap] = j;
        nswap++;
        swap(arr, i, j);
        shift_down(arr, nel, j);
    }
}

/*
 * build_heap: converts the array arr, with nel elements, into a min-heap.
 */
void build_heap(uint *arr, uint nel)
{
    uint i;

    for (i = nel / 2; i > 0; i--)
        shift_down(arr, nel, i - 1);
}

int main() {
    uint *arr;
    uint n, i;

    scanf("%u", &n);
    if (n == 0) {
        printf("n is equal to zero");
        return 1;
    }
    if ((arr = malloc(n * sizeof(*arr))) == NULL) {
        printf("malloc failed\n");
        return 1;
    }
    if ((swap_i = malloc((4 * n) * sizeof(*swap_i))) == NULL) {
        printf("malloc failed\n");
        return 1;
    }
    if ((swap_j = malloc((4 * n) * sizeof(*swap_i))) == NULL) {
        printf("malloc failed\n");
        return 1;
    }
    nswap = 0;
    for (i = 0; i < n; i++)
        scanf("%u", &arr[i]);
    build_heap(arr, n);
    printf("%u\n", nswap);
    for (i = 0; i < nswap; i++) {
        printf("%u %u\n", swap_i[i], swap_j[i]);
    }
    free(arr);
    free(swap_i);
    free(swap_j);
    return 0;
}