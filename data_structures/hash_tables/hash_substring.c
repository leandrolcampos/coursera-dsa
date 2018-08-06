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
 *   Solution for Find Pattern in Text Problem
 * 
 * ----------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 500000

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
 * hash: calculates the hash value of str[start...end], where 0 <= start <= end
 * <= (strlen(str) - 1).
 */
size_t hash(char *str, size_t start, size_t end)
{
    size_t p, x, h;
    size_t i;

    p = 1000000007;
    x = 1;
    h = 0;
    for (i = end + 1; i > start; i--)
        h = (h * x + str[i-1]) % p;
    return h;
}

/*
 * compute_hashes: computes the hash value hashes[i] of the substring 
 * txt[i...(i + pat_len - 1)], where 0 <= i <= (strlen(txt) - pat_len).
 */
void compute_hashes(char *txt, size_t pat_len, size_t *hashes)
{
    size_t txt_len;
    long long i;
    size_t y, p, x;

    txt_len = strlen(txt);
    hashes[txt_len - pat_len] = hash(txt, txt_len - pat_len, txt_len - 1);
    p = 1000000007;
    x = 1;
    y = 1;
    for (i = 1; i <= pat_len; i++)
        y = (y * x) % p;
    for (i = (txt_len - pat_len - 1); i >= 0; i--) {
        hashes[i] = (x * hashes[i+1] + txt[i] - y * txt[i+pat_len]) % p;
    }
}

/*
 * rabin_karp: prints all the positions of the occurrences of P in T in the 
 * ascending order.
 */
void rabin_karp(char *txt, char *pat)
{
    size_t p_hsh, *hashes;
    size_t p_len, t_len;
    size_t i;

    p_len = strlen(pat);
    t_len = strlen(txt);
    p_hsh = hash(pat, 0, p_len - 1);
    hashes = emalloc((t_len - p_len + 1) * sizeof(*hashes));
    compute_hashes(txt, p_len, hashes);
    for (i = 0; i <= (t_len - p_len); i++) {
        if (p_hsh != hashes[i])
            continue;
        if ((strncmp(txt + i, pat, p_len)) == 0)
            printf("%u ", i);
    }
    free(hashes);
    putchar('\n');
}

int main()
{
    char pat[MAXLEN+1], txt[MAXLEN+1];

    scanf("%s", pat);
    scanf("%s", txt);
    rabin_karp(txt, pat);
    return 0;
}