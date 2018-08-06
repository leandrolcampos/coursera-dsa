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
 *   Solution for Hashing With Chains Problem
 * 
 * ----------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define uint unsigned int

typedef struct String String;
struct String {
    char *value;
    String *next;  /* in chain */
};

/* 
 * emalloc: allocates memory or print a message if an error occurs.
 */
void *emalloc(uint n)
{
    void *p;

    if ((p = malloc(n)) == NULL) {
        printf("malloc of %u bytes failed\n", n);
        exit(1);
    }
    return p;
}

/*
 * create: creates a hash table with m buckets and initializes each of them 
 * to NULL.
 */
String **create(uint m)
{
    String **base;
    uint i;

    base = emalloc(m * sizeof(String *));
    for (i = 0; i < m; i++)
        base[i] = NULL;
    return base;
}

/*
 * freeall: deallocates the memory previously allocated for the hash table 
 * base, where m is the number of buckets in base.
 */
void freeall(String **base, uint m)
{
    uint i;
    String *listp, *next;

    for (i = 0; i < m; i++) {
        for (listp = base[i]; listp != NULL; listp = next) {
            next = listp->next;
            free(listp->value);
            free(listp);
        }
    }
    free(base);
}

/*
 * hash: creates the hash value of str, where m is the number of buckets in 
 * the hash table.
 */
uint hash(uint m, char *str)
{
    unsigned long p, x, h;
    int i;

    p = 1000000007;
    x = 263;
    h = 0;
    for (i = strlen(str) - 1; i >= 0; i--)
        h = (h * x + str[i]) % p;
    return h % m;
}

/*
 * find: returns a pointer to the String with value equals to str or NULL if  
 * such String does not exist. The parameter base is the hash table and m is  
 * the number of buckets in base.
 */
String *find(String **base, uint m, char *str)
{
    String *listp;
    uint h;

    h = hash(m, str);
    for (listp = base[h]; listp != NULL; listp = listp->next)
        if ((strcmp(listp->value, str)) == 0)
            return listp;
    return NULL;
}

/*
 * add: inserts str into the hash table base, that has m buckets. If there is 
 * already such string in the hash table, then this function will do nothing. 
 */
String *add(String **base, uint m, char *str)
{
    String *_str;
    uint h;

    _str = find(base, m, str);
    if (_str == NULL) {
        h = hash(m, str);
        _str = emalloc(sizeof(*_str));
        _str->value = emalloc(strlen(str) + 1);
        strcpy(_str->value, str);
        _str->next = base[h];
        base[h] = _str;
    }
    return _str;
}

/*
 * delete: removes a String with value 'str' from the hash table base, where 
 * m is its number of buckets. 
 */
void delete(String **base, uint m, char *str)
{
    String *listp, *prev;
    uint h;

    h = hash(m, str);
    prev = NULL;
    for (listp = base[h]; listp != NULL; listp = listp->next) {
        if ((strcmp(listp->value, str)) == 0) {
            if (prev == NULL)
                base[h] = listp->next;
            else
                prev->next = listp->next;
            free(listp->value);
            free(listp);
        }
        prev = listp;
    }
}

/*
 * print: prints the content of the i-th list in the hash table base, where m 
 * is its number of buckets. 
 */
void print(String **base, uint m, uint i)
{
    String *listp;

    if (i < m)
        for (listp = base[i]; listp != NULL; listp = listp->next)
            printf("%s ", listp->value);
    putchar('\n');
}

int main()
{
    String **base;
    uint m, n, i, number;
    char cmd[6], str[16];

    scanf("%u", &m);
    base = create(m);
    scanf("%u", &n);
    for (i = 0; i < n; i++) {
        scanf("%5s", cmd);
        if (strcmp(cmd, "add") == 0) {
            scanf("%15s", str);
            add(base, m, str);
        } else if (strcmp(cmd, "find") == 0) {
            scanf("%15s", str);
            if (find(base, m, str) == NULL)
                printf("no\n");
            else
                printf("yes\n");
        } else if (strcmp(cmd, "del") == 0) {
            scanf("%15s", str);
            delete(base, m, str);
        } else if (strcmp(cmd, "check") == 0) {
            scanf("%u", &number);
            print(base, m, number);
        } else {
            printf("command not found\n");
            break;
        }
    }
    freeall(base, m);
    return 0;
}