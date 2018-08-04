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
 *   Solution for Phone Book Problem
 * 
 * ----------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define uint unsigned int

typedef struct Contact Contact;
struct Contact {
    char *name;
    uint number;
    Contact *next;  /* in chain */
};

/* 
 * emalloc: allocates memory or print a message if an error occurs.
 */
void *emalloc(size_t n)
{
    void *p;

    if ((p = malloc(n)) == NULL) {
        printf("malloc of %u bytes failed\n", n);
        exit(1);
    }
    return p;
}

/*
 * create: creates an array of nel pointers to Contact and initializes each 
 * of them to NULL.
 */
Contact **create(uint nel)
{
    Contact **base;
    uint i;

    base = emalloc(nel * sizeof(Contact *));
    for (i = 0; i < nel; i++)
        base[i] = NULL;
    return base;
}

/*
 * freeall: deallocates the memory previously allocated for the base and its 
 * chains of contacts.
 */
void freeall(Contact **base, uint nel)
{
    uint i;
    Contact *listp, *next;

    for (i = 0; i < nel; i++) {
        for (listp = base[i]; listp != NULL; listp = next) {
            next = listp->next;
            free(listp->name);
            free(listp);
        }
    }
    free(base);
}

/*
 * hash: creates the hash value of number, where nel is the number of chains 
 * in the hash table.
 */
uint hash(uint nel, uint number)
{
    uint p, a, b;

    p = 10000019; /* prime number bigger than the largest phone number */
    a = 34;       /* any integer a such that 1 <= a <= p - 1 */
    b = 2;        /* any integer b such that 1 <= b <= p - 1 */
    return ((a * number + b) % p) % nel;
}

/*
 * find: returns a pointer to the contact with phone number equals to number 
 * or NULL if such contact does not exist. The parameter base is the hash 
 * table and nel is its length. 
 */
Contact *find(Contact **base, uint nel, uint number)
{
    Contact *listp;
    uint h;

    h = hash(nel, number);
    for (listp = base[h]; listp != NULL; listp = listp->next)
        if (listp->number == number)
            return listp;
    return NULL;
}

/*
 * add: adds a contact with name 'name' and phone number 'number' to the phone 
 * book. If there exists a user with such number already, then the function 
 * will overwrite the corresponding name. 
 */
Contact *add(Contact **base, uint nel, char *name, uint number)
{
    Contact *ct;
    uint h;

    ct = find(base, nel, number);
    if (ct == NULL) {
        h = hash(nel, number);
        ct = emalloc(sizeof(*ct));
        ct->name = emalloc(strlen(name) + 1);
        strcpy(ct->name, name);
        ct->number = number;
        ct->next = base[h];
        base[h] = ct;
    } else {
        if (strcmp(ct->name, name) != 0) {
            free(ct->name);
            ct->name = emalloc(strlen(name) + 1);
            strcpy(ct->name, name);
        }
    }
    return ct;
}

/*
 * delete: erases a contact with phone number 'number' from the phone book. 
 */
void delete(Contact **base, uint nel, uint number)
{
    Contact *listp, *prev;
    uint h;

    h = hash(nel, number);
    prev = NULL;
    for (listp = base[h]; listp != NULL; listp = listp->next) {
        if (listp->number == number) {
            if (prev == NULL)
                base[h] = listp->next;
            else
                prev->next = listp->next;
            free(listp->name);
            free(listp);
        }
        prev = listp;
    }
}

int main()
{
    Contact **base, *result;
    uint nel, number, i;
    char cmd[5], name[16];

    scanf("%u", &nel);
    base = create(nel);
    for (i = 0; i < nel; i++) {
        scanf("%4s %u", cmd, &number);
        if (strcmp(cmd, "add") == 0) {
            scanf("%15s", name);
            add(base, nel, name, number);
        } else if (strcmp(cmd, "find") == 0) {
            result = find(base, nel, number);
            if (result == NULL)
                printf("not found\n");
            else
                printf("%s\n", result->name);
        } else if (strcmp(cmd, "del") == 0) {
            delete(base, nel, number);
        } else {
            printf("command not found\n");
            break;
        }
    }
    freeall(base, nel);
    return 0;
}