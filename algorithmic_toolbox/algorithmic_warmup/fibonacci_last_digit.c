/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Last Digit of a Large Fibonacci Number Problem
 */

#include <stdio.h>

unsigned char fibonacci_last_digit(unsigned int);

int main()
{
    unsigned int n;

    scanf("%u", &n);
    printf("%hhu\n", fibonacci_last_digit(n));
    return 0;
}

// fibonacci_last_digit: calculate the last digit of the nth Fibonacci number 
// (assuming that 0 <= n <= 10^7)
unsigned char fibonacci_last_digit(unsigned int n)
{
    unsigned int m, f_i_1, f_i_2, temp;

    m = 10; // module base to obtain the last digit
    if (n < 2)
    {
        if (n == 0)
            return 0;
        else
            return 1;
    }
    f_i_2 = 0, f_i_1 = 1;
    while (n-- > 2)
    {
        temp = (f_i_1 + f_i_2) % m;
        f_i_2 = f_i_1;
        f_i_1 = temp;
    }
    return (f_i_1 + f_i_2) % m;
}