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
 *   Solution for Binary Tree Traversals Problem
 * 
 * ----------------------------------------------------------------------- */

#include <stdio.h>

#define MAXLEN 100000

/*
 * inorder: prints the key of each vertice in the in-order traversal of the 
 * tree.
 */
void inorder(unsigned int key[], int left[], int right[], int idx)
{
    if (idx == -1)
        return;
    inorder(key, left, right, left[idx]);
    printf("%u ", key[idx]);
    inorder(key, left, right, right[idx]);
}

/*
 * preorder: prints the key of each vertice in the pre-order traversal of the 
 * tree.
 */
void preorder(unsigned int key[], int left[], int right[], int idx)
{
    if (idx == -1)
        return;
    printf("%u ", key[idx]);
    preorder(key, left, right, left[idx]);
    preorder(key, left, right, right[idx]);
}

/*
 * postorder: prints the key of each vertice in the post-order traversal of 
 * the tree.
 */
void postorder(unsigned int key[], int left[], int right[], int idx)
{
    if (idx == -1)
        return;
    postorder(key, left, right, left[idx]);
    postorder(key, left, right, right[idx]);
    printf("%u ", key[idx]);
}

int main()
{
    unsigned int key[MAXLEN];
    int left[MAXLEN], right[MAXLEN];
    int i, n;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%u %d %d", &key[i], &left[i], &right[i]);
    }
    inorder(key, left, right, 0);
    putchar('\n');
    preorder(key, left, right, 0);
    putchar('\n');
    postorder(key, left, right, 0);
    putchar('\n');
    return 0;
}