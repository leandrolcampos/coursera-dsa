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
 *   Solution for Compute Tree Height Problem
 * 
 * ----------------------------------------------------------------------- */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef size_t
#undef size_t
#endif

#define size_t unsigned int

#define MAXNNODES 100000   /* maximum number of nodes in a tree */
#define PARENT_IDX_ROOT -1 /* parent_idx for the root node */

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

typedef struct Child Child;
typedef struct Node Node;
typedef struct Tree Tree;

struct Child {
    size_t  node_idx;
    Child   *next;
};

struct Node {
    size_t  val;
    size_t  height;         /* 0 if this height has not been calculated yet */
    Child   *children;
};

struct Tree {
    size_t  nnodes;
    bool    hupdtd;         /* true if the height of all nodes is updated */
    size_t  root_idx;
    Node    *nodes;
};

/* 
 * emalloc: allocates n bytes memory or print a message if an error occurs
 */
void *emalloc(size_t nbytes)
{
    void *p;

    p = malloc(nbytes);
    if (p == NULL) {
        printf("malloc of %u bytes failed\n", nbytes);
        exit(1);
    }
    return p;
}

/* 
 * efree: deallocates the memory previously allocated or print a message if 
 * an error occurs
 */
void *efree(void *ptr)
{
    if (ptr == NULL) {
        printf("ptr points to NULL\n");
        exit(1);
    }
    free(ptr);
    return (ptr = NULL);
}

/*
 * addchild: informs that the node with index child_idx is a child of the node 
 * with index parent_idx
 */
void addchild(Tree *treep, size_t parent_idx, size_t child_idx)
{
    Node *nodep;
    Child *childp;

    if (parent_idx >= treep->nnodes) {
        printf("parent_idx is out of bounds\n");
        exit(1);
    }
    if (child_idx >= treep->nnodes) {
        printf("child_idx is out of bounds\n");
        exit(1);
    }
    childp = emalloc(sizeof(*childp));
    childp->node_idx = child_idx;
    nodep = &treep->nodes[parent_idx];
    childp->next = nodep->children;
    nodep->children = childp;
    treep->hupdtd = false;
}

/*
 * newtree: creates and initializes a tree with n nodes
 */
Tree *newtree(size_t nnodes)
{
    Tree *treep;
    Node *nodep;
    size_t i;

    if (nnodes == 0 || nnodes > MAXNNODES) {
        printf("nnodes is out of bounds\n");
        exit(1);
    }
    treep = emalloc(sizeof(*treep));
    treep->nodes = emalloc(nnodes * sizeof(*nodep));
    nodep = treep->nodes;
    for (i = 0; i < nnodes; i++) {
        nodep->val = 0;
        nodep->height = 0;
        nodep->children = NULL;
    }
    treep->root_idx = 0;
    treep->hupdtd = true;
    treep->nnodes = nnodes;
    return treep;
}

/*
 * freeall: deallocates the memory previously allocated for the tree, its 
 * nodes, and the parent-child relationships
 */
Tree *freeall(Tree *treep)
{
    size_t i, n;
    Node *nodep;
    Child *childp, *next;

    if (treep == NULL) {
        printf("treep points to NULL\n");
        exit(1);
    }
    n = treep->nnodes;
    nodep = treep->nodes;
    for (i = 0; i < n; i++) { /* free all children of each node */
        childp = nodep->children;
        for ( ; childp != NULL; childp = next) {
            next = childp->next;
            childp->next = NULL;
            childp = efree(childp);
        }
        nodep++;
    }
    treep->nodes = efree(treep->nodes);
    return (treep = efree(treep));
}

/*
 * buildtree: creates and initializes a tree with n nodes, where the value 
 * and the parent of the ith node is, respectively, val[i] and parent_idx[i]
 */
Tree *buildtree(size_t nnodes, int *val, int *parent_idx)
{
    Tree *treep;
    Node *nodep;
    Child *childp;
    size_t i, j;

    treep = newtree(nnodes);
    nodep = treep->nodes;
    for (i = 0; i < nnodes; i++) {
        nodep[i].val = val[i];
        j = parent_idx[i];
        if (j == PARENT_IDX_ROOT) {
            treep->root_idx = i;
        } else {
            addchild(treep, j, i);
        }
    }
    return treep;
}

/*
 * height: computes the height of the node with index node_idx
 */
size_t height(Tree *treep, size_t node_idx)
{
    size_t i, n, maxh;
    Node *nodep;
    Child *childp;

    if (treep == NULL) {
        printf("treep points to NULL\n");
        exit(1);
    }
    if (node_idx >= treep->nnodes) {
        printf("nnodes is out of bounds\n");
        exit(1);
    }
    if (!treep->hupdtd) { /* the height of all nodes is outdated */
        n = treep->nnodes;
        nodep = treep->nodes;
        for (i = 0; i < n; i++)
            nodep->height = 0;
        nodep++;
    }
    nodep = &treep->nodes[node_idx];
    if (nodep->height > 0) /* the height is already calculated */
        return nodep->height;
    maxh = 0;
    for (childp = nodep->children; childp != NULL; childp = childp->next)
        maxh = max(maxh, height(treep, childp->node_idx));
    return maxh + 1;
}

int main()
{
    Tree *treep;
    size_t nnodes, i;
    int *val, *parent_idx;

    scanf("%u", &nnodes);
    val = emalloc(nnodes * sizeof(*val));
    parent_idx = emalloc(nnodes * sizeof(*parent_idx));
    for (i = 0; i < nnodes; i++) {
        val[i] = i;
        scanf("%d", &parent_idx[i]);
    }
    treep = buildtree(nnodes, val, parent_idx);
    printf("%u\n", height(treep, treep->root_idx));
    freeall(treep);
    parent_idx = efree(parent_idx);
    val = efree(val);
    exit(0);
}