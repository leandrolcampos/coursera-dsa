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

#include <stdio.h>
#include <stdlib.h>

#define ROOT_IDX -1 /* parent index for the root node */

typedef struct Child Child;
typedef struct Node Node;
typedef struct Tree Tree;

struct Child {
    Node    *nodep;
    Child   *next;
};

struct Node {
    size_t  val;
    size_t  height;
    Node    *parent;
    Child   *children;
};

struct Tree {
    size_t  nnodes;
    Node    *root;
    Node    *nodes;
};

inline size_t max(size_t x, size_t y)
{
    return (x > y) ? x : y;
}

Child *newchild(Node *nodep)
{
    Child *newp;

    if ((newp = (Child *)malloc(sizeof(Child))) == NULL) {
        fprintf(stderr, "memory allocation error when creating a child\n");
        exit(1);
    }
    newp->nodep = nodep;
    newp->next = NULL;
    return newp;
}

Child *freechild(Child *childp)
{
    Child *next;

    next = childp->next;
    free(childp);
    return next;
}

Child *addchild(Node *parentp, Child *childp)
{
    size_t tmp;

    //printf("add node %lu as a child of node %lu\n", childp->nodep->val, parentp->val);
    childp->nodep->parent = parentp;
    childp->next = parentp->children;
    tmp = childp->nodep->height;
    //printf("height of node %lu: %lu\n", childp->nodep->val, tmp);
    for ( ; parentp != NULL; parentp = parentp->parent) {
        parentp->height = max(parentp->height, tmp + 1);
        tmp = parentp->height;
        //printf("height of node %lu: %lu\n", parentp->val, tmp);
    }
    return childp;
}

Tree *newtree(size_t nnodes)
{
    Tree *newp;
    Node *nodep;
    size_t i;

    if ((newp = (Tree *)malloc(sizeof(Tree))) == NULL) {
        fprintf(stderr, "memory allocation error when creating a tree\n");
        exit(1);
    }
    if ((newp->nodes = (Node *)malloc(nnodes * sizeof(Node))) == NULL) {
        fprintf(stderr, "memory allocation error when creating nodes\n");
        free(newp);
        exit(1);
    }
    nodep = newp->nodes;
    for (i = 0; i < nnodes; i++, nodep++) {
        nodep->val = i;
        nodep->height = 1;
        nodep->parent = NULL;
        nodep->children = NULL;
    }
    newp->root = NULL;
    newp->nnodes = nnodes;
    return newp;
}

void freeall(Tree *treep)
{
    size_t i;
    Child *childp, *next;

    for (i = 0; i < treep->nnodes; i++) {
        childp = treep->nodes[i].children;
        for ( ; childp != NULL; childp = next) {
            next = freechild(childp);
        }
    }
    free(treep->nodes);
    free(treep);
}

Tree *buildtree(int *parent_idx, size_t nnodes)
{
    Tree *treep;
    Node *nodes;
    Child *childp;
    size_t i, j;

    treep = newtree(nnodes);
    nodes = treep->nodes;
    for (i = 0; i < nnodes; i++) {
        j = parent_idx[i];
        if (j == ROOT_IDX) {
            treep->root = &nodes[i];
        } else {
            childp = newchild(&nodes[i]);
            nodes[j].children = addchild(&nodes[j], childp);
        }
    }
    return treep;
}

int main()
{
    Tree *treep;
    size_t nnodes, i;
    int parent_idx[100000];

    nnodes = 100000;
    for (i = 0; i < nnodes; i++)
        parent_idx[i] = i - 1;
    treep = buildtree(parent_idx, nnodes);
    printf("%lu\n", treep->root->height);
    freeall(treep);
    exit(0);
}