#include <stdio.h>
#include <cs50.h>
#include <math.h>

int checksum(long number)
{
    int count = 0;
    int sum1 = 0, sum2 = 0;
    int ans = -1;
    while (number > 0)
    {

        // MasterCard Check
        if ((count == 14) && (number == 51 || number == 52 || number == 53 || number == 54 || number == 55))
        {
            ans = 1;
        }

        // AMEX Check
        else if ((count == 13) && (number == 34 || number == 37))
        {
            ans = 2;
        }

        // VISA Check
        else if ((count == 12 || count == 15) && (number < 10 && number == 4))
        {
            ans = 3;
        }

        // Checksum Calculation
        if (count % 2 == 0)
        {
            sum2 += number % 10;
        }
        else
        {
            int rem = 2 * (number % 10);
            if (rem >= 10)
            {
                sum1 += rem % 10;
                rem /= 10;
            }
            sum1 += rem;
        }
        number /= 10;
        count++;
    }

    // printf("%d\n", count);
    // printf("%d %d\n", sum1, sum2);
    if ((sum1 + sum2) % 10 == 0)
    {
        return ans;
    }
    return -1;
}

int main(void)
{
    long number;

    // Take input from the user and verify non negative number
    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0);

    // Calculate Checksum
    int ans = checksum(number);

    if (ans == 1)
    {
        printf("MASTERCARD\n");
    }
    else if (ans == 2)
    {
        printf("AMEX\n");
    }
    else if (ans == 3)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }


}