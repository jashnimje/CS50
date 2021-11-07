#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, string argv[])
{

    // Check if the arguments are 2
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check if arg is num or not
    int i, n = strlen(argv[1]);
    for (i = 0; i < n; i++)
    {
        if (isdigit(argv[1][i]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Starts encryption
    string plaintext = get_string("plaintext: ");
    string ciphertext = "";
    int k = atoi(argv[1]);
    n = strlen(plaintext);
    printf("ciphertext: %s", ciphertext);

    // Looping over each character
    for (i = 0; i < n; i++)
    {
        // Check if alpha
        if (isalpha(plaintext[i]))
        {
            // Check if lowercase letter
            if (islower(plaintext[i]))
            {
                // First subtract the value eg-> a = 0
                printf("%c", ((plaintext[i] - 97 + k) % 26) + 97);
            }
            else
            {
                // First subtract the value eg-> A = 0
                printf("%c", ((plaintext[i] - 65 + k) % 26) + 65);
            }
        }
        else
        {
            // Ignore other characters like spaces, special characters
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");

}