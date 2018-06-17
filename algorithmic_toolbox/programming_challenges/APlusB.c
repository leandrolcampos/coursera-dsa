/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Sum of Two Digits Problem
 */

#include <stdio.h>

int main()
{
    unsigned short a, b;

    scanf("%hu %hu", &a, &b);
    printf("%u\n", a + b);
    return 0;
}