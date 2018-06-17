/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Fibonacci Number Problem
 */

#include <stdio.h>

#define FIB_TABLE_SIZE 45 + 1 // fib[0], ..., fib[fib_table_p], where fib_table_p <= 45

static unsigned int fib_table[FIB_TABLE_SIZE] = {0, 1}; // { 0, 1, 0, ..., 0 }
static unsigned char fib_table_p = 1;                   // index to the larger Fibonacci number calculated
unsigned int fibonacci(unsigned char);

int main()
{
    unsigned char n;

    scanf("%hhu", &n);
    printf("%u\n", fibonacci(n));
    return 0;
}

// fibonacci: calculate the nth Fibonacci number (assuming that 0 <= n <= 45)
unsigned int fibonacci(unsigned char n)
{
    while (fib_table_p < n)
    {
        fib_table_p++;
        fib_table[fib_table_p] = fib_table[fib_table_p - 1] + fib_table[fib_table_p - 2];
    }
    return fib_table[n];
}