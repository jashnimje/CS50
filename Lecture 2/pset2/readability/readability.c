#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    int cWords = 0, cSentences = 0, cLetters = 0;
    string st = get_string("Text: ");
    int i, n = strlen(st);
    for (i = 0; i < n; i++)
    {

        // Counts Words
        if (st[i] == ' ')
        {
            cWords++;
        }

        // Counts Letters
        if (tolower(st[i]) >= 'a' && tolower(st[i]) <= 'z')
        {
            cLetters++;
        }

        // Counts Sentences
        if (st[i] == '.' || st[i] == '!' || st[i] == '?')
        {
            cSentences++;
        }
    }

    // Increments a Word after sentence is over since it does not do in the loop
    cWords++;

    // printf("Words: %d\n", cWords);
    // printf("Sentences: %d\n", cSentences);
    // printf("Letters: %d\n", cLetters);

    int index = round(0.0588 * (cLetters * 100 / (float)cWords) - 0.296 * (cSentences * 100 / (float)cWords) - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
}