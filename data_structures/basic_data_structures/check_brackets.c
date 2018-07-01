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
 *   Solution for Check Brackets in the Code Problem
 * 
 * ----------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 100000 /* max length of any string */

typedef struct Item Item;
struct Item {
    char bracket;
    int index;
};

typedef struct Stack Stack;
struct Stack {      /* stack implementation with growable array */
    int nit;        /* current number of items */
    int max;        /* allocated number of items */
    Item *base;     /* array of items - refer to its elements by subscripts */
};

enum { STKINIT = 15625, STKGROW = 2 };

/*
 * push: adds item to stack and returns the index of the item just add, or -1
 * if some error occurred in memory allocation
 */
int push(Stack *stack, Item item)
{
    Item *membck;

    if (stack->base == NULL) { /* first item */
        stack->base = (Item *)malloc(STKINIT * sizeof(Item));
        if (stack->base == NULL)
            return -1;
        stack->max = STKINIT;
        stack->nit = 0;
    } else if (stack->nit == stack->max) { /* grow */
        membck = (Item *)realloc(stack->base, 
                    (STKGROW * stack->max) * sizeof(item));
        if (membck == NULL)
            return -1;
        stack->max *= STKGROW;
        stack->base = membck; /* the address of the array may change */
    }
    stack->base[stack->nit] = item;
    return stack->nit++;
}

/*
 * top: copies the most recently-added item in stack into the Item pointed to 
 * by item and returns its 0-based index, or -1 if some error occurred
 */
int top(const Stack *stack, Item *item)
{
    Item *itemp;

    if (stack->nit == 0) {
        return -1;
    } else {
        itemp = &stack->base[stack->nit-1];
        item->bracket = itemp->bracket;
        item->index = itemp->index;
        return (stack->nit - 1);
    }
}

/*
 * pop: copies the most recently-added item in stack into the Item pointed to 
 * by item, removes it and returns its 0-based index, or -1 if some error 
 * occurred
 */
int pop(Stack *stack, Item *item)
{
    Item *itemp;

    if (stack->nit == 0) {
        return -1;
    } else {
        itemp = &stack->base[--(stack->nit)];
        item->bracket = itemp->bracket;
        item->index = itemp->index;
        return stack->nit;
    }
}

/*
 * isempty: returns -1 if there are any items in stack and 0 otherwise
 */
inline int isempty(const Stack *stack)
{
    return (stack->nit == 0);
}

/*
 * brktchk: checks the usage of brackets in the string str. If the usage is 
 * correct, returns -1. Otherwise, returns the 0-based index of the first 
 * unmatched closing bracket, and if there are no unmatched closing brackets, 
 * output the 0-based index of the first unmatched opening bracket. And if 
 * some error occurred in push function, returns -2.
 */
int brktchk(const char *str)
{
    int i, c;
    Stack stk;
    Item top;
    
    stk = (Stack){ 0, 0, NULL };
    for (i = 0; (c = str[i]) != '\0'; i++) {
        if (c == '[' || c == '{' || c == '(') {
            if (push(&stk, (Item){ c, i }) == -1)
                return -2;
        } else if (c == ']' || c == '}' || c == ')') {
            if (isempty(&stk))
                return i;
            pop(&stk, &top);
            if ((top.bracket == '[' && c != ']')
             || (top.bracket == '{' && c != '}')
             || (top.bracket == '(' && c != ')'))
                return i;
        }
    }
    if (isempty(&stk))
        return -1;
    pop(&stk, &top);
    if (stk.base != NULL)
        free(stk.base);
    return top.index;
}

int main()
{
    char str[MAXLEN+2]; /* two extra characters, for '\n' and '\0' */
    int res;

    /* one extra character, for '\n' */
    if (fgets(str, MAXLEN+1, stdin) == NULL)
        return -1;
    if ((res = brktchk(str)) == -2) {
        puts("error in push function\n");
        return -1;
    } else if (res == -1) {
        puts("Success\n");
    } else {
        printf("%d\n", res + 1); /* 1-based index */
    }
    return 0;
}