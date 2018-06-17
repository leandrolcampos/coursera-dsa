/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Greatest Common Divisor Problem
 */

#include <stdio.h>

unsigned int gcd(unsigned int, unsigned int);

int main()
{
    unsigned int a, b;

    scanf("%u %u", &a, &b);
    printf("%u\n", gcd(a, b));
    return 0;
}

// gcd: calculate the greatest common divisor of two non-negative integers a and b,
// where 0 <= a, b <= 2 * 10^9. This function implements the Euclidean algorithm.
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