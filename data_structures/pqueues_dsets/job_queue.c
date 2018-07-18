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
 *   Solution for Parallel Processing Problem
 * 
 * ----------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

#define ulong unsigned long

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

typedef struct Job Job;
struct Job {
    ulong cost;          /* time, in seconds, necessary to process this job */
    ulong thread_id;     /* id of the thread which processed this job */
    ulong start;         /* time, in seconds, when this job was processed */
};

typedef struct Thread Thread;
struct Thread {
    ulong id;
    ulong busy;          /* this thread is available, if busy == 0
                           or the time, in seconds, until the thread 
                           will be busy, if busy > 0 */
};

/*
 * shift_down: executes the necessary swap operations to garantee that the 
 * job's array arr[i], ..., arr[nel-1] is a min-heap, where nel is the 
 * number of elements in arr.
 */
void shift_down(Thread *arr, ulong nel, ulong i)
{
    ulong j; /* index of the minimum value: arr[i], arr[lt] and arr[rt] */
    ulong lt, rt;

    j = i;
    lt = left_child(i);
    if (lt < nel) {
        if ((arr[lt].busy < arr[j].busy) 
        || ((arr[lt].busy == arr[j].busy) && (arr[lt].id < arr[j].id))) 
            j = lt;
    }
    rt = right_child(i);
    if (rt < nel) {
        if ((arr[rt].busy < arr[j].busy) 
        || ((arr[rt].busy == arr[j].busy) && (arr[rt].id < arr[j].id))) 
            j = rt;
    }
    if (i != j) {
        swap(arr, i, j);
        shift_down(arr, nel, j);
    }
}

/*
 * processor: simulates the processing of jobs following the instructions of 
 * the problem (see the corresponding programming assignment file), where 
 * nthd is the number of threads
 */
void processor(Job *arr, ulong nel, ulong nthd)
{
    Thread *pool;
    ulong i;

    if ((nel == 0) || (nthd == 0))
        return;
    if ((pool = malloc(nthd * sizeof(*pool))) == NULL) {
        printf("malloc failed\n");
        exit(1);
    }
    for (i = 0; i < nthd; i++) {
        pool[i].id = i;
        pool[i].busy = 0;
    }
    for (i = 0; i < nel; i++) {
        arr[i].thread_id = pool[0].id;
        arr[i].start = pool[0].busy;
        pool[0].busy += arr[i].cost;
        shift_down(pool, nthd, 0);
    }
    free(pool);
}

int main() {
    ulong n; /* number of threads */
    ulong m; /* number of jobs */
    Job *arr;
    ulong i;

    scanf("%lu %lu", &n, &m);
    if ((n == 0) || (m == 0)) {
        printf("n or m is equal to zero");
        return 1;
    }
    if ((arr = malloc(m * sizeof(*arr))) == NULL) {
        printf("malloc failed\n");
        return 1;
    }
    for (i = 0; i < m; i++)
        scanf("%lu", &arr[i].cost);
    processor(arr, m, n);
    for (i = 0; i < m; i++) {
        printf("%lu %lu\n", arr[i].thread_id, arr[i].start);
    }
    free(arr);
    return 0;
}