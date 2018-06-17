/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Fibonacci Number Again Problem
 */

#include <stdio.h>
#include <math.h>

#define MODULE_MIN 2
#define MODULE_MAX 1000
#define FIRST_PISANO_PERIODS_SIZE 10
#define FIB_TABLE_SIZE (2 * 6 * MODULE_MAX)

unsigned short first_pisano_periods[] = {1, 3, 8, 6, 20, 24, 16, 12, 24, 60};
unsigned short fib_table[FIB_TABLE_SIZE] = {0, 1};
unsigned short fib_table_idx = 1;
unsigned short fib_table_module = 0;
unsigned short fib_module(unsigned short, unsigned short);
unsigned short pisano_period(unsigned short);
unsigned short fibonacci_huge_naive(unsigned long long, unsigned short);

int main()
{
    unsigned short m, r;
    unsigned long long n;

    scanf("%llu %hu", &n, &m);
    r = pisano_period(m);
    printf("%hu\n", fib_module(n % r, m));
    return 0;
}

// fib_module: calculate fib(n) mod m, where fib(n) is the nth
// fibonnaci number, 1 <= n <= 10^18 and 2 <= m <= 10^3.
unsigned short fib_module(unsigned short n, unsigned short m)
{
    unsigned short fib_value;

    if (n >= FIB_TABLE_SIZE)
    {
        printf("n is larger than or equals to FIB_TABLE_SIZE\n");
        return -1;
    }
    if (m > MODULE_MAX)
    {
        printf("m is larger than MODULE_MAX\n");
        return -1;
    }
    if (m < MODULE_MIN)
    {
        printf("m is smaller than MODULE_MIN\n");
        return -1;
    }
    if (m != fib_table_module)
    {
        fib_table_idx = 1;
        fib_table_module = m;
    }
    while (fib_table_idx < n)
    {
        fib_table_idx++;
        fib_value = fib_table[fib_table_idx - 1];
        fib_value += fib_table[fib_table_idx - 2];
        fib_value %= m;
        fib_table[fib_table_idx] = fib_value;
    }
    return fib_table[n];
}

// pisano_period: calculate the nth Pisano period, where
// 2 <= m <= 10^3.
unsigned short pisano_period(unsigned short m)
{
    unsigned short i, n, p;
    double k;

    if (m > MODULE_MAX)
    {
        printf("m is larger than MODULE_MAX\n");
        return -1;
    }
    if (m < MODULE_MIN)
    {
        printf("m is smaller than MODULE_MIN\n");
        return -1;
    }
    if (m <= FIRST_PISANO_PERIODS_SIZE)
        return first_pisano_periods[m - 1];
    n = 4 * m;
    if (m % 2 == 0 && m % 5 == 0)
    {
        k = log(m / 2) / log(5);
        if (k - floor(k) == 0)
            n = 6 * m;
    }
    for (p = 2; p < n; p += 2)
    {
        for (i = 0; i < n; i++)
            if (fib_module(i, m) != fib_module(i + p, m))
                break;
        if (i == n)
            break;
    }
    return p;
}

// fibonacci_huge_naive: calculate fib(n) mod m, where fib(n) is the nth
// fibonnaci number, 1 <= n <= 10^18 and 2 <= m <= 10^3.
unsigned short fibonacci_huge_naive(unsigned long long n, unsigned short m)
{
    unsigned short next, current, previous;

    if (n < 2)
    {
        if (n == 0)
            return 0;
        else
            return 1;
    }
    previous = 0, current = 1;
    while (n-- > 2)
    {
        next = (current + previous) % m;
        previous = current;
        current = next;
    }
    return (current + previous) % m;
}