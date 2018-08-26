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
 *   Solution for Is It a Binary Search Tree? Hard Version Problem
 * 
 * ----------------------------------------------------------------------- */

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAXLEN 100000
#define MAXVAL INT_MAX
#define MINVAL INT_MIN

int key[MAXLEN] = {0};
int left[MAXLEN] = {-1};
int right[MAXLEN] = {-1};
int sm[MAXLEN] = {MAXVAL};
int lg[MAXLEN] = {MINVAL};

/*
 * is_bst: tests whether a binary search tree data structure was implemented 
 * correctly.
 */
bool is_bst(int idx)
{
    if (idx == -1)
        return true;
    if (left[idx] == -1) {
        sm[idx] = key[idx];
    } else {
        if (!is_bst(left[idx]))
            return false;
        if (key[idx] <= lg[left[idx]])
            return false;
        sm[idx] = sm[left[idx]];    
    }
    if (right[idx] == -1) {
        lg[idx] = key[idx];
    } else {
        if (!is_bst(right[idx]))
            return false;
        if (key[idx] > sm[right[idx]])
            return false;
        lg[idx] = lg[right[idx]];    
    }
    return true;
}

int main()
{
    int i, n;

    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d %d %d", &key[i], &left[i], &right[i]);
    }
    if (is_bst(0))
        printf("CORRECT\n");
    else
        printf("INCORRECT\n");
    return 0;
}