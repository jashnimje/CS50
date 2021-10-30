#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int i, j, height;

    // Take input from the user and verify number (1-8)
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height <= 0);

    // Print the pattern
    for (i = 1; i <= height; i++)
    {
        // Print Spaces
        for (j = 0; j < height - i; j++)
        {
            printf(" ");
        }

        // Print Hashes
        for (j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }

}