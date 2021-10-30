#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;

    // Take input from the user and verify non negative number
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars <= 0);

    int cents = round(dollars * 100);

    // printf("Coin: %f\n", dollars);
    // printf("Cents: %d\n", cents);

    int coin = 0;

    // Check with 25 cent
    coin += cents / 25;
    cents = cents % 25;

    // Check with 10 cent
    coin += cents / 10;
    cents = cents % 10;

    // Check with 5 cent
    coin += cents / 5;
    cents = cents % 5;

    // Check with 1 cent
    coin += cents / 1;
    cents = cents % 1;

    printf("%d\n", coin);



}