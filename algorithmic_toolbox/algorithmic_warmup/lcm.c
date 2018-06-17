/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Least Common Multiple Problem
 */

#include <stdio.h>

unsigned long long lcm(unsigned int, unsigned int);
unsigned int gcd(unsigned int, unsigned int);

int main()
{
    unsigned int a, b;

    scanf("%u %u", &a, &b);
    printf("%llu\n", lcm(a, b));
    return 0;
}

// lcm: calculate the least common multiple of two positive integers a and b,
// where 1 <= a, b <= 2 * 10^9.
unsigned long long lcm(unsigned int a, unsigned int b)
{
    return (unsigned long long)a * b / gcd(a, b);
}

// gcd: calculate the greatest common divisor of two non-negative integers a and b.
// This function implements the Euclidean algorithm.
unsigned int gcd(unsigned int a, unsigned int b)
{
    if (a > b)
    {
        if (b == 0)
            return a;
        else
            return gcd(b, a % b);
    }
    else
    {
        if (a == 0)
            return b;
        else
            return gcd(a, b % a);
    }
}