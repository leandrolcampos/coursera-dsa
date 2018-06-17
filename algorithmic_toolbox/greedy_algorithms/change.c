/*
 * Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 * Data Structures and Algorithms Specialization,
 * by University of California, San Diego, 
 * and National Research University Higher School of Economics
 * 
 * Course 1: Algorithmic Toolbox
 * 
 * Solution for Money Change Problem
 */

#include <stdio.h>

unsigned char number_of_coins(unsigned short);

static unsigned char coins[] = { 10, 5, 1 }; /* coin values */

int main()
{
    unsigned short amount;

    scanf("%hu", &amount);
    printf("%hhu\n", number_of_coins(amount));
    return 0;
}

/*
 * number_of_coins: calculate the minimum number of coins needed to change the amount 
 * into coins with denominations 1, 5, and 10, where 1 <= amount <= 10^3.
 */
unsigned char number_of_coins(unsigned short amount)
{
    unsigned char *coin, counter;

    coin = coins;
    counter = 0;
    while (amount)
    {
        counter += amount / *coin;
        amount %= *coin++;
    }
    return counter;
}