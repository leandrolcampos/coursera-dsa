/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Last Digit of the Sum of Fibonacci Numbers Problem
 */

#include <stdio.h>
#include <math.h>

#define MODULE_MIN 2
#define MODULE_MAX 10
#define FIRST_PISANO_PERIODS_SIZE 10
#define FIB_TABLE_SIZE (2 * 6 * MODULE_MAX)

unsigned short first_pisano_periods[] = {1, 3, 8, 6, 20, 24, 16, 12, 24, 60};
unsigned short fib_table[FIB_TABLE_SIZE] = {0, 1};
unsigned short fib_table_idx = 1;
unsigned short fib_table_module = 0;
unsigned char fib_sum_squares_last_digit(unsigned long long);
unsigned short fib_module(unsigned short, unsigned short);
unsigned short pisano_period(unsigned short);
unsigned short fibonacci_huge_naive(unsigned long long, unsigned short);

int main()
{
    unsigned long long n;

    scanf("%llu", &n);
    printf("%hhu\n", fib_sum_squares_last_digit(n));
    return 0;
}

// fib_sum_squares_last_digit: calculate the last digit of a sum of squares
// of Fibonacci numbers: f(0)^2 + ... + f(n)^2, where 0 <= n <= 10^18.
unsigned char fib_sum_squares_last_digit(unsigned long long n)
{
    unsigned char sum;
    unsigned short i, m, p, r;
    unsigned long long q;

    m = 10; // module base to obtain the last digit
    p = pisano_period(m);
    q = n / p;
    r = n % p;
    sum = 0;
    if (q > 0)
        for (i = 0; i <= p; i++)
            sum = (sum + fib_module(i, m) * fib_module(i, m)) % m;
    sum = (sum * q) % m;
    if (r > 0)
        for (i = 0; i <= r; i++)
            sum = (sum + fib_module(i, m) * fib_module(i, m)) % m;
    return sum;
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