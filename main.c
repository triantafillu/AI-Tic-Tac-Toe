#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "aide_projet.c"


/*uint32_t isWin(uint32_t table)
{

}*/

uint32_t tableTo3(uint8_t table[3][3])
{
    uint32_t res = 0;
    uint32_t mult = 100000000;
    for (uint32_t i = 0; i < 3; i++)
    {
        for (uint32_t j = 0; j < 3; j++)
        {
            res += table[i][j] * mult;
            mult /= 10;
        }
    }

    return res;
}

/*uint32_t[3][3] * threeToTable(uint32_t three)
{
    uint32_t res[3][3];
    for (int i = 2; i > -1 ; i--)
    {
        for (int j = 2; j > -1 ; j--)
        {
            res[i][j] = three % 10;
            three /= 10;
        }
    }

    return res;
}*/

// Translate the table represented by a number of base 3 to the base 10
uint32_t translate10 (uint32_t table)
{
    uint32_t digit;
    uint32_t res = 0;
    uint32_t power = 0;

    // Iterate over the table
    while(table != 0)
    {
        // Pick up the last digit of the number
        digit = table % 10;

        // + digit multiplied by a 3 in power corresponding to position in table
        res += digit * pow(3,power);

        // Increment power
        power++;

        // Remove the last digit
        table = table / 10;
    }

    return res;
}

// Translate the decimal number to its table representation (base 3)
uint32_t translate3(uint32_t number)
{
    uint32_t res = 0;
    uint32_t power = 0;
    uint32_t rem;

    while (number != 0)
    {
        // Pick up the remainder
        rem = number % 3;

        // Get the result of division by base (3)
        number = number / 3;

        // The remainder becomes the lowest digit
        res += rem * pow(10, power);

        // Increment the power
        power++;
    }

    return res;
}

int main() {
    translate3( 15774);
    // 210122020
    return 0;
}
