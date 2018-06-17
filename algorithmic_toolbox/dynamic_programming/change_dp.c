/* ----------------------------------------------------------------------- *
 * 
 *   Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 *   Data Structures and Algorithms Specialization,
 *   by University of California, San Diego, 
 *   and National Research University Higher School of Economics
 * 
 *   Course 1: Algorithmic Toolbox
 * 
 *   Solution for Money Change Problem
 * 
 * ----------------------------------------------------------------------- */

#include <stdlib.h>
#include <stdio.h>

#define MAX_MONEY 1000
#define MAX_NUM_COINS MAX_MONEY

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

static const uint8_t coins_denominations[] = {1, 3, 4}; /* in ascending 
                                                           order */
static const uint8_t num_coins_denominations = 3;
static uint16_t change_table[MAX_MONEY + 1] = {0}; /* from 0 to MAX_MONEY */
static uint16_t change_table_last_index = 0;

uint16_t min_num_coins(uint16_t);

int main()
{
    uint16_t money;

    scanf("%hu", &money);
    printf("%hu\n", min_num_coins(money));
    return 0;
}

/*
 * min_num_coins: finds the minimum number of coins that changes money.
 */
uint16_t min_num_coins(uint16_t money)
{
    uint16_t i, num_coins;

    if (money <= change_table_last_index)
        return change_table[money];
    while (++change_table_last_index <= money)
    {
        change_table[change_table_last_index] = MAX_NUM_COINS;
        for (i = 0; i < num_coins_denominations; i++)
        {
            if (change_table_last_index >= coins_denominations[i])
            {
                num_coins = change_table[change_table_last_index - coins_denominations[i]] + 1;
                if (num_coins < change_table[change_table_last_index])
                    change_table[change_table_last_index] = num_coins;
            }
        }
    }
    return change_table[money];
}