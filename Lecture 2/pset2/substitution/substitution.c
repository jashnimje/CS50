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
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check if arg key has 26 chars
    int i, n = strlen(argv[1]);
    string sub = argv[1];
    char seen[26] = {0};

    if (n != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check if all char is alphabets
    for (i = 0; i < n; i++)
    {
        if (!isalpha(sub[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        int a;
        if (islower(sub[i]))
        {
            a = sub[i] - 97;
        }
        else
        {
            a = sub[i] - 65;
        }

        seen[a]++;
    }

    // Check if all are distinct and not repeated
    for (i = 0; i < n; i++)
    {
        if (seen[i] != 1)
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
    }

    // Starts encryption
    string plaintext = get_string("plaintext: ");
    string ciphertext = "";

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
                printf("%c", tolower(sub[plaintext[i] - 97]));
            }
            else
            {
                // First subtract the value eg-> A = 0
                printf("%c", toupper(sub[plaintext[i] - 65]));
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