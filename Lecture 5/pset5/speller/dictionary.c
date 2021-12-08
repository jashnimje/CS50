// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10;

// Hash table
node *table[N];

// Dict Size
int dictSize = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int val = hash(word);
    node *head = table[val];

    while (head != NULL)
    {
        if (strcasecmp(word, head->word) == 0)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0, nWord = strlen(word);
    for (int j = 0; word[j] != '\0'; j++)
    {
        sum += tolower(word[j]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open a file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL || dictionary == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        int val = hash(word);
        n->next = table[val];
        table[val] = n;
        dictSize++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictSize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        while (head != NULL)
        {
            node *tmp = head;
            head = head->next;
            free(tmp);
        }

        if (head == NULL && i == N - 1)
        {
            return true;
        }
    }
    return true;
}
